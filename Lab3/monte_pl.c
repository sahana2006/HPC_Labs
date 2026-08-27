#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>

#define N 1000000
#define THREADS 4

long long in[THREADS];

void *calculate(void *arg)
{
    int id = *(int *)arg;
    unsigned int seed = id + 1;

    in[id] = 0;

    for (long long i = 0; i < N / THREADS; i++)
    {
        double x = (double)rand_r(&seed) / RAND_MAX * 2 - 1;
        double y = (double)rand_r(&seed) / RAND_MAX * 2 - 1;

        if (x * x + y * y <= 1)
            in[id]++;
    }

    return NULL;
}

int main()
{
    pthread_t threads[THREADS];
    int id[THREADS];

    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    // Create threads and concurrently call the calculate function
    for (int i = 0; i < THREADS; i++)
    {
        id[i] = i;
        pthread_create(&threads[i], NULL, calculate, &id[i]);
    }

    // Wait for threads to join after the last thread has been executed
    for (int i = 0; i < THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Combine results from all results
    long long total_inside = 0;

    for (int i = 0; i < THREADS; i++)
    {
        total_inside += in[i];
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double pi = 4.0 * total_inside / N;

    double time =
        (end.tv_sec - start.tv_sec) +
        (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Pi = %lf\n", pi);
    printf("Time = %lf seconds\n", time);

    return 0;
}