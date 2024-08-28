#include "main.h"

/**
 * execute_command - function to execute command
 * @command: command to execute
 * Return: 0 if succesfull and _1 if failed
 */

int execute_command(char *command)
{
	char *argv[MAX_ARGS];
	int argc = parse_command(command, argv);
	char *command1 = argv[0], *path;

	if (command1 == NULL)
		return (-1);
	if (_strcmp(command1, "env") == 0)
		print_environ();
	else if (_strcmp(command1, "echo") == 0)
	{
		echo(argv[1]);
		return (0);
	}
	else if (_strcmp(command1, "cd") == 0)
		handle_cd(argv);
	else if (_strcmp(command1, "exit") == 0)
		exit(0);
	else if (_strcmp(command1, "setenv") == 0)
	{
		_setenv(argv[1], argv[2]);
		return (0);
	}
	else if (_strcmp(command1, "unsetenv") == 0)
	{
		if (argc > 1)
			_unsetenv(argv[1]);
			return (0);
	}
	else
	{
		if (command1[0] == '/')
			path = _strdup(command1);
		else
		{
			path = search_command(command1);
			if (path == NULL)
			{
				perror("path");
				return (-1);
			}
		}
		run_command(path, argv, NULL);
		free(path);
	}

	return (0);
}
/**
 * parse_command - function that parses commands
 * @command: command
 * @argv: arguments
 *
 * Return: arguments
 */
int parse_command(char *command, char *argv[])
{
	int argc = 0;

	argv[argc] = _strtok(command, " ");
	while (argv[argc] != NULL && argc < MAX_ARGS - 1)
	{
		argc++;
		argv[argc] = _strtok(NULL, " ");
	}
	argv[argc] = NULL; /* NULL terminate argument list */

	return (argc);
}
