#ifndef HW1SHELL_H
#define HW1SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>


#define CMD_MAX_LENGTH 1024   // Maximum command line length 
#define ARG_MAX_COUNT 64      // Maximum number of arguments
#define MAX_BG_JOBS 4         // Maximum background jobs

typedef struct {
    pid_t pid;
    char command[CMD_MAX_LENGTH];
} BackgroundJob;


extern BackgroundJob bgJobs[MAX_BG_JOBS];
extern int activeJobs;


void executeCommand(char *args[], int isBackground, char *originalCmd);
void printJobs(void);
void reapFinishedJobs(void);
void cleanupOnExit(void);
#endif
