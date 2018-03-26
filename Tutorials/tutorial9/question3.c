#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <omp.h>
#include<stdlib.h>

double expensive(int num)
{
    return rand()%100;
}

int main (int argc, char *argv[])
{
    long double t = omp_get_wtime();
    int ARRAYSIZE = 100;
    double x = 0; // Used in the summation
    int thread_num, nthreads = 16;
    #ifdef _OPENMP
    omp_set_num_threads(nthreads);
    #endif

    #pragma omp parallel for reduction(+: x)
    for (int i = 0; i < ARRAYSIZE; ++i)
    {
        x += expensive(i);
    }
    t = t - omp_get_wtime();
    printf("SUM of x = %f in %d time\n", x/100, t);

    t = omp_get_wtime();
    int z[ARRAYSIZE];
    int zsum = 0;

    for (int i = 0; i < ARRAYSIZE; ++i){
      z[i] = (int)rand()%100;
    }
    for (int i = 0; i < ARRAYSIZE; ++i){
      zsum += z[i];
    }
    t = t - (int)omp_get_wtime();
    printf("SUM of z = %d in %d time\n", zsum/ARRAYSIZE, t);
}
