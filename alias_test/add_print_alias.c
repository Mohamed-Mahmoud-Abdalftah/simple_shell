#include "main.h"
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
 * print_aliases - function thatprints aliases in format 'name='value''
 */

void print_aliases() {
    Alias *current = alias_list;
    while (current != NULL) {
        printf("%s='%s'\n", current->name, current->value);
        current = current->next;
    }
}
