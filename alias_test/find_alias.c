#include "main.h"
 
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
