#define _XOPEN_SOURCE 600 // Required for barriers to work
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_GRADES 10

int grades[NUM_GRADES]; // Array to hold grades
int total_grade = 0;
int total_bellcurve = 0;

pthread_barrier_t barrier;
pthread_mutex_t lock;

void *read_grades(void *arg) {
    FILE *fp = fopen("grades.txt", "r");
    if (fp == NULL) {
        printf("Error: could not open grades.txt\n");
        exit(1);
    }

    for (int i = 0; i < NUM_GRADES; i++) {
        fscanf(fp, "%d", &grades[i]);
    }
    
    fclose(fp);
    pthread_barrier_wait(&barrier);
    pthread_exit(NULL);
}

void *save_bellcurve(void *arg) {
    int grade = *((int *)arg);
    
    pthread_mutex_lock(&lock);
    total_grade += grade;
    pthread_mutex_unlock(&lock);
    
    int bellcurve = (int) (grade *1.5);

    pthread_mutex_lock(&lock);
    total_bellcurve += bellcurve;
    pthread_mutex_unlock(&lock);

    FILE *fp = fopen("bellcurve.txt", "a");
    if (fp == NULL) {
        printf("Error: could not open bellcurve.txt\n");
        exit(1);
    }

    fprintf(fp, "%d\n", bellcurve);
    
    fclose(fp);
    
    pthread_exit(NULL);
}

int main(void) {
    pthread_t tids[NUM_GRADES + 1];

    pthread_barrier_init(&barrier, NULL, NUM_GRADES + 1);
    pthread_mutex_init(&lock, NULL);

    pthread_create(&tids[0], NULL, read_grades, NULL);

    for (int i = 1; i <= NUM_GRADES; i++) {
        pthread_create(&tids[i], NULL, save_bellcurve, (void *) &grades[i-1]);
    }

    for (int i = 0; i < NUM_GRADES + 1; i++) {
        pthread_join(tids[i], NULL);
    }

    float class_avg_before = (float)total_grade / NUM_GRADES;
    float class_avg_after = (float)total_bellcurve / NUM_GRADES;
    fflush(stdout);
    printf("Total grade: %d\n", total_grade);
    printf("Class average before bellcurve: %.2f\n", class_avg_before);
    printf("Total bellcurve: %d\n", total_bellcurve);
    printf("Class average after bellcurve: %.2f\n", class_avg_after);

    pthread_barrier_destroy(&barrier);
    pthread_mutex_destroy(&lock);

    return 0;
}