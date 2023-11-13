#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int i;

    for (i = 0; i < 5; ++i) {
        pid_t child_pid = fork();

        if (child_pid == -1) {
            perror("Error:");
            exit(EXIT_FAILURE);
        }

        if (child_pid == 0) {
            // Child process
            printf("Child %d executing ls -l /tmp:\n", i + 1);
            execlp("ls", "ls", "-l", "/tmp", NULL);

            // If execlp fails
            perror("Error:");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            wait(NULL); // Wait for the child to exit
        }
    }

    // Code executed only by the original parent process
    printf("All children have finished.\n");

    return 0;
}

