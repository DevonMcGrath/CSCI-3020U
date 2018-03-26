#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <omp.h>
#include <stdlib.h>


int main (int argc, char *argv[])
{
    long double t = omp_get_wtime();
    int ARRAYSIZE = 10;
    int matrix1 [ARRAYSIZE][ARRAYSIZE];
    int matrix2 [ARRAYSIZE][ARRAYSIZE];
    int output [ARRAYSIZE][ARRAYSIZE];

    //Populate Arrays
    for(int index = 0; index < ARRAYSIZE*ARRAYSIZE; index++){
      matrix1[index/ARRAYSIZE][index%ARRAYSIZE] = rand()%5;
      matrix2[index/ARRAYSIZE][index%ARRAYSIZE] = rand()%5;
    }


    int thread_num, nthreads = 16;
    #ifdef _OPENMP
    omp_set_num_threads(nthreads);
    #endif

    for(int index = 0; index < ARRAYSIZE; index++){
      for(int indey = 0; indey < ARRAYSIZE; indey++){
        #pragma omp parallel for reduction(+: output[index][indey])
        for(int indez = 0; indez < ARRAYSIZE; indez++){
          output[index][indey] += matrix1[index][indez] *  matrix2[indez][indey];
        }
      printf("%d ", output[index][indey]);
      }
      printf("\n");
    }

    t = t - omp_get_wtime();
}
