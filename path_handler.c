#include "simple_shell.h"

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
