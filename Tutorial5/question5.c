#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#define NUM_THREADS 10
#define GRADES_FILE "grades.txt"
#define BELLCURVE_FILE "bellcurve.txt"

int grades[NUM_THREADS];
int total_grade = 0;
float total_bellcurve = 0.0;

pthread_barrier_t barrier;
pthread_mutex_t mutex;

void* save_bellcurve(void* arg) {
    int* grade = (int*) arg;
    float bellcurve = (*grade) * 1.5;

    pthread_mutex_lock(&mutex);
    total_grade += (*grade);
    total_bellcurve += bellcurve;

    FILE* fp = fopen(BELLCURVE_FILE, "a");
    if (fp != NULL) {
        fprintf(fp, "%.2f\n", bellcurve);
        fclose(fp);
    }
    pthread_mutex_unlock(&mutex);
    
    pthread_barrier_wait(&barrier);

    return NULL;
}

void read_grades() {
    FILE* fp = fopen(GRADES_FILE, "r");
    if (fp == NULL) {
        printf("Error opening file %s\n", GRADES_FILE);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        fscanf(fp, "%d", &grades[i]);
    }

    fclose(fp);
}

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_t read_grades_thread[1];

    pthread_barrier_init(&barrier, NULL, NUM_THREADS + 1);
    pthread_mutex_init(&mutex, NULL);
    
    pthread_create(&read_grades_thread[0], NULL, read_grades, NULL);
    pthread_join(read_grades_thread[0], NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, save_bellcurve, &grades[i]);
    }

    pthread_barrier_wait(&barrier);

    float class_avg_before = (float) total_grade / NUM_THREADS;
    float class_avg_after = total_bellcurve / NUM_THREADS;

    printf("Total grade: %d\n", total_grade);
    printf("Class average before bellcurve: %.2f\n", class_avg_before);
    printf("Class average after bellcurve: %.2f\n", class_avg_after);

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_barrier_destroy(&barrier);
    pthread_mutex_destroy(&mutex);

    return EXIT_SUCCESS;
}
