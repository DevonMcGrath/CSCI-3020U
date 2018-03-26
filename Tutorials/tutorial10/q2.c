/*
 * Tutorial 10 MPI Demo for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Author: Jonathan Gillett
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>

// Define process 0 as MASTER
#define MASTER 0

#define DATA_SIZE 10000000
#define CHUNK_SIZE 10000

void master(int n_proc, int ITERATIONS)
{
    double* data =  malloc(DATA_SIZE * sizeof(double));    // The data to send
    double chunk[CHUNK_SIZE] = { 0 };  // The chunk to store results
    int total_chunks = DATA_SIZE / CHUNK_SIZE;
    //calculate the chunk size
                    // The process that returned data
    MPI_Status status;                 // MPI status struct

    // Populate the data to send to slaves
    for (int i = 0; i < DATA_SIZE; ++i)
    {
        data[i] = i;
    }

    double startTime = MPI_Wtime();
    // "Map" the data to slave processes
    // i MUST start from 1, since MASTER is process 0!
    int a =0;
    while (a < ITERATIONS){
      int n_sent = 0, n_recv = 0;        // The number of the data chunks sent/recv
      int proc = 0;
      // "Map" the data to slave processes
      // i MUST start from 1, since MASTER is process 0!
      for (int i = 1; i < n_proc; ++i){
          // Send CHUNK_SIZE of data to each process initially
          // Sends data, of type double to process 'i'
          MPI_Send(&data[n_sent*CHUNK_SIZE], CHUNK_SIZE, MPI_DOUBLE, i,
                   n_sent, MPI_COMM_WORLD);
          n_sent++;
      }

      // Receive EACH of the chunks from the slave processes
      for (int i = 0; i < total_chunks; ++i)
      {
          // Receive the computed chunk back from the slave
          MPI_Recv(chunk, CHUNK_SIZE, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG,
                   MPI_COMM_WORLD, &status);
          // Get the process that sent the data and send it the next chunk
          proc = status.MPI_SOURCE;
          n_recv = status.MPI_TAG;

          // Copy the results from the slave into the results array
          if (n_sent < total_chunks)
          {
              MPI_Send(&data[n_sent*CHUNK_SIZE], CHUNK_SIZE, MPI_DOUBLE, proc,
                       n_sent, MPI_COMM_WORLD);
              n_sent++;
          }
      }
      a++;
  }


      // Send all the slave processes STOP signal, (TAG of CHUNK_SIZE)
      for (int i = 1; i < n_proc; ++i)
      {
          MPI_Send(chunk, CHUNK_SIZE, MPI_DOUBLE, i,
                   CHUNK_SIZE, MPI_COMM_WORLD);
      }


    double endTime = MPI_Wtime();

    printf("The total time to send %d doubles values %d time is %f\n", DATA_SIZE, ITERATIONS, endTime-startTime);
}


void slave(int proc_id)
{
    double chunk[CHUNK_SIZE] = { 0 };  // The chunk to receive for calculations
    double result[CHUNK_SIZE] = { 0 }; // The results
    int n_recv = 0;                    // The number of the data chunk received
    MPI_Status status;                 // MPI status struct

    // Receive the chunk to calculate from MASTER
    MPI_Recv(chunk, CHUNK_SIZE, MPI_DOUBLE, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    n_recv = status.MPI_TAG;

    // Calculate all results provided until "STOP" signal recieved (CHUNK_SIZE)
    while (n_recv < CHUNK_SIZE)
    {
        //send a pong to master
        for (int i = 0; i < CHUNK_SIZE; ++i)
        {
            result[i] = chunk[i];
        }

        // Send the results back to MASTER, include in TAG the chunk that was calculated
        MPI_Send(result, CHUNK_SIZE, MPI_DOUBLE, MASTER, n_recv, MPI_COMM_WORLD);

        // Wait for the next chunk of data to be received
        MPI_Recv(chunk, CHUNK_SIZE, MPI_DOUBLE, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        n_recv = status.MPI_TAG;
    }
}


int main (int argc, char* argv[])
{
    int proc_id;            // Process rank
    int n_proc;             // Number of processes

    // Initialize MPI
    MPI_Init(&argc, &argv);

    // Get the current number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &n_proc);

    // Get the current process id
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);


    if (proc_id == MASTER)
    {
        master(n_proc,100);
    }
    else
    {
        slave(proc_id);
    }

    // Required to terminate all MPI processes
    MPI_Finalize();
}
