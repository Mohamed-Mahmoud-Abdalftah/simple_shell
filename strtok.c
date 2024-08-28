#include "main.h"
/**
 * _strtok - Custom strtok function
 * @str: string to tokenize
 * @delim: delimiter
 *
 * Return: tokenized string
 */
char *_strtok(char *str, const char *delim)
{
	static char *saved_str;
	char *start;
	const char *d;

	if (str)
	{
		saved_str = str;
	}
	if (!saved_str || *saved_str == '\0')
	{
		return (NULL);
	}

	start = saved_str;
	while (*saved_str)
	{
		d = delim;
		while (*d)
		{
			if (*saved_str == *d)
			{
				*saved_str++ = '\0';
				if (saved_str == start)
				{
					start++;
					continue;
				}
				return (start);
			}
			d++;
		}
		saved_str++;
	}
	return (start);
}
