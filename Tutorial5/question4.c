#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define _XOPEN_SOURCE 600 // Required for barriers to work
#define NUM_STUDENTS 10

int grades[NUM_STUDENTS]; // Array to hold grades
int total_grade = 0; // Global variable for the total grade
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex for mutual exclusion

void *class_total(void *arg) {
    // Cast the arg pointer to an int pointer
    int grade = *((int *) arg);

    pthread_mutex_lock(&mutex); // Acquire lock
    total_grade += grade; // Increment total_grade
    pthread_mutex_unlock(&mutex); // Release lock

    pthread_exit(NULL);
}

int main(void) {
    pthread_t tids[NUM_STUDENTS];

    // Prompt the professor for grades and store them in the array
    printf("Enter the grades of %d students:\n", NUM_STUDENTS);
    for (int i = 0; i < NUM_STUDENTS; i++) {
        printf("Student %d: ", (i+1));
        scanf("%d", &grades[i]);
    }

    // Create threads for each student and pass in their grade as the argument
    for (int i = 0; i < NUM_STUDENTS; i++) {
        if (pthread_create(&tids[i], NULL, class_total, &grades[i])) {
            fprintf(stderr, "Error creating thread for student %d\n", i);
            exit(1);
        }
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_STUDENTS; i++) {
        if (pthread_join(tids[i], NULL)) {
            fprintf(stderr, "Error joining thread for student %d\n", i);
            exit(1);
        }
    }

    printf("Total grade: %d\n", total_grade);

    return 0;
}