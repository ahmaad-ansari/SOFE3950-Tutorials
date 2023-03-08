#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_GRADES 10

int grades[NUM_GRADES];
int total_grade = 0;
int total_bellcurve = 0;

pthread_barrier_t barrier;
pthread_mutex_t mutex;
pthread_t threads[NUM_GRADES];

void *save_bellcurve(void *arg) {
    int grade = *(int *)arg;
    int bellcurve = grade * 1.5;

    pthread_mutex_lock(&mutex);
    total_grade += grade;
    total_bellcurve += bellcurve;
    pthread_mutex_unlock(&mutex);

    FILE *file = fopen("bellcurve.txt", "a");
    fprintf(file, "%d\n", bellcurve);
    fclose(file);

    pthread_barrier_wait(&barrier);

    return NULL;
}

void read_grades() {
    FILE *file = fopen("grades.txt", "r");
    for (int i = 0; i < NUM_GRADES; i++) {
        fscanf(file, "%d", &grades[i]);
    }
    fclose(file);
    pthread_barrier_wait(&barrier);
}

int main() {
    pthread_barrier_init(&barrier, NULL, NUM_GRADES + 1);
    pthread_mutex_init(&mutex, NULL);

    read_grades();

    for (int i = 0; i < NUM_GRADES; i++) {
        pthread_create(&threads[i], NULL, save_bellcurve, &grades[i]);
    }

    for (int i = 0; i < NUM_GRADES; i++) {
        pthread_join(threads[i], NULL);
    }

    double class_avg = (double)total_grade / NUM_GRADES;
    double bellcurve_avg = (double)total_bellcurve / NUM_GRADES;

    printf("Total grade: %d\n", total_grade);
    printf("Class average before bellcurve: %f\n", class_avg);
    printf("Class average after bellcurve: %f\n", bellcurve_avg);

    pthread_barrier_destroy(&barrier);
    pthread_mutex_destroy(&mutex);

    return 0;
}
