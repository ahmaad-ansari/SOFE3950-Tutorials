#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define _XOPEN_SOURCE 600 // Required for barriers to work

void *bellcurve(void *grade) {
    // Cast the grade pointer to an integer pointer
    int *p_grade = (int *) grade;

    // Bellcurve the grade
    int bellcurved_grade = *p_grade * 1.50;

    printf("Bellcurved grade: %d\n", bellcurved_grade);

    pthread_exit(NULL);
}

int main(void) {
    int grades[5];
    pthread_t tids[5];

    // Prompt the professor for five student's grades
    printf("Enter five student's grades:\n");

    for (int i = 0; i < 5; i++) {
        printf("Student %d: ", (i+1));
        scanf("%d", &grades[i]);
    }

    printf("\nThe bellcurved grades are: \n");

    // Create threads
    for (int i = 0; i < 5; i++) {
        pthread_create(&tids[i], NULL, bellcurve, (void *) &grades[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < 5; i++) {
        pthread_join(tids[i], NULL);
    }

    return 0;
}