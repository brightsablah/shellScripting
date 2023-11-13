#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

volatile int exit_flag = 0;

// Signal handler for Ctrl+C (SIGINT)
void handle_sigint(int signum)
{
    if (signum == SIGINT)
    {
        printf("\nCtrl+C detected. Exiting...\n");
        exit_flag = 1;
    }
}

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t getline_return;

    // Set the signal handler for Ctrl+C
    signal(SIGINT, handle_sigint);

    while (!exit_flag)
    {
        printf("#cisfun$ ");

        getline_return = getline(&line, &len, stdin);

        if (getline_return == -1)
        {
            printf("\nError reading input\n");
            exit(EXIT_FAILURE);
        }

        printf("line: %s", line);

        // If the user pressed Enter without typing anything, exit the loop
        if (getline_return == 1 && line[0] == '\n')
        {
            break;
        }

        // Fork a process to run a shell
        pid_t shell_pid = fork();

        if (shell_pid == -1)
        {
            perror("Error forking shell process");
            exit(EXIT_FAILURE);
        }

        if (shell_pid == 0)
        {
            // Child process (shell)
            char *shell_path = "/bin/sh";
           // char *shell_args[] = {"sh", "-c", line, NULL};
          char *shell_args[] = {"sh","-c" , line, NULL};

            execve(shell_path, shell_args, NULL);

            // If execve fails
            perror("Error executing shell");
            exit(EXIT_FAILURE);
        }
        else
        {
            // Parent process
            // Wait for the shell process to finish
            wait(NULL);
        }
    }

    free(line); // Free allocated memory

    return 0;
}

