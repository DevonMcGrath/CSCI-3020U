#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>


int main (int argc, char* argv[])
{
  int ierr = MPI_Init(4, 4);
  ierr = MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
  ierr = MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
  printf("Hello World! I'm process %i out of %i processess\n", my_id, num_procs);
  ierr = MPI_Finalize();
}
