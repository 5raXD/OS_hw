/*
 * hw1shell.h
 * Header file for hw1shell - a simple Unix shell implementation
 * 
 * This shell supports:
 * - Internal commands: exit, cd, jobs
 * - External command execution with fork/exec/wait
 * - Foreground and background process management
 * - Up to 4 concurrent background processes
 */

#ifndef HW1SHELL_H
#define HW1SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

/* Maximum limits */
#define CMD_MAX_LENGTH 1024   /* Maximum command line length */
#define ARG_MAX_COUNT 64      /* Maximum number of arguments */
#define MAX_BG_JOBS 4         /* Maximum background jobs */

/* Structure to track background jobs */
typedef struct {
    pid_t pid;                          /* Process ID of background job */
    char command[CMD_MAX_LENGTH];       /* Command string executed */
} BackgroundJob;

/* Global background job tracking */
extern BackgroundJob bgJobs[MAX_BG_JOBS];
extern int activeJobs;


void executeCommand(char *args[], int isBackground, char *originalCmd);

/*
 * printJobs - Display list of currently running background processes
 * Prints: "pid\tcommand" format (one per line)
 */
void printJobs(void);

/*
 * reapFinishedJobs - Non-blocking reap of finished background processes
 * Uses waitpid with WNOHANG to check for finished children
 * Prints "hw1shell: pid %d finished" for each reaped process
 */
void reapFinishedJobs(void);

/*
 * cleanupOnExit - Blocking wait for all remaining background processes
 * Called when shell exits to ensure proper cleanup of all children
 */
void cleanupOnExit(void);

#endif /* HW1SHELL_H */
