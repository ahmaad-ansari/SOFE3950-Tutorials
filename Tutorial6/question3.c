#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 5

sem_t semaphores[NUM_THREADS];

int moving_sum[NUM_THREADS] = {0};

struct thread_data {
    int num;
    int index;
};

void *factorial(void *threadarg) {
    struct thread_data *data;
    data = (struct thread_data *) threadarg;
    int num = data->num;
    int index = data->index;

    int fact = 1;
    for (int i = 1; i <= num; i++) {
        fact *= i;
    }

    while (1) {
        if (index == 0) {
            sem_wait(&semaphores[index]);
            moving_sum[index] += fact;
            sem_post(&semaphores[index]);
            break;
        } else {
            sem_wait(&semaphores[index - 1]);
            if (moving_sum[index - 1] > 0) {
                moving_sum[index] = moving_sum[index - 1] + fact;
                sem_post(&semaphores[index]);
                sem_post(&semaphores[index - 1]);
                break;
            }
            sem_post(&semaphores[index - 1]);
            sched_yield(); // allow other threads access to critical section
        }
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    struct thread_data data[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        sem_init(&semaphores[i], 0, 1);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        printf("Enter number %d: ", i + 1);
        scanf("%d", &data[i].num);
        data[i].index = i;
        pthread_create(&threads[i], NULL, factorial, (void *) &data[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Moving sum: ");
    for (int i = 0; i < NUM_THREADS; i++) {
        printf("%d ", moving_sum[i]);
    }
    printf("\n");

    pthread_exit(NULL);
}
