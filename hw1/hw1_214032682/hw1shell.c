#include "hw1shell.h"

/* Global background job tracking */
BackgroundJob bgJobs[MAX_BG_JOBS];
int activeJobs = 0;

void executeCommand(char *args[], int isBackground, char *originalCmd) {
    pid_t pid = fork();

    if (pid == -1) {
        printf("hw1shell: fork failed, errno is %d\n", errno);
    } else if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            if (errno != 2) {
                printf("hw1shell: execvp failed, errno is %d\n", errno);
            }
            printf("hw1shell: invalid command\n");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process
        if (isBackground) {
            if (activeJobs < MAX_BG_JOBS) {
                printf("hw1shell: pid %d started\n", pid);
                bgJobs[activeJobs].pid = pid;
                strncpy(bgJobs[activeJobs].command, originalCmd, CMD_MAX_LENGTH - 1);
                bgJobs[activeJobs].command[CMD_MAX_LENGTH - 1] = '\0';
                activeJobs++;
            } else {
                printf("hw1shell: too many background commands running\n");
                waitpid(pid, NULL, 0);  /* kill the forked process */
            }
        } else {
            if (waitpid(pid, NULL, 0) == -1) {
                printf("hw1shell: waitpid failed, errno is %d\n", errno);
            }
        }
    }
}

/* CHANGED: Removed header "PID\tCommand\n" - jobs output should only show pid\tcommand lines */
void printJobs() {
    for (int i = 0; i < activeJobs; i++) {
        printf("%d\t%s\n", bgJobs[i].pid, bgJobs[i].command);
    }
}

void reapFinishedJobs() {
    int status;
    pid_t pid;

    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        printf("hw1shell: pid %d finished\n", pid);

        for (int i = 0; i < activeJobs; i++) {
            if (bgJobs[i].pid == pid) {
                for (int j = i; j < activeJobs - 1; j++) {
                    bgJobs[j] = bgJobs[j + 1];
                }
                activeJobs--;
                break;
            }
        }
    }
}

void cleanupOnExit() {
    int status;
    while (waitpid(-1, &status, 0) > 0) {
        // Wait for all child processes to finish
    }
}

int main() {
    while (1) {
        reapFinishedJobs();
        char input[CMD_MAX_LENGTH];
        char inputCopy[CMD_MAX_LENGTH];  /* for storing original command */
        char *args[ARG_MAX_COUNT];

        // Display the shell prompt
        printf("hw1shell$ ");
        fflush(stdout);

        // Read user input
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\n");  /* EOF on Ctrl-D */
            cleanupOnExit();
            exit(EXIT_SUCCESS);
        }

        // Trim newline character
        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) == 0) {
            continue;  // Skip empty commands
        }

        /* save original command before tokenizing */
        strncpy(inputCopy, input, CMD_MAX_LENGTH - 1);
        inputCopy[CMD_MAX_LENGTH - 1] = '\0';

        // Tokenize input into arguments
        char *token = strtok(input, " ");
        int argCount = 0;

        while (token != NULL && argCount < ARG_MAX_COUNT - 1) {
            args[argCount++] = token;
            token = strtok(NULL, " ");
        }
        args[argCount] = NULL;  // Null-terminate the arguments array

        if (argCount == 0) continue;

        if (strcmp(args[0], "&") == 0) {
            printf("hw1shell: invalid command\n");
            continue;
        }

        // Check for background command
        int isBackground = 0;
        if (argCount > 0 && strcmp(args[argCount - 1], "&") == 0) {
            isBackground = 1;
            args[argCount - 1] = NULL;  // Remove "&" from arguments
            /* remove & from stored command */
            char *amp = strrchr(inputCopy, '&');
            if (amp) *amp = '\0';
            /* trim trailing space */
            /* CHANGED: Also trim tabs, not just spaces */
            while (strlen(inputCopy) > 0 && 
                   (inputCopy[strlen(inputCopy)-1] == ' ' || 
                    inputCopy[strlen(inputCopy)-1] == '\t')) {
                inputCopy[strlen(inputCopy)-1] = '\0';
            }
        }

        reapFinishedJobs();

        // Internal commands
        if (strcmp(args[0], "exit") == 0) {
            cleanupOnExit();
            exit(EXIT_SUCCESS);
        } else if (strcmp(args[0], "cd") == 0) {
            /* CHANGED: Added check for argCount < 2 to prevent accessing invalid args[1] */
            if (argCount < 2) {
                printf("hw1shell: invalid command\n");
            } else if (chdir(args[1]) != 0) {
                printf("hw1shell: chdir failed, errno is %d\n", errno);
                printf("hw1shell: invalid command\n");
            }
        } else if (strcmp(args[0], "jobs") == 0) {
            printJobs();
        } else {
            executeCommand(args, isBackground, inputCopy);
        }

        reapFinishedJobs();
    }

    return 0;
}