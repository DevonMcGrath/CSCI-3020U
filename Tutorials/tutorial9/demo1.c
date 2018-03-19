#include <stdio.h>
#include <omp.h>

int main (int argc, char *argv[])
{
    printf("This statement will always print.\n");
    /*
    * will only enter this block when openmp is linked properly to the program
    */
    #ifdef _OPENMP
    printf("This statement will only print when compiled with \"-fopenmp\"\n");
    #endif
    return 0;
}