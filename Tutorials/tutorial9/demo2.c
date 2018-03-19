#include <stdio.h>
#include <omp.h>
int main (int argc, char *argv[])
{
    int num = 0; // Watch out for race conditions!
    int thread_num, nthreads = 16;
    /*
    will set the number of threads
    if OpenMP is liked
    */
    #ifdef _OPENMP
    omp_set_num_threads(nthreads);
    #endif
    printf("Testing OpenMP, you should see each thread print...\n");

    /*
    tells the compiler that we are going to be using
    a pre processor.  In this case we are telling the
    compiler that this block is using the omp parallel pre-processor
    */
    #pragma omp parallel
    {

      /*
      tells the compiler that this block is
      in the omp critical section
      */
        #pragma omp critical
        {
            thread_num = omp_get_thread_num();
            #ifdef _OPENMP
            num += 1; // THREAD SAFE INCREMENT
            printf("This thread = %d, num = %d\n", thread_num, num);
            #endif
        }
    }
    return 0;
}
