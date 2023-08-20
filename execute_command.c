#include "simple_shell.h"

/**
 * create_child_process - Create and execute a child process
 * @tokens: Array of tokens from the command
 * @env: Environment variables
 * @exec_path: Path of the executable to execute
 */
void create_child_process(char **tokens, char **env, const char *exec_path)
{
	/* Create a child process */
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		/* Fork error */
		perror("fork");
		return;
	}

	if (child_pid == 0)
	{
		/* Child process: execute the command */
		execve(exec_path, tokens, env);
		perror("error ");
		exit(EXIT_FAILURE);
	}
	else
	{
		/* Parent process: wait for the child to complete */
		wait(NULL);
	}
}

/**
 * execute_command - Execute a command
 * @command: The command to execute
 * @env: Environment variables
 */
void execute_command(char *command, char **env)
{
	char *token, **tokens = NULL;
	int token_count = 0;
	char **paths = get_paths();
	char *exec_path;

	token = strtok(command, " \n");
	if (token == NULL)
		return;

	while (token != NULL)
	{
		/* Tokenize the command string */
		tokens = realloc(tokens, sizeof(char *) * (token_count + 1));
		if (tokens == NULL)
		{
			/* Memory allocation error */
			perror("realloc");
			return;
		}
		tokens[token_count] = token; /* Store current token in the tokens array */
		token_count++;				 /* Increment the token count */
		token = strtok(NULL, " \n"); /* Get the next token from the command string */
		tokens[token_count] = NULL;	 /* Set next element in the array to NULL */
	}

	exec_path = find_executable_path(paths, tokens[0]);

	if (exec_path != NULL)
	{
		/* Execute the command using the found executable path */
		create_child_process(tokens, env, exec_path);
		free(exec_path);
	}

	free(paths);
	free(tokens);
}

/**
 * find_executable_path - Find the executable path for a command
 * @paths: Paths to search for the executable
 * @command: The command to search for
 * Return: The executable path if found, otherwise NULL
 */
char *find_executable_path(char **paths, const char *command)
{
	char *path_copy;
	char *exec_path;
	int i;

	if (access(command, X_OK) == 0) /* Checks if the file is executable */
	{
		/* Check if the command is already an absolute path */
		path_copy = strdup(command);
		if (path_copy == NULL)
		{
			/* Memory allocation error */
			perror("strdup");
			free(path_copy);
			return (NULL);
		}
		return (path_copy);
	}

	for (i = 0; paths[i] != NULL; i++)
	{
		/* Loop through paths and concatenate to find the executable */
		exec_path = malloc(strlen(paths[i]) + strlen(command) + 2);
		if (exec_path == NULL)
		{
			/* Memory allocation error */
			perror("malloc");
			break;
		}
		concatenate_path(paths[i], command, exec_path);

		if (access(exec_path, X_OK) == 0)
			return (exec_path);

		free(exec_path);
	}

	return (NULL);
}

/**
 * concatenate_path - Concatenate a path and a command
 * @path: The path to concatenate
 * @command: The command to append
 * @exec_path: The resulting concatenated path
 */
void concatenate_path(const char *path, const char *command, char *exec_path)
{
	/* Concatenate the path and command to create the full path */
	strcpy(exec_path, path);
	strcat(exec_path, "/");
	strcat(exec_path, command);
}
