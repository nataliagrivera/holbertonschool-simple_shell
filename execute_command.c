#include "simple_shell.h"

/**
 * get_command_path - Get the full path of a command
 * @command_name: The name of the command
 * Return: A dynamically allocated string containing the full path
 *         NULL if the command is not found
 */
char *get_command_path(char *command_name)
{
	char *command_path = "/bin/";
	char *full_path;

	if (access(command_name, X_OK) == 0)
	{
		full_path = strdup(command_name);
		if (full_path == NULL)
		{
			perror("malloc");
			return (NULL);
		}
		return (full_path);
	}

	full_path = malloc(strlen(command_path) + strlen(command_name) + 1);
	if (full_path == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	sprintf(full_path, "%s%s", command_path, command_name);

	/* Check if the full path is executable */
	if (access(full_path, X_OK) != 0)
	{
		perror("Command not found");
		free(full_path);
		return (NULL);
	}

	return (full_path);
}

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
		tokens[token_count] = strdup(token); /* Store token in tokens array */
		token_count++;						 /* Increment the token count */
		token = strtok(NULL, " \n");		 /* Get next token from command string */
	}
	tokens = realloc(tokens, sizeof(char *) * (token_count + 1));
	if (tokens == NULL)
	{
		perror("realloc");
		return;
	}
	tokens[token_count] = NULL; /* Set next element in the array to NULL */

	full_path = get_command_path(tokens[0]); /* Get the full path of the command */
	if (full_path == NULL)
	{
		free_token_array(tokens, token_count);
		return;
	}

	free(tokens[0]);
	tokens[0] = full_path;
	create_child_process(tokens, env);
	free_token_array(tokens, token_count);
}

/**
 * create_child_process - Create a child process and execute the command
 * @tokens: The tokenized command and arguments
 * @env: The environment variables
 */
void create_child_process(char **tokens, char **env)
{
	pid_t child_pid = fork(); /* Create a child process */
	int status;

	if (child_pid == -1)
	{
		perror("fork"); /* Print error message if fork fails */
		return;
	}
	if (child_pid == 0)
	{
		if (strcmp(tokens[0], "exit") == 0)
			exit(2);                                                     /* Set exit status to 2 for the "exit" command */
			
		execve(tokens[0], tokens, env);									 /* Execute the command using execve */
		perror("error ");												 /* Print an error message if execve fails */
		exit(EXIT_FAILURE); /* Exit child process with failure status */ /* Exit child process with failure status */
	}
	else
	{
		/* Wait specifically for the child process to complete */
		waitpid(child_pid, &status, 0);
	}
}
