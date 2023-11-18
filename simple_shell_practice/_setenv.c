#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// External variable defined in the system library
extern char **environ;

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

/**
 * _setenv - Change or add an environment variable.
 * @name: Name of the environment variable.
 * @value: Value to set for the environment variable.
 * @overwrite: Flag to determine whether to overwrite an existing variable.
 *
 * Return: 0 on success, -1 on failure.
 */
int _setenv(const char *name, const char *value, int overwrite) {
    if (name == NULL || *name == '\0' || strchr(name, '=') != NULL) {
        return -1; // Invalid input
    }

    // Check if the variable already exists
    char *existingValue = _getenv(name);

    // If the variable exists and overwrite is 0, do nothing
    if (existingValue != NULL && !overwrite) {
        return 0;
    }

    // Concatenate name=value into a single string
    size_t envVarLength = strlen(name) + strlen(value) + 2; // +2 for '=' and null terminator
    char *newEnvVar = (char *)malloc(envVarLength);
    if (newEnvVar == NULL) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }
    snprintf(newEnvVar, envVarLength, "%s=%s", name, value);

    // Update the environment by reallocating and copying
    int envSize = 0;
    while (environ[envSize] != NULL) {
        envSize++;
    }

    char **newEnviron = (char **)malloc((envSize + 2) * sizeof(char *));
    if (newEnviron == NULL) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    // Copy existing environment variables
    for (int i = 0; i < envSize; i++) {
        newEnviron[i] = environ[i];
    }

    // Free the memory of the existing environment variable
    if (existingValue != NULL) {
        free(existingValue);
    }

    // Add the new environment variable
    newEnviron[envSize] = newEnvVar;
    newEnviron[envSize + 1] = NULL;

    // Free the memory of the old environment variables
    free(environ);

    // Update the global environ pointer
    environ = newEnviron;

    return 0;
}

int main(void) {
    // Example usage
    _setenv("MY_VARIABLE", "some_value", 1);

    // Access the value of the environment variable
    char *value = getenv("MY_VARIABLE");
    if (value != NULL) {
        printf("Value of MY_VARIABLE: %s\n", value);
    } else {
        printf("MY_VARIABLE not found in the environment.\n");
    }

    return 0;
}

