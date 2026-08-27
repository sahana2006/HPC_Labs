#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000

int image[N][N];
int output[N][N];

int kernel[3][3] = {
    {-1, -1, -1},
    {-1,  5, -1},
    {-1, -1, -1}
};

int main()
{
    // Random number assignment to each index
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            image[i][j] = rand() % 256;
        }
    }

    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    // Edge detection by mapping the kernel over the image
    for (int i = 1; i < N - 1; i++)
    {
        for (int j = 1; j < N - 1; j++)
        {
            int sum = 0;

            for (int ki = -1; ki <= 1; ki++)
            {
                for (int kj = -1; kj <= 1; kj++)
                {
                    sum += image[i + ki][j + kj]
                           * kernel[ki + 1][kj + 1];
                }
            }

            output[i][j] = sum;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double time =
        (end.tv_sec - start.tv_sec) +
        (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Serial execution time = %lf sec\n", time);

    return 0;
}