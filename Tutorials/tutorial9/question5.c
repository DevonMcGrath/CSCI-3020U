/* Name: question5.c
 * Author: Devon McGrath
 * Description: This is question 5 code for tutorial 9 of CSCI 3020U.
 * Compile with:
 * gcc -Wall -Wextra -std=c99 -fopenmp question5.c -o question5 -lm
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

int main(int argc, char* argv[]) {

    // Parse the number of threads from the command line args
    int nthreads = 1;
    if (argc < 2) {
        printf("Usage: %s <nthreads>\n", argv[0]);
        return EXIT_FAILURE;
    }
    nthreads = atoi(argv[1]);

    #ifdef _OPENMP
    omp_set_num_threads(nthreads);
    #endif

    // Create the file
    FILE* out = fopen("./calculations.txt", "w");

    double x = 0;
    int n = 100000000;
    double dx = 1.0 / (n + 1);
    int write_every = 1000000;

    // Do the expensive operations in parallel
    #pragma omp parallel for private(x)
    for (int i = 0; i <= n; i ++) {

        // Do the calculations
        x = i * dx;
        double y = exp(x) * cos(x) * sin(x) * sqrt(5 * x + 6.0);

        // Write to file
        if (i % write_every == 0) {
            #pragma omp critical
            {
                fprintf(out, "index=%i\tx=%f,\ty=%f\n", i, x, y);
            } 
        }
    }

    // Close the output stream
    fclose(out);

    return EXIT_SUCCESS;
}