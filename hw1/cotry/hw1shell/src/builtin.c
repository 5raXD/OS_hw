#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

void shell_exit() {
    exit(0);
}

void shell_cd(char *path) {
    if (path == NULL || chdir(path) != 0) {
        perror("cd failed");
    }
}

void shell_jobs() {
    // This function will list background jobs.
    // Implementation will depend on how jobs are tracked in the jobs.c file.
    printf("Jobs functionality not implemented yet.\n");
}