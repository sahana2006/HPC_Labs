#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

pthread_mutex_t chopstick[N];

void *philosopher(void *arg)
{
    int id = *(int *)arg;

    int left = id;
    int right = (id + 1) % N;

    while (1)
    {
        printf("Philosopher %d is thinking\n", id);
        sleep(1);

        // Different order for even and odd philosophers
        if (id % 2 == 0)
        {
            pthread_mutex_lock(&chopstick[right]);
            pthread_mutex_lock(&chopstick[left]);
        }
        else
        {
            pthread_mutex_lock(&chopstick[left]);
            pthread_mutex_lock(&chopstick[right]);
        }

        printf("Philosopher %d is eating\n", id);
        sleep(1);

        pthread_mutex_unlock(&chopstick[left]);
        pthread_mutex_unlock(&chopstick[right]);

        printf("Philosopher %d finished eating\n", id);
    }

    return NULL;
}

int main()
{
    pthread_t philosophers[N];
    int id[N];

    // Initialize chopsticks
    for (int i = 0; i < N; i++)
    {
        pthread_mutex_init(&chopstick[i], NULL);
    }

    // Create philosophers
    for (int i = 0; i < N; i++)
    {
        id[i] = i;

        pthread_create(
            &philosophers[i],
            NULL,
            philosopher,
            &id[i]
        );
    }

    // Wait for philosophers
    for (int i = 0; i < N; i++)
    {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}