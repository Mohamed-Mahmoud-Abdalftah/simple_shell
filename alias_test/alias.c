#include "main.h"

/**
 * alias - function that gets commands from arguments
 * @argc: arguments
 * @argv: pointer to arguments
 */

void alias(int argc, char *argv[])
{
	char *equal_sign;
	int i;
	const char *msg;

	if (argc == 1)
	{
		/* No arguments: print all aliases */
		print_aliases();
	}
	else if (argc > 1)
	{
		if (strchr(argv[1], '=') != NULL)
		{
			/* Define or update aliases */
			for (i = 1; i < argc; ++i)
			{
				equal_sign = strchr(argv[i], '=');
				if (equal_sign != NULL)
				{
					*equal_sign = '\0';  /* Split name and value */
					add_or_update_alias(argv[i], equal_sign + 1);
				}
				else
				{
					fprintf(stderr, "Invalid alias format: %s\n", argv[i]);
				}
			}
		}
		else
		{
			/* Print specific aliases */
			for (i = 1; i < argc; ++i)
			{
				Alias *alias = find_alias(argv[i]);
				if (alias != NULL)
				{
					printf("%s='%s'\n", alias->name, alias->value);
				}
				else
				{
					printf("Alias %s not found\n", argv[i]);
				}
			}
		}
	}
}

/**
 * free_aliases - function that frees any allocated memory
 */

void free_aliases()
{
	Alias *current = alias_list;
	Alias *next;

	while (current != NULL)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}

	alias_list = NULL;
}
