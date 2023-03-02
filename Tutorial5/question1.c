#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define _XOPEN_SOURCE 600 // Required for barriers to work

void *hello_world(void *arg) {
    // Sleep for a random duration
    int sleep_duration = rand() % 10 + 1;
    sleep(sleep_duration);

    printf("Hello World!\n");

    pthread_exit(NULL);
}

void *goodbye(void *arg) {
    // Sleep for a random duration
    int sleep_duration = rand() % 20 + 1;
    sleep(sleep_duration);

    printf("Goodbye!\n");

    pthread_exit(NULL);
}

int main(void) {
    pthread_t tid1, tid2;

    // Create threads
    pthread_create(&tid1, NULL, hello_world, NULL);
    pthread_create(&tid2, NULL, goodbye, NULL);

    // Wait for threads to finish
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;
}