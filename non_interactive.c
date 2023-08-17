#include "simple_shell.h"

/**
 * handle_non_interactive_mode - Handles the non-interactive mode of the shell
 * @env: The environment variables
 *
 * This function is responsible for handling input and executing commands
 * when the shell is running in non-interactive mode 
 * It reads input lines, processes them, and executes commands as needed.
 *
 * @env: The environment variables passed to the executed commands
 */
void handle_non_interactive_mode(char **env)
{
    char *line = NULL;     /* Stores the input line */
    size_t len = 0;        /* Initial size for getline() */
    ssize_t read;          /* Stores the number of characters read */

    /* Loop to read and process input lines in non-interactive mode */
    while ((read = getline(&line, &len, stdin)) != -1)
    {
        /* Remove newline character from input line if present */
        if (read > 0 && line[read - 1] == '\n')
            line[read - 1] = '\0';

        /* Check if the user wants to exit the shell */
        if (strcmp(line, "exit") == 0)
            break;

        /* Skip processing if the input line is empty or starts with a space */
        if (line[0] == '\0' || line[0] == ' ')
            continue;

        /* Execute the command specified in the input line */
        execute_command(line, env);
    }

    free(line); /* Free the allocated memory for the input line */
}
