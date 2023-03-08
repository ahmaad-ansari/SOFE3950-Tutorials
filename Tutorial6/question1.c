#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    // Create two child processes using fork()
    pid_t pid1 = fork();
    
    if (pid1 < 0) {
        fprintf(stderr, "Failed to fork child process 1\n");
        exit(1);
    }

    if (pid1 == 0) {
        // Child process 1
        FILE *fp1 = fopen("child1.txt", "w");
        if (fp1 == NULL) {
            fprintf(stderr, "Failed to open child1.txt for writing\n");
            exit(1);
        }
        fprintf(fp1, "child 1\n");
        fclose(fp1);
        sleep(1);
        fp1 = fopen("child1.txt", "r");
        if (fp1 == NULL) {
            fprintf(stderr, "Failed to open child1.txt for reading\n");
            exit(1);
        }
        char line[100];
        fgets(line, 100, fp1);
        printf("Child 1 contents: %s", line);
        fclose(fp1);
        exit(0);
    }

    pid_t pid2 = fork();
    if (pid2 < 0) {
        fprintf(stderr, "Failed to fork child process 2\n");
        exit(1);
    }

    if (pid2 == 0) {
        // Child process 2
        FILE *fp2 = fopen("child2.txt", "w");
        if (fp2 == NULL) {
            fprintf(stderr, "Failed to open child2.txt for writing\n");
            exit(1);
        }
        fprintf(fp2, "child 2\n");
        fclose(fp2);
        sleep(1);
        fp2 = fopen("child2.txt", "r");
        if (fp2 == NULL) {
            fprintf(stderr, "Failed to open child2.txt for reading\n");
            exit(1);
        }
        char line[100];
        fgets(line, 100, fp2);
        printf("Child 2 contents: %s", line);
        fclose(fp2);
        exit(0);
    }

    // Wait for child processes to exit
    int status;
    waitpid(pid1, &status, 0);
    waitpid(pid2, &status, 0);

    // Master process
    printf("Master process finished\n");
    return 0;
}
