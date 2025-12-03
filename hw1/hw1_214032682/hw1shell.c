#include "hw1shell.h"
BackgroundJob bgJobs[MAX_BG_JOBS];
int activeJobs = 0;
void executeCommand(char *args[], int isBackground, char *originalCmd) {
    pid_t pid = fork();
    if (pid == -1) {//i think fork filed i do not know if this happens for something else
        fprintf(stderr,"hw1shell: %s failed, errno is %d\n", "fork", errno);
    } else if (pid == 0) { // Child process
        if (execvp(args[0], args) == -1) {
            fprintf(stderr, "hw1shell: invalid command\n");
            exit(EXIT_FAILURE);
        }
    } else {
        if (isBackground) { // Parent process
            if (activeJobs < MAX_BG_JOBS) {
                printf("[Background job started] pid: %d\n", pid);
                bgJobs[activeJobs].pid = pid;
                strncpy(bgJobs[activeJobs].command, originalCmd, CMD_MAX_LENGTH - 1);
                bgJobs[activeJobs].command[CMD_MAX_LENGTH - 1] = '\0';
                activeJobs++;
            } else {
                fprintf(stderr,"hw1shell: too many background commands running\n");
                waitpid(pid, NULL, 0);
            }
        } else {
            int status;
            pid_t result = waitpid(pid, &status, 0);
            if (result == -1) {
                fprintf(stderr,"hw1shell: %s failed, errno is %d\n", "waitpid", errno);
            }
        }
    }
}
void printJobs() {
    for (int i = 0; i < activeJobs; i++) {
        printf("%d\t%s\n", bgJobs[i].pid, bgJobs[i].command);
    }
}
void reapFinishedJobs() {
    int status;
    pid_t pid;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        printf("[Background job finished] pid: %d\n", pid);

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
    while (waitpid(-1, &status, 0) > 0) { // wait for all children
    }
}
int main() {
    while (1) {
        reapFinishedJobs();
        char input[CMD_MAX_LENGTH];
        char inputCopy[CMD_MAX_LENGTH];
        char *args[ARG_MAX_COUNT];
        printf("hw1shell$ ");
        fflush(stdout);
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\n");
            cleanupOnExit();
            exit(EXIT_SUCCESS);//i should chesk if it is better to do break here to exit the while
        }
        input[strcspn(input, "\n")] = '\0';
        if (strlen(input) == 0) {
            continue;  //empty
        }
        strncpy(inputCopy, input, CMD_MAX_LENGTH - 1);
        inputCopy[CMD_MAX_LENGTH - 1] = '\0';
        char *token = strtok(input, " ");
        int argCount = 0;

        while (token != NULL && argCount < ARG_MAX_COUNT - 1) {
            args[argCount++] = token;
            token = strtok(NULL, " ");
        }
        args[argCount] = NULL;  // Null
        if (argCount == 0) continue;
        if (strcmp(args[0], "&") == 0) {
            printf("hw1shell: invalid command\n");
            continue;
        }
        int isBackground = 0;
        if (argCount > 0 && strcmp(args[argCount - 1], "&") == 0) { // if background
            isBackground = 1;
            args[argCount - 1] = NULL;  // remove "&"
                argCount--;
            char *amp = strrchr(inputCopy, '&');
            if (amp) *amp = '\0';
            while (strlen(inputCopy) > 0 && 
                   (inputCopy[strlen(inputCopy)-1] == ' ' || 
                    inputCopy[strlen(inputCopy)-1] == '\t')) {
                inputCopy[strlen(inputCopy)-1] = '\0';
            }
        }
        reapFinishedJobs();
        if (strcmp(args[0], "exit") == 0) {
            cleanupOnExit();
            exit(EXIT_SUCCESS);
        } else if (strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL || args[2] != NULL) {
                fprintf(stderr, "hw1shell: invalid command\n");
            } else {
                if (chdir(args[1]) == -1) {
                    fprintf(stderr, "hw1shell: %s failed, errno is %d\n", "chdir", errno);
                }
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