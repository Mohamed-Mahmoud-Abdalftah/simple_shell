#include "main.h"

/**
 * my_exit - function to handle exit command
 * @args: arguments
 */

void my_exit(char **args)
{
	int stat_val = 0;
	char *msg;

	if (args[1] != NULL)
	{
		if (_strtol(args[1], &stat_val) != 0 || stat_val < 0 || stat_val > 255)
		{
			msg = "exit: invalid status\n";
			write(STDERR_FILENO, msg, _strlen(msg));
			return;
		}
	}
	exit(stat_val);
}
