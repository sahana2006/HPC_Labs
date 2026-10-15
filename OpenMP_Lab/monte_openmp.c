#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

int main()
{

    long long N;
    long long in;

    printf("Enter number of points: ");
    scanf("%lld", &N);

    in = 0;

    srand(time(NULL));

    double start = omp_get_wtime();

    #pragma omp parallel reduction(+:in)
    {
        // Each thread gets its own random number seed
        unsigned int seed = (unsigned int)time(NULL)
                            + omp_get_thread_num();

        #pragma omp for
        for (long long i = 0; i < N; i++)
        {
            double x = (double)rand_r(&seed) / RAND_MAX * 2 - 1;
            double y = (double)rand_r(&seed) / RAND_MAX * 2 - 1;

            if (x * x + y * y <= 1)
                in++;
        }
    }

    double pi = 4.0 * in / N;
    clock_t end = omp_get_wtime();

    double tot_time =
        (double)(end - start) / CLOCKS_PER_SEC;

    printf("Estimated Pi = %lf\n", pi);
    printf("Error = %lf\n", fabs(M_PI - pi));
    printf("EXE Time = %f sec\n", tot_time);

    return 0;
}
