#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// Function to handle errors and print error messages
void handle_error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

// Function to allocate memory and check for allocation failure
void *safe_malloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        handle_error("Memory allocation failed");
    }
    return ptr;
}

// Function to duplicate a string and check for allocation failure
char *safe_strdup(const char *s) {
    char *dup = strdup(s);
    if (dup == NULL) {
        handle_error("String duplication failed");
    }
    return dup;
}

// Function to free memory and set pointer to NULL
void safe_free(void **ptr) {
    if (ptr != NULL && *ptr != NULL) {
        free(*ptr);
        *ptr = NULL;
    }
}