#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

#define SIZE 100

// Define process 0 as MASTER
#define MASTER 0

void master(int n_proc) {

	// Check that there is at least one slave
	int slaves = n_proc - 1;
	if (slaves < 1) {
		fprintf(stderr, "ERROR: No slaves to perform computation!\n");
		return;
	}

	int A[SIZE][SIZE];
    int B[SIZE][SIZE];
    int C[SIZE][SIZE]; // result
	int chunk[SIZE + 1] = { 0 }; // row result (+1 for row index)
	MPI_Status status;

    // Populate matrices
    for (int r = 0; r < SIZE; r ++) {
		for (int c = 0; c < SIZE; c ++) {
			A[r][c] = r + 1;
			B[r][c] = c + 1;
			C[r][c] = 0;
		}
	}

	// Send B and the number of rows this slave will process
	int n_rows = SIZE / slaves, remaining = SIZE % slaves;
	for (int i = 1; i < n_proc; i ++) {
		int slave = i - 1;
		int data = n_rows + (slave < remaining? 1 : 0);
		MPI_Send(&B[0][0], SIZE * SIZE, MPI_INT, i, i - 1, MPI_COMM_WORLD);
		MPI_Send(&data, 1, MPI_INT, i, i - 1, MPI_COMM_WORLD);
	}

	// Send the rows to the slaves
	for (int r = 0; r < SIZE; r ++) {
		int slave = r % (n_proc - 1) + 1; // master is 0
		int row[SIZE + 1];
		row[SIZE] = r;
		for (int c = 0; c < SIZE; c ++) { row[c] = A[r][c]; }
		MPI_Send(&row[0], SIZE + 1, MPI_INT, slave, r, MPI_COMM_WORLD);
	}

	// Receive the result from each slave
	for (int i = 0; i < SIZE; i ++) {

		// Get a computed row
		MPI_Recv(chunk, SIZE + 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG,
			MPI_COMM_WORLD, &status);
		
		// Set the row
		int r = chunk[SIZE];
		for (int c = 0; c < SIZE; c ++) {
			C[r][c] = chunk[c];
		}
	}

	// Print the result
	for (int r = 0; r < SIZE; r ++) {
		for (int c = 0; c < SIZE; c ++) {
			printf("%i ", C[r][c]);
		}
		printf("\n");
	}
}

void slave(int proc_id) {
	
	int B[SIZE][SIZE];
	int tmp[1] = { 0 };
	int n_rows = 0;
	int row[SIZE + 1] = { 0 };
	MPI_Status status;

	// Recieve B and the number of rows
	MPI_Recv(B, SIZE * SIZE, MPI_INT, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
	MPI_Recv(tmp, 1, MPI_INT, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
	n_rows = tmp[0];

	// Recieve the n rows
	for (int i = 0; i < n_rows; i ++) {

		int result[SIZE + 1] = { 0 };

		// Receive the row
		MPI_Recv(row, SIZE + 1, MPI_INT, MASTER,
			MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		int r = row[SIZE];
		result[SIZE] = r;
		
		// Do the row calculation
		for (int col = 0; col < SIZE; col ++) {
			for (int c = 0; c < SIZE; c ++) {
				result[col] += row[c] * B[c][r];
			}
		}

		// Send the result
		MPI_Send(result, SIZE + 1, MPI_INT, MASTER, i, MPI_COMM_WORLD);
	}
}

int main (int argc, char* argv[]) {

	int proc_id;            // Process rank
	int n_proc;             // Number of processes

	// Initialize MPI
	MPI_Init(&argc, &argv);

	// Get the current process id
	MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);

	// Get the current number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &n_proc);

	if (proc_id == MASTER) {
		master(n_proc);
	} else {
		slave(proc_id);
	}

	// Required to terminate all MPI processes
	MPI_Finalize();
}