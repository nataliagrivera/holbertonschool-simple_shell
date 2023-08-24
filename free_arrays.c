#include "simple_shell.h"

/**
 * free_token_array - Frees memory allocated for token array and token strings
 * @tokens: The token array to be freed
 * @token_count: The number of tokens in the array
 */
void free_token_array(char **tokens, int token_count)
{
	int i;

	for (i = 0; i < token_count; i++)
	{
		free(tokens[i]);
	}
	free(tokens);
}

/**
 * free_paths_array - Frees memory allocated for the paths array
 * @paths: The paths array to be freed
 * @num_paths: The number of paths in the array
 */
void free_paths_array(char **paths, int num_paths)
{
	int i;

	for (i = 0; i < num_paths; i++)
	{
		free(paths[i]);
	}
	free(paths);
}
