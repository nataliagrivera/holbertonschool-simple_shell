#include "simple_shell.h"

/**
 * execute_command - Execute a command using fork and execve
 * @command: The command to execute
 * @env: The environment variables
 */
void execute_command(char *command, char **env)
{
    char *token = NULL;
    char **tokens = NULL;
    int token_count = 0;

    get_paths();
    token = strtok(command, " \n"); /* Tokenize the command string */
    if (token == NULL)
        return;

    while (token != NULL)
    {
        tokens = realloc(tokens, sizeof(char *) * (token_count + 1));
        if (tokens == NULL)
        {
            perror("realloc");
            return;
        }
        tokens[token_count] = token; /* Store current token in the tokens array */
        token_count++; /* Increment the token count */
        token = strtok(NULL, " \n"); /* Get the next token from the command string */
        tokens[token_count] = NULL; /* Set next element in the array to NULL */
    }

    create_child_process(tokens, env); /* Create child process and execute command */

    free(tokens); /* Free allocated memory */
}


/**
 * create_child_process - Create a child process and execute the command
 * @tokens: The tokenized command and arguments
 * @env: The environment variables
 */
void create_child_process(char **tokens, char **env)
{
    pid_t child_pid = fork(); /* Create a child process */
    if (child_pid == -1)
    {
        perror("fork"); /* Print error message if fork fails */
        return;
    }
    if (child_pid == 0)
    {
        execve(tokens[0], tokens, env); /* Execute the command using execve */
        perror("error "); /* Print an error message if execve fails */
        exit(EXIT_FAILURE); /* Exit child process with failure status */
    }
    else
    {
        wait(NULL); /* Parent process waits for the child process to complete */
    }
}

