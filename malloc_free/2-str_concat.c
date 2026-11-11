#include "main.h"
#include <stdlib.h>

/**
 * str_concat - concatenates two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: pointer to the concatenated string, or NULL
 */
char *str_concat(char *s1, char *s2)
{
	char *result;
	unsigned int i, j, len1, len2;

	if (s1 == NULL)
		s1 = "";

	if (s2 == NULL)
		s2 = "";

	len1 = 0;
	while (s1[len1] != '\0')
		len1++;

	len2 = 0;
	while (s2[len2] != '\0')
		len2++;

	result = malloc(sizeof(char) * (len1 + len2 + 1));
	if (result == NULL)
		return (NULL);

	i = 0;
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}

	j = 0;
	while (s2[j] != '\0')
	{
		result[i + j] = s2[j];
		j++;
	}

	result[i + j] = '\0';

	return (result);
}

