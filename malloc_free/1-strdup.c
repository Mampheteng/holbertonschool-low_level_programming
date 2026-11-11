#include "main.h"
#include <stdlib.h>

/**
 * _strdup - returns a pointer to a duplicated string
 * @str: string to duplicate
 *
 * Return: pointer to the duplicated string, or NULL
 */
char *_strdup(char *str)
{
	char *copy;
	unsigned int i;

	if (str == NULL)
		return (NULL);

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}

	copy = malloc(sizeof(char) * (i + 1));
	if (copy == NULL)
		return (NULL);

	i = 0;
	while (str[i] != '\0')
	{
		copy[i] = str[i];
		i++;
	}

	copy[i] = '\0';

	return (copy);
}

