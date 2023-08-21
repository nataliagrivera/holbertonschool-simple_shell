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
#endif
