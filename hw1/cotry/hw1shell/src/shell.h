#ifndef SHELL_H
#define SHELL_H

// Function prototypes for the shell
void execute_command(char *command);
void change_directory(char *path);
void exit_shell();
void list_jobs();
void parse_input(char *input, char **commands);
void handle_background_processes();

#endif // SHELL_H