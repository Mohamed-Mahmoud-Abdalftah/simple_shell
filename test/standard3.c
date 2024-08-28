#include "main.h"
/**
 * Custom strncpy function
 */
char *_strncpy(char *dest, const char *src, size_t n)
{
    size_t i;
    for (i = 0; i < n && src[i] != '\0'; i++)
        dest[i] = src[i];
    for (; i < n; i++)
        dest[i] = '\0';
    return dest;
}

/**
 * _strtol - Mimic strtol function
 * @str: String
 * @value: Pointer to store converted value
 *
 * Return: 0 on success, -1 on error
 */
int _strtol(const char *str, int *value)
{
	int result = 0;
	int sign = 1;

	if (*str == '\0')
	{
		return (-1);
	}
	if (*str == '-')
	{
		sign = -1;
		str++;
	}

	while (*str)
	{
		if (*str < '0' || *str > '9')
		{
			return (-1);
		}
		if (result > (INT_MAX - (*str - '0')) / 10)
		{
			return (-1);
		}
		result = result * 10 + (*str - '0');
		str++;
	}
	*value = sign * result;

	return (0);
}
