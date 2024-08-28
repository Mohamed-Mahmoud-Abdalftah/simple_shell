#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Node structure for linked list
 * @Alias:
 * @name:
 * @value:
 * @next:
 *
 * Description: a structure to store aliases in a linked list
 */
 
typedef struct Alias
{
	char *name;
	char *value;
	struct Alias *next;
} Alias;

Alias *alias_list = NULL;

/**
 * add_or_update_alias - function to add, update adn find aliases
 * @name:
 * @value:
 * 
 * Return:
 */
 
void add_or_update_alias(const char *name, const char *value) 
{
	Alias *current = alias_list;
	Alias *previous = NULL;

	/* Traverse the list to check if the alias already exists */
	while (current != NULL && strcmp(current->name, name) != 0) 
	{
		previous = current;
		current = current->next;
	}

	if (current != NULL)
	{
        /* Alias exists, update its value */
		free(current->value);
		current->value = strdup(value);
    }
	else
	{
		/* Alias does not exist, create a new one */
		Alias *new_alias = malloc(sizeof(Alias));
		new_alias->name = strdup(name);
		new_alias->value = strdup(value);
		new_alias->next = NULL;

		if (previous != NULL)
		{
			previous->next = new_alias;
		}
		else
		{
			alias_list = new_alias;
		}
	}
}

/**
 * find_alias - function to search for an alias
 * @name: name to search
 *
 * Return: a pointer to the alias else NULL
 *
 */
Alias* find_alias(const char *name)
{
	Alias *current = alias_list;

	while (current != NULL)
	{
		if (strcmp(current->name, name) == 0)
		{
			return (current);
		}
		current = current->next;
	}
	return (NULL);
}

/**
 * print_aliases - function thatprints aliases in format 'name='value''
 */

void print_aliases() {
    Alias *current = alias_list;
    while (current != NULL) {
        printf("%s='%s'\n", current->name, current->value);
        current = current->next;
    }
}

/**
 * alias - function that gets commands from arguments
 * @argc: arguments
 * @argv: pointer to arguments
 */
void alias(int argc, char *argv[])
{
	char *equal_sign;

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
			for (int i = 1; i < argc; ++i)
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
			for (int i = 1; i < argc; ++i)
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

