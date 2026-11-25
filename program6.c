
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t forks[N];
sem_t room;

void *philosopher(void *arg) {
    int id = *(int *)arg;

    printf("Philosopher %d is thinking.\n", id + 1);
    sleep(1);

    sem_wait(&room);

    sem_wait(&forks[id]);
    sem_wait(&forks[(id + 1) % N]);

    printf("Philosopher %d is eating.\n", id + 1);
    sleep(1);

    sem_post(&forks[(id + 1) % N]);
    sem_post(&forks[id]);

    printf("Philosopher %d finished eating.\n", id + 1);

    sem_post(&room);

    return NULL;
}

int main() {
    pthread_t philosophers[N];
    int ids[N];

    sem_init(&room, 0, N - 1);

    for (int i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1);
        ids[i] = i;
    }

    for (int i = 0; i < N; i++)
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);

    for (int i = 0; i < N; i++)
        pthread_join(philosophers[i], NULL);

    for (int i = 0; i < N; i++)
        sem_destroy(&forks[i]);

    sem_destroy(&room);

    printf("All philosophers finished eating.\n");

    return 0;
}
s