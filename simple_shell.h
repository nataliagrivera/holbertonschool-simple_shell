#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

int main(int ac, char **av, char **env);
void execute_command(char *command, char **env);
char **get_paths(void);
void handle_non_interactive_mode(char **env);
char *find_executable_path(char **paths, const char *command);
void create_child_process(char **tokens, char **env, const char *exec_path);
void concatenate_path(const char *path, const char *command, char *exec_path);
#endif
