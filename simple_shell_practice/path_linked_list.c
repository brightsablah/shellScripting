#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for a node in the linked list
typedef struct PathNode {
    char *directory;
    struct PathNode *next;
} list_node;

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
 * build_path_list - Build a linked list of directories from the PATH environment variable.
 *
 * Return: Pointer to the head of the linked list.
 */
list_node *build_path_list(void) {
    list_node *head = NULL;
    list_node *current = NULL;

    // Get the value of the PATH environment variable
    char *path = _getenv("PATH");

    if (path == NULL) {
        printf("PATH environment variable not found\n");
        return NULL;
    }

    // Tokenize the PATH string using colons as delimiters
    char *token = strtok(path, ":");
    while (token != NULL) {
        // Create a new node for the current directory
        list_node *newNode = (list_node *)malloc(sizeof(list_node));
        if (newNode == NULL) {
            perror("Error allocating memory");
            exit(EXIT_FAILURE);
        }

        // Set the directory and next pointer for the new node
        newNode->directory = strdup(token);
        newNode->next = NULL;

        // Add the new node to the linked list
        if (head == NULL) {
            head = newNode;
            current = newNode;
        } else {
            current->next = newNode;
            current = newNode;
        }

        // Get the next token
        token = strtok(NULL, ":");
    }

    return head;
}

/**
 * free_path_list - Free the memory allocated for the linked list of directories.
 * @head: Pointer to the head of the linked list.
 */
void free_path_list(list_node *head) {
    while (head != NULL) {
        list_node *temp = head;
        head = head->next;
        free(temp->directory);
        free(temp);
    }
}

int main(void) {
    // Example usage
    list_node *pathList = build_path_list();

    // Print the linked list of directories
    printf("Linked List of PATH Directories:\n");
    list_node *current = pathList;
    while (current != NULL) {
        printf("%s\n", current->directory);
        current = current->next;
    }

    // Free the memory allocated for the linked list
    free_path_list(pathList);

    return 0;
}

