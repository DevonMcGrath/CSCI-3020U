#include <stdio.h>
#include <omp.h>
#include <math.h>

int main (){
    int nthreads = 16;

    printf("%s\n","Enter thread number");
    scanf("%d", &nthreads);

    #ifdef _OPENMP
    omp_set_num_threads(nthreads);
    #endif

    int n = 100000000;

    double y[n];

    double dx = 1/(n+1);

    #pragma omp parallel
    {
      for (int i =0;i<n;i++){
        int x =i*dx;
        y[i] = exp(x) * cos (x) * sin (x) * sqrt (5 * x + 6.0);

      }
    }

    return 0;
}
