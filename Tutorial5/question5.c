#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 10

pthread_barrier_t barrier;
pthread_mutex_t mutex;
int total_grade = 0;
int total_bellcurve = 0;

void *read_grades(void *arg) {
    FILE *file = fopen("grades.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        exit(EXIT_FAILURE);
    }
    int grade;
    for (int i = 0; i < 10; i++) {
        fscanf(file, "%d", &grade);
        pthread_barrier_wait(&barrier);
    }
    fclose(file);
    pthread_exit(NULL);
}

void *save_bellcurve(void *arg) {
    int *grade_ptr = (int *)arg;
    int grade = *grade_ptr;
    pthread_barrier_wait(&barrier);
    int bellcurve = (int)(grade * 1.50);
    pthread_mutex_lock(&mutex);
    total_grade += grade;
    total_bellcurve += bellcurve;
    FILE *file = fopen("bellcurve.txt", "a");
    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%d\n", bellcurve);
    fclose(file);
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main() {
    pthread_barrier_init(&barrier, NULL, NUM_THREADS + 1);
    pthread_mutex_init(&mutex, NULL);

    pthread_t threads[NUM_THREADS + 1]; // +1 for read_grades thread
    pthread_create(&threads[0], NULL, read_grades, NULL);
    for (int i = 1; i <= NUM_THREADS; i++) {
        int *grade_ptr = malloc(sizeof(int));
        if (grade_ptr == NULL) {
            fprintf(stderr, "Error allocating memory\n");
            exit(EXIT_FAILURE);
        }
        FILE *file = fopen("grades.txt", "r");
        if (file == NULL) {
            fprintf(stderr, "Error opening file\n");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < i; j++) {
            fscanf(file, "%d", grade_ptr);
        }
        fclose(file);
        pthread_create(&threads[i], NULL, save_bellcurve, grade_ptr);
    }

    pthread_join(threads[0], NULL);
    for (int i = 1; i <= NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    double class_avg = (double)total_grade / NUM_THREADS;
    double bellcurve_avg = (double)total_bellcurve / NUM_THREADS;
    printf("Total grade: %d\n", total_grade);
    printf("Class average before bellcurve: %.2f\n", class_avg);
    printf("Class average after bellcurve: %.2f\n", bellcurve_avg);

    pthread_barrier_destroy(&barrier);
    pthread_mutex_destroy(&mutex);

    return 0;
}
