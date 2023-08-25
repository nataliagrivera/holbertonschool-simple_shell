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
	char *trimmed_line;

	while (1)
	{
		if (isatty(0))
			write(STDOUT_FILENO, "$ ", 2);

		(void)ac; /* Suppress unused parameter warning */
		(void)av; /* Suppress unused parameter warning */

		read = getline(&line, &len, stdin); /* Read user input */

		if (read == -1)
			break;

		/* Trim leading and trailing whitespace */
		trimmed_line = trim_whitespace(line);

		if (strcmp(trimmed_line, "exit") == 0)
			{
				free(line);
				return (2);
			}

		if (trimmed_line[0] == '\0')
			continue;

		execute_command(trimmed_line, env); /* Execute the command entered by user */
	}

	free(line); /* Free allocated memory */
	return (0); /* Exit the shell */
}

/**
 * trim_whitespace - Remove leading and trailing whitespace from a string
 * @str: The string to trim
 * Return: A pointer to the trimmed string
 */
char *trim_whitespace(char *str)
{
	char *start = str;				   /* Pointer to the start of the string */
	char *end = str + strlen(str) - 1; /* Pointer to the end of the string */

	/* Remove leading whitespace */
	while (isspace((unsigned char)*start))
		start++;

	/* Remove trailing whitespace */
	while (end > start && isspace((unsigned char)*end))
		end--;

	/* Null-terminate the trimmed string */
	end[1] = '\0';

	return (start); /* Return the trimmed string */
}
