#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>


int main (int argc, char* argv[])
{
  int MAX = 100;
  int primes[MAX];
  int ierr = MPI_Init(4, 4);
  ierr = MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
  ierr = MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
  printf("Hello World! I'm process %i out of %i processess\n", my_id, num_procs);
for(int index = 0; index < MAX; index++){
	for(int indey = 2; indey < index; indey++){
		if(index % indey == 0){
break;}else{
continue;
}
primes[index] = index;
}
} 
  ierr = MPI_Finalize();
}
