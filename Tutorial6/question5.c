#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_THREADS 5

int total_sum = 0;
sem_t sem;

void *factorial(void *arg) {
    int *num = (int*) arg;
    int fact = 1;
    for (int i = 1; i <= *num; i++) {
        fact *= i;
    }
    sem_wait(&sem);
    total_sum += fact;
    printf("Factorial of %d is %d\n", *num, fact);
    printf("Current sum is %d\n", total_sum);
    sem_post(&sem);
    pthread_exit(NULL);
}

int main() {
    int numbers[NUM_THREADS];
    printf("Enter five numbers:\n");
    for (int i = 0; i < NUM_THREADS; i++) {
        scanf("%d", &numbers[i]);
    }
    FILE *fp;
    fp = fopen("numbers.txt", "w");
    if (fp == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        fprintf(fp, "%d ", numbers[i]);
    }
    fclose(fp);
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        fp = fopen("numbers.txt", "r");
        if (fp == NULL) {
            printf("Error opening file.\n");
            exit(1);
        }
        for (int i = 0; i < NUM_THREADS; i++) {
            fscanf(fp, "%d", &numbers[i]);
        }
        fclose(fp);
        pthread_t threads[NUM_THREADS];
        sem_init(&sem, 0, 1);
        for (int i = 0; i < NUM_THREADS; i++) {
            pthread_create(&threads[i], NULL, factorial, (void*) &numbers[i]);
        }
        for (int i = 0; i < NUM_THREADS; i++) {
            pthread_join(threads[i], NULL);
        }
        fp = fopen("sum.txt", "w");
        if (fp == NULL) {
            printf("Error opening file.\n");
            exit(1);
        }
        fprintf(fp, "%d", total_sum);
        fclose(fp);
        exit(0);
    } else if (pid > 0) {
        // Parent process
        wait(NULL);
        fp = fopen("sum.txt", "r");
        if (fp == NULL) {
            printf("Error opening file.\n");
            exit(1);
        }
        int sum;
        fscanf(fp, "%d", &sum);
        printf("Total sum is %d\n", sum);
        fclose(fp);
    } else {
        printf("Error forking.\n");
        exit(1);
    }
    return 0;
}
