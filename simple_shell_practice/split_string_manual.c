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

/* Function to split a string into an array of words without using strtok */
char** splitString(const char *inputString, size_t *wordCount) {
    if (inputString == NULL || wordCount == NULL) {
        return NULL;  /* Invalid input parameters */
    }

    /* Count the number of words in the string */
    *wordCount = 0;
    int inWord = 0;

    /* First pass: count the number of words */
    for (size_t i = 0; inputString[i] != '\0'; ++i) {
        if (inputString[i] == ' ' || inputString[i] == '\t' || inputString[i] == '\n') {
            inWord = 0;
        } else if (inWord == 0) {
            inWord = 1;
            ++(*wordCount);
        }
    }

    /* Allocate memory for the array of words */
    char **words = (char **)malloc(*wordCount * sizeof(char *));
    if (words == NULL) {
        return NULL;  /* Memory allocation failure */
    }

    size_t index = 0;
    size_t wordStart = 0;

    /* Second pass: extract and store each word in the array */
    for (size_t i = 0; inputString[i] != '\0'; ++i) {
        if (inputString[i] == ' ' || inputString[i] == '\t' || inputString[i] == '\n') {
            if (wordStart < i) {
                size_t wordLength = i - wordStart;
                words[index] = (char *)malloc((wordLength + 1) * sizeof(char));
                if (words[index] == NULL) {
                    /* Memory allocation failure, clean up and return NULL */
                    for (size_t j = 0; j < index; ++j) {
                        free(words[j]);
                    }
                    free(words);
                    return NULL;
                }
                strncpy(words[index], inputString + wordStart, wordLength);
                words[index][wordLength] = '\0';
                ++index;
            }
            wordStart = i + 1; /* Start of the next word */
        }
    }

    /* Check if there is a last word at the end of the string */
    if (wordStart < strlen(inputString)) {
        size_t wordLength = strlen(inputString) - wordStart;
        words[index] = (char *)malloc((wordLength + 1) * sizeof(char));
        if (words[index] == NULL) {
            /* Memory allocation failure, clean up and return NULL */
            for (size_t j = 0; j < index; ++j) {
                free(words[j]);
            }
            free(words);
            return NULL;
        }
        strncpy(words[index], inputString + wordStart, wordLength);
        words[index][wordLength] = '\0';
    }

    return words;
}

