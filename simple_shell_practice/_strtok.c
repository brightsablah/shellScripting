#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function to find the next token in a string */
char* _strtok(char *str, const char *delimiters);

int main() {
    char sentence[] = "This is a sample sentence.";
    const char delimiters[] = " ";

    char *token = _strtok(sentence, delimiters);

    while (token != NULL) {
        printf("Token: %s\n", token);
        token = _strtok(NULL, delimiters);
    }

    return 0;
}

/* Implementation of the _strtok function */
char* _strtok(char *str, const char *delimiters) {
    static char *nextToken = NULL;  /* Pointer to the next token in the string */

    if (str != NULL) {
        /* If a new string is provided, update the pointer */
        nextToken = str;
    }

    /* Skip leading delimiters */
    while (*nextToken != '\0' && strchr(delimiters, *nextToken) != NULL) {
        ++nextToken;
    }

    if (*nextToken == '\0') {
        return NULL;  /* No more tokens */
    }

    /* Find the end of the current token */
    char *tokenStart = nextToken;
    while (*nextToken != '\0' && strchr(delimiters, *nextToken) == NULL) {
        ++nextToken;
    }

    if (*nextToken != '\0') {
        *nextToken = '\0';  /* Null-terminate the current token */
        ++nextToken;        /* Move to the next character after the delimiter */
    }

    return tokenStart;
}

