#include <stdio.h>
#include <omp.h>
#include <math.h>
#include<time.h>


int main ()
{
    int nthreads = 16;

    printf("%s\n","Enter thread number");
    scanf("%d", &nthreads);

    #ifdef _OPENMP
    omp_set_num_threads(nthreads);
    #endif

    int n = 100000000;

    double y[n];

    double dx = 1/(n+1);
    clock_t start, stop;
    start = clock();
    #pragma omp parallel
    {

      for (int i =0;i<n;i++){

            int x =i*dx;
            y[i] = exp(x) * cos (x) * sin (x) * sqrt (5 * x + 6.0);

      }
    }
    stop=clock();

    printf("Total time %d\n",stop-start);


    return 0;
}
