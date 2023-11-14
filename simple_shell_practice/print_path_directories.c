#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *_getenv(const char *name);
void print_path_directories(void);
// External variable defined in the system library
extern char **environ;

/**
 * print_path_directories - Print each directory in the PATH environment variable.
 */
void print_path_directories(void) {
    // Get the value of the PATH environment variable
    char *path = _getenv("PATH");

    if (path == NULL) {
        printf("PATH environment variable not found\n");
        return;
    }

    // Iterate through the directories in the PATH
    char *token = strtok(path, ":");
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, ":");
    }
}

/**
 * _getenv - Get the value of an environment variable.
 * @name: Name of the environment variable.
 *
 * Return: Pointer to the value of the environment variable,
 * or NULL if the variable is not found.
 */
char *_getenv(const char *name) {
    if (name == NULL || *name == '\0') {
        return NULL; // Invalid input
    }

    // Iterate through the environment variables
    for (char **env = environ; *env != NULL; env++) {
        // Check if the current environment variable starts with the specified name
        if (strncmp(*env, name, strlen(name)) == 0 && (*env)[strlen(name)] == '=') {
            // Return the value part of the environment variable
            return *env + strlen(name) + 1;
        }
    }

    return NULL; // Variable not found
}

int main(void) {
    // Example usage
    print_path_directories();

    return 0;
}

