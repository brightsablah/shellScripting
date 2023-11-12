#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function to split a string into an array of words */
char** splitString(const char *inputString, size_t *wordCount);

int main() {
    const char *sentence = "This is a sample sentence.";

    size_t wordCount;
    char** words = splitString(sentence, &wordCount);

    if (words != NULL) {
        printf("Original sentence: %s\n", sentence);
        printf("Number of words: %zu\n", wordCount);
        printf("Words:\n");

        for (size_t i = 0; i < wordCount; ++i) {
            printf("%zu: %s\n", i + 1, words[i]);
        }

        /* Free the allocated memory for each word */
        for (size_t i = 0; i < wordCount; ++i) {
            free(words[i]);
        }

        /* Free the array of words */
        free(words);
    } else {
        printf("Error splitting the string.\n");
    }

    return 0;
}

/* Function to split a string into an array of words */
char** splitString(const char *inputString, size_t *wordCount) {
    if (inputString == NULL || wordCount == NULL) {
        return NULL;  /* Invalid input parameters */
    }

    /* Make a copy of the input string as strtok modifies the input string */
    char *copy = strdup(inputString);
    if (copy == NULL) {
        return NULL;  /* Memory allocation failure */
    }

    /* Count the number of words in the string */
    *wordCount = 0;
    char *token = strtok(copy, " ");  /* Assume words are separated by space */
    while (token != NULL) {
        ++(*wordCount);
        token = strtok(NULL, " ");
    }

    /* Allocate memory for the array of words */
    char **words = (char **)malloc(*wordCount * sizeof(char *));
    if (words == NULL) {
        free(copy);
        return NULL;  /* Memory allocation failure */
    }

    /* Reset copy to the beginning of the string for tokenization */
    strcpy(copy, inputString);

    /* Tokenize the string and store each word in the array */
    size_t index = 0;
    token = strtok(copy, " ");
    while (token != NULL) {
        words[index] = strdup(token);
        if (words[index] == NULL) {
            /* Memory allocation failure, clean up and return NULL */
            for (size_t i = 0; i < index; ++i) {
                free(words[i]);
            }
            free(words);
            free(copy);
            return NULL;
        }
        ++index;
        token = strtok(NULL, " ");
    }

    /* Free the temporary copy of the input string */
    free(copy);

    return words;
}

