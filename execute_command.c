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
		tokens[token_count] = strdup(token); /* Store current token in the tokens array */
		token_count++;						 /* Increment the token count */
		token = strtok(NULL, " \n");		 /* Get the next token from the command string */
	}
	tokens = realloc(tokens, sizeof(char *) * (token_count + 1));
	if (tokens == NULL)
	{
		perror("realloc");
		return;
	}
	tokens[token_count] = NULL; /* Set next element in the array to NULL */

	create_child_process(tokens, env); /* Create child process and execute command */

	free_token_array(tokens, token_count); /* Free allocated memory */
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
		perror("error ");				/* Print an error message if execve fails */
		exit(EXIT_FAILURE);				/* Exit child process with failure status */
	}
	else
	{
		wait(NULL); /* Parent process waits for the child process to complete */
	}
}

/**
 * get_paths - Extracts paths from the PATH environment variable
 * Return: A pointer to an array of strings containing the paths
 *         NULL on failure or if PATH is not found
 */
char **get_paths(void)
{
	/* Get the value of the PATH environment variable */
	char *path_env = getenv("PATH");
	char *token = NULL;
	int num_paths = 0;
	char **paths = NULL;

	/* Check if PATH environment variable exists */
	if (path_env == NULL)
	{
		perror("error ");
		return (NULL);
	}

	token = strtok(path_env, ":");
	while (token != NULL)
	{
		/* Allocate memory for the new path in the array */
		paths = realloc(paths, sizeof(char *) * (num_paths + 1));
		if (paths == NULL)
		{
			perror("error ");
			free_paths_array(paths, num_paths);
			return (NULL);
		}

		paths[num_paths] = strdup(token); /* Store the current path in the array */
		num_paths++;					  /* Increment the num_paths counter. */
		token = strtok(NULL, ":");		  /* Move to the next token */
	}
	paths = realloc(paths, sizeof(char *) * (num_paths + 1));
	if (paths == NULL)
	{
		perror("error ");
		free_paths_array(paths, num_paths);
		return (NULL);
	}
	paths[num_paths] = NULL; /* Add NULL pointer at the end of the array */

	free(path_env); /* Free the environment variable string */
	return (paths);
}
