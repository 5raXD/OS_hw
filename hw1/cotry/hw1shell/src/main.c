#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

#define MAX_INPUT_SIZE 1024

int main() {
    char input[MAX_INPUT_SIZE];

    while (1) {
        printf("hw1shell> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            perror("fgets failed");
            continue;
        }

        // Remove newline character from input
        input[strcspn(input, "\n")] = 0;

        // Process the input command
        if (strcmp(input, "exit") == 0) {
            break;
        }

        // Call the function to execute the command
        execute_command(input);
    }

    return 0;
}