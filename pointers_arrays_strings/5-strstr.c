#include <stddef.h>

/**
 * _strstr - Locates a substring within a string.
 * @haystack: The main string to be searched.
 * @needle: The substring to look for.
 *
 * Return: A pointer to the beginning of the located substring,
 *         or NULL if the substring is not found.
 *         If needle is an empty string, haystack is returned.
 */
char *_strstr(char *haystack, char *needle)
{
	int i;
	int j;

	if (*needle == '\0')
		return (haystack);

	for (i = 0; haystack[i] != '\0'; i++)
	{
		for (j = 0; needle[j] != '\0'; j++)
		{
			if (haystack[i + j] != needle[j])
				break;
		}

		if (needle[j] == '\0')
			return (haystack + i);
	}

	return (NULL);
}
