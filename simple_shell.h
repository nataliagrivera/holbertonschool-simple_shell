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
void create_child_process(char **tokens, char **env);
void free_token_array(char **tokens, int token_count);
void free_paths_array(char **paths, int num_paths);
#endif
