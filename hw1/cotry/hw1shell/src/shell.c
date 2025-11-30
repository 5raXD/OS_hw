#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

#define MAX_CMD_LENGTH 1024
#define MAX_ARG_LENGTH 100
#define MAX_ARGS 10

void execute_command(char *input);
void handle_builtin_commands(char **args);
void add_job(pid_t pid, char *cmd);
void remove_job(pid_t pid);
void list_jobs();

typedef struct Job {
    pid_t pid;
    char cmd[MAX_CMD_LENGTH];
    struct Job *next;
} Job;

Job *job_list = NULL;

int main() {
    char input[MAX_CMD_LENGTH];

    while (1) {
        printf("hw1shell> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break; // Exit on EOF
        }

        // Remove trailing newline
        input[strcspn(input, "\n")] = 0;

        execute_command(input);
    }

    return 0;
}

void execute_command(char *input) {
    char *args[MAX_ARGS];
    char *token = strtok(input, " ");
    int i = 0;

    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    if (args[0] == NULL) {
        return; // Empty command
    }

    if (strcmp(args[0], "exit") == 0 || strcmp(args[0], "cd") == 0 || strcmp(args[0], "jobs") == 0) {
        handle_builtin_commands(args);
    } else {
        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            execvp(args[0], args);
            perror("execvp failed");
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            // Parent process
            int status;
            waitpid(pid, &status, 0);
        } else {
            perror("fork failed");
        }
    }
}

void handle_builtin_commands(char **args) {
    if (strcmp(args[0], "exit") == 0) {
        exit(0);
    } else if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            fprintf(stderr, "cd: missing argument\n");
        } else if (chdir(args[1]) != 0) {
            perror("cd failed");
        }
    } else if (strcmp(args[0], "jobs") == 0) {
        list_jobs();
    }
}

void add_job(pid_t pid, char *cmd) {
    Job *new_job = malloc(sizeof(Job));
    new_job->pid = pid;
    strncpy(new_job->cmd, cmd, MAX_CMD_LENGTH);
    new_job->next = job_list;
    job_list = new_job;
}

void remove_job(pid_t pid) {
    Job **current = &job_list;
    while (*current) {
        if ((*current)->pid == pid) {
            Job *to_remove = *current;
            *current = to_remove->next;
            free(to_remove);
            return;
        }
        current = &(*current)->next;
    }
}

void list_jobs() {
    Job *current = job_list;
    while (current) {
        printf("[%d] %s\n", current->pid, current->cmd);
        current = current->next;
    }
}