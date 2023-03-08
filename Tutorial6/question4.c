#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define BUFFER_SIZE 5
#define NUMBERS 10

int buffer[BUFFER_SIZE] = {0};
int numbers[NUMBERS];

sem_t empty;
sem_t full;
sem_t mutex;

void *producer(void *arg)
{
    int i, j = 0;
    while (j < NUMBERS) {
        sem_wait(&empty);
        sem_wait(&mutex);
        for (i = 0; i < BUFFER_SIZE; i++) {
            if (buffer[i] == 0) {
                buffer[i] = numbers[j];
                printf("Produced %d\n", numbers[j]);
                j++;
                break;
            }
        }
        sem_post(&mutex);
        sem_post(&full);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg)
{
    int i, j = 0;
    while (j < NUMBERS) {
        sem_wait(&full);
        sem_wait(&mutex);
        for (i = 0; i < BUFFER_SIZE; i++) {
            if (buffer[i] != 0) {
                printf("Consumed %d\n", buffer[i]);
                buffer[i] = 0;
                j++;
                break;
            }
        }
        sem_post(&mutex);
        sem_post(&empty);
    }
    pthread_exit(NULL);
}

int main()
{
    int i;
    srand(time(NULL));
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    printf("Enter ten numbers:\n");
    for (i = 0; i < NUMBERS; i++) {
        scanf("%d", &numbers[i]);
    }

    pthread_t prod, cons;
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    printf("Contents of buffer:\n");
    for (i = 0; i < BUFFER_SIZE; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
