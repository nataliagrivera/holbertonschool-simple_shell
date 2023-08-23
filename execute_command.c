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
	char *full_path;
	char **paths = get_paths();

	if (paths == NULL)
		return;

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
		token_count++;				 /* Increment the token count */
		token = strtok(NULL, " \n"); /* Get the next token from the command string */
		tokens[token_count] = NULL;	 /* Set next element in the array to NULL */
	}

	full_path = construct_full_path(tokens[0], paths);
	if (full_path != NULL)
	{
		create_child_process(tokens, env, full_path);
		free(full_path);
	}
	else
	{
		printf("Command not found: %s\n", tokens[0]);
	}

	free(tokens);
}

/**
 * create_child_process - Create a child process and execute the command
 * @tokens: The tokenized command and arguments
 * @full_path: path concat
 * @env: The environment variables
 */
void create_child_process(char **tokens, char **env, char *full_path)
{
	pid_t child_pid;

	child_pid = fork(); /* Create a child process */
	if (child_pid == -1)
	{
		perror("fork"); /* Print error message if fork fails */
		return;
	}
	if (child_pid == 0)
	{
		execve(full_path, tokens, env); /* Execute the command using execve */
		perror("error ");				/* Print an error message if execve fails */
		exit(EXIT_FAILURE);				/* Exit child process with failure status */
	}
	else
	{
		wait(NULL); /* Parent process waits for the child process to complete */
	}
}

/**
 * construct_full_path - Constructs full path for command using available paths
 * @command: The command for which to construct the full path
 * @paths: An array of paths to search for the command
 * Return: A dynamically allocated string containing the full path,
 *         or NULL if the command is not found in any of the paths
 */
char *construct_full_path(char *command, char **paths)
{
	int i = 0;
	char *full_path = NULL;

	while (paths[i] != NULL)
	{
		/* Allocate memory for the potential full path */
		full_path = malloc(strlen(paths[i]) + strlen(command) + 2);
		if (full_path == NULL)
		{
			perror("malloc");
			return (NULL);
		}
		if (access(command, X_OK) == -1)
		{
			/* Construct the full path by concatenating the path and command */
			strcpy(full_path, paths[i]);
			strcat(full_path, "/");
			strcat(full_path, command);

			/* Check if the potential path is executable */
			if (access(full_path, X_OK) == 0)
				return (full_path); /* Return the valid full path */

			/* Free memory and move to the next path */
			free(full_path);
			i++;
		}
		else
			return (command);
	}

	return (NULL); /* Command not found in any path */
}
/**
 * get_paths - Extracts paths from the PATH environment variable
 * Return: A pointer to an array of strings containing the paths
 *         NULL on failure or if PATH is not found
 */
char **get_paths(void)
{
	/* Get the value of the PATH environment variable */
	char *path_env = NULL;
	char *token = NULL;
	int num_paths = 0;
	char **paths = NULL;

	path_env = getenv("PATH");
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
			free(paths);
			return (NULL);
		}

		paths[num_paths] = token; /* Store the current path in the array */
		num_paths++;			  /* You increment the num_paths counter.*/
		token = strtok(NULL, ":"); /* Move to the next token */
	}

	/* Add a NULL pointer at the end to terminate the array */
	paths = realloc(paths, sizeof(char *) * (num_paths + 1));
	paths[num_paths] = NULL;

	return (paths);
}
