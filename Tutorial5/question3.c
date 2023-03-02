#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define _XOPEN_SOURCE 600 // Required for barriers to work

typedef struct {
    char name[50];
    int id;
    int grade;
} student;

void *bellcurve(void *data) {
    // Cast the data pointer to a student pointer
    student *p_student = (student *) data;

    // Bellcurve the grade
    int bellcurved_grade = p_student->grade * 1.50;

    printf("Name: %s, ID: %d, Bellcurved grade: %d\n", p_student->name, p_student->id, bellcurved_grade);

    pthread_exit(NULL);
}

int main(void) {
    student students[5];
    pthread_t tids[5];

    // Prompt the professor for five student's grades
    printf("Enter five student's names, IDs, and grades:\n");

    for (int i = 0; i < 5; i++) {
        printf("Student %d: ", (i+1));
        scanf("%s %d %d", students[i].name, &students[i].id, &students[i].grade);
    }

    printf("\nThe bellcurved grades and student information are: \n");

    // Create threads
    for (int i = 0; i < 5; i++) {
        pthread_create(&tids[i], NULL, bellcurve, (void *) &students[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < 5; i++) {
        pthread_join(tids[i], NULL);
    }

    return 0;
}