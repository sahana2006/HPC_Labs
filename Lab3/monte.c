#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main()
{

    long long N;
    long long in;

    printf("Enter number of points: ");
    scanf("%lld", &N);

    in = 0;

    srand(time(NULL));

    clock_t start = clock();

    for (long long i = 0; i < N; i++)
    {

        double x = (double)rand() / RAND_MAX * 2 - 1;
        double y = (double)rand() / RAND_MAX * 2 - 1;

        if (x * x + y * y <= 1)
            in++;
    }

    double pi = 4.0 * in / N;
    clock_t end = clock();

    double tot_time =
        (double)(end - start) / CLOCKS_PER_SEC;

    printf("Estimated Pi = %lf\n", pi);
    printf("Error = %lf\n", fabs(M_PI - pi));
    printf("EXE Time = %f sec\n", tot_time);

    return 0;
}
