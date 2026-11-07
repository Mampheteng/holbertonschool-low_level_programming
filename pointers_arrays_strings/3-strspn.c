
#include "main.h"

/**
 * _strspn - gets the length of a prefix substring
 * @s: string to search
 * @accept: characters to match
 *
 * Return: number of bytes in the initial segment
 */
unsigned int _strspn(char *s, char *accept)
{
	unsigned int i, j;

	i = 0;
	while (s[i] != '\0')
	{
		j = 0;
		while (accept[j] != '\0' && accept[j] != s[i])
			j++;

		if (accept[j] == '\0')
			break;

		i++;
	}

	return (i);
}

