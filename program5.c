
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex, write_lock;
int read_count = 0;
int shared_data = 0;

void *reader(void *arg) {
    int id = *(int *)arg;

    sem_wait(&mutex);
    read_count++;

    if (read_count == 1)
        sem_wait(&write_lock);

    sem_post(&mutex);

    printf("Reader %d is reading data: %d\n", id, shared_data);
    sleep(1);

    sem_wait(&mutex);
    read_count--;

    if (read_count == 0)
        sem_post(&write_lock);

    sem_post(&mutex);

    return NULL;
}

void *writer(void *arg) {
    int id = *(int *)arg;

    sem_wait(&write_lock);

    shared_data++;
    printf("Writer %d is writing data: %d\n", id, shared_data);
    sleep(1);

    sem_post(&write_lock);

    return NULL;
}

int main() {
    pthread_t readers[3], writers[2];
    int reader_ids[3] = {1, 2, 3};
    int writer_ids[2] = {1, 2};

    sem_init(&mutex, 0, 1);
    sem_init(&write_lock, 0, 1);

    for (int i = 0; i < 3; i++)
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);

    for (int i = 0; i < 2; i++)
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);

    for (int i = 0; i < 3; i++)
        pthread_join(readers[i], NULL);

    for (int i = 0; i < 2; i++)
        pthread_join(writers[i], NULL);

    sem_destroy(&mutex);
    sem_destroy(&write_lock);

    return 0;
}
