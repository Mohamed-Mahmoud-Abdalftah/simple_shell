#include "main.h"

/**
 * split_line - function to tokenize arguments
 * @line: line
 *
 * Return: tokens
 */
char **split_line(char *line)
{
	int bufsize = BUFFER_SIZE, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		perror("simple_shell: allocation error");
		exit(EXIT_FAILURE);
	}

	token = _strtok(line, DELIMITERS);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += BUFFER_SIZE;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				perror("simple_shell: allocation error");
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, DELIMITERS);
	}
	tokens[position] = NULL;

	return (tokens);
} 
