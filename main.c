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

	/* Main loop to keep the shell running */
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

	free(line); /* Free allocated memory */
	return (0); /* Exit the shell */
}
