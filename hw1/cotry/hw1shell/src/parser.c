#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

#define MAX_COMMANDS 100
#define MAX_ARGS 100

char **parse_input(char *input) {
    char **commands = malloc(MAX_COMMANDS * sizeof(char *));
    char *command;
    int i = 0;

    command = strtok(input, ";\n");
    while (command != NULL && i < MAX_COMMANDS) {
        commands[i] = malloc((strlen(command) + 1) * sizeof(char));
        strcpy(commands[i], command);
        command = strtok(NULL, ";\n");
        i++;
    }
    commands[i] = NULL; // Null-terminate the array of commands
    return commands;
}

char **parse_command(char *command) {
    char **args = malloc(MAX_ARGS * sizeof(char *));
    char *arg;
    int i = 0;

    arg = strtok(command, " \t\n");
    while (arg != NULL && i < MAX_ARGS) {
        args[i] = malloc((strlen(arg) + 1) * sizeof(char));
        strcpy(args[i], arg);
        arg = strtok(NULL, " \t\n");
        i++;
    }
    args[i] = NULL; // Null-terminate the array of arguments
    return args;
}

void free_parsed_commands(char **commands) {
    for (int i = 0; commands[i] != NULL; i++) {
        free(commands[i]);
    }
    free(commands);
}

void free_parsed_args(char **args) {
    for (int i = 0; args[i] != NULL; i++) {
        free(args[i]);
    }
    free(args);
}