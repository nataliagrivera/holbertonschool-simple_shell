#include "simple_shell.h"

/**
 * main - Entry point for the simple shell program
 * @ac: The argument count (unused)
 * @av: The argument vector (unused)
 * @env: The environment variables
 * Return: Always 0
 */
int main(int ac, char **av, char **env)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int non_interactive_mode = isatty(STDIN_FILENO) == 0;

	if (non_interactive_mode)
	{
		handle_non_interactive_mode(env);
	}
	else
	{
		while (1)
		{
			(void)ac; /* Suppress unused parameter warning */
			(void)av; /* Suppress unused parameter warning */

			printf("($) ");						/* Display the shell prompt */
			read = getline(&line, &len, stdin); /* Read user input */

			if (read == -1)
				break;
			if (line[read - 1] == '\n')
				line[read - 1] = '\0'; /* Remove newline character */

			if (strcmp(line, "exit") == 0)
				break;

			if (isspace((unsigned char)line[0]))
				continue;

			if (line[0] == '\0' || line[0] == ' ')
				continue;

			execute_command(line, env); /* Execute the command entered by user */
		}
	}
	return (0);
}


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
	char *line = NULL; /* Stores the input line */
	size_t len = 0;	   /* Initial size for getline() */
	ssize_t read;	   /* Stores the number of characters read */

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
