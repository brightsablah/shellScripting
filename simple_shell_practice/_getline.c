#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 128

ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

/* Implementation of the _getline function */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream) {
    if (*lineptr == NULL || *n == 0) {
        /* Allocate initial buffer if not provided */
        *n = BUFFER_SIZE;
        *lineptr = (char *)malloc(*n);
        if (*lineptr == NULL) {
            return -1;  /* Memory allocation failure */
        }
    }

    int ch;
    size_t i = 0;

    /* Read characters until a newline or EOF is encountered */
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        /* Check if more space is needed */
        if (i == *n - 1) {
            *n *= 2;
            char *temp = realloc(*lineptr, *n);
            if (temp == NULL) {
                return -1;  /* Memory allocation failure */
            }
            *lineptr = temp;
        }

        /* Store the character */
        (*lineptr)[i++] = (char)ch;
    }

    /* Check if any characters were read */
    if (i == 0 && ch == EOF) {
        return 0;  /* End of file reached */
    }

    /* Null-terminate the string */
    (*lineptr)[i] = '\0';

    return i;  /* Number of characters read */
}
