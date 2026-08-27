#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 1000
#define THREADS 16

int image[N][N];
int output[N][N];

int kernel[3][3] = {
    {-1, -1, -1},
    {-1,  5, -1},
    {-1, -1, -1}
};

void *edge_detection(void *arg)
{
    int id = *(int *)arg;

    int start = id * (N / THREADS);
    int end = (id + 1) * (N / THREADS);

    // Avoid boundary rows
    if (start < 1)
        start = 1;

    if (end > N - 1)
        end = N - 1;

    for (int i = start; i < end; i++)
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

    return NULL;
}

int main()
{
    pthread_t threads[THREADS];
    int id[THREADS];

    // Create image
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            image[i][j] = rand() % 256;
        }
    }

    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    // Create threads
    for (int i = 0; i < THREADS; i++)
    {
        id[i] = i;

        pthread_create(
            &threads[i],
            NULL,
            edge_detection,
            &id[i]
        );
    }

    // Wait for threads
    for (int i = 0; i < THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double time =
        (end.tv_sec - start.tv_sec) +
        (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Threads = %d\n", THREADS);
    printf("Parallel execution time = %lf seconds\n", time);

    return 0;
}