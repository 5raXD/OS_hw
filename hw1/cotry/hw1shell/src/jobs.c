#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

#define MAX_JOBS 1024

typedef struct {
    pid_t pid;
    char command[256];
    int status; // 0 for running, 1 for stopped, 2 for completed
} Job;

static Job jobs[MAX_JOBS];
static int job_count = 0;

void add_job(pid_t pid, const char *command) {
    if (job_count < MAX_JOBS) {
        jobs[job_count].pid = pid;
        strncpy(jobs[job_count].command, command, sizeof(jobs[job_count].command) - 1);
        jobs[job_count].command[sizeof(jobs[job_count].command) - 1] = '\0';
        jobs[job_count].status = 0; // running
        job_count++;
    } else {
        fprintf(stderr, "Job limit reached.\n");
    }
}

void remove_job(pid_t pid) {
    for (int i = 0; i < job_count; i++) {
        if (jobs[i].pid == pid) {
            jobs[i] = jobs[job_count - 1]; // replace with last job
            job_count--;
            return;
        }
    }
}

void update_job_status(pid_t pid, int status) {
    for (int i = 0; i < job_count; i++) {
        if (jobs[i].pid == pid) {
            jobs[i].status = status;
            return;
        }
    }
}

void list_jobs() {
    for (int i = 0; i < job_count; i++) {
        printf("[%d] %s (PID: %d) - %s\n", i + 1, jobs[i].command, jobs[i].pid,
               jobs[i].status == 0 ? "Running" : (jobs[i].status == 1 ? "Stopped" : "Completed"));
    }
}

void handle_completed_jobs() {
    for (int i = 0; i < job_count; i++) {
        int status;
        pid_t result = waitpid(jobs[i].pid, &status, WNOHANG);
        if (result == jobs[i].pid) {
            if (WIFEXITED(status)) {
                update_job_status(jobs[i].pid, 2); // completed
            } else if (WIFSTOPPED(status)) {
                update_job_status(jobs[i].pid, 1); // stopped
            }
        }
    }
}