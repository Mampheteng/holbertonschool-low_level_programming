#include <stdlib.h>

/**
 * string_nconcat - Concatenates two strings using at most n bytes from s2.
 * @s1: The first string.
 * @s2: The second string.
 * @n: The maximum number of bytes to copy from s2.
 *
 * Return: A pointer to the newly allocated space in memory,
 *         or NULL if memory allocation fails.
 */
char *string_nconcat(char *s1, char *s2, unsigned int n)
{
	char *concat;
	unsigned int len1 = 0, len2 = 0, i, j;

	/* Treat NULL pointers as empty strings */
	if (s1 == NULL)
		s1 = "";
	if (s2 == NULL)
		s2 = "";

	/* Calculate lengths of s1 and s2 */
	while (s1[len1] != '\0')
		len1++;
	while (s2[len2] != '\0')
		len2++;

	/* Use the entire s2 string if n >= length of s2 */
	if (n >= len2)
		n = len2;

	/* Allocate memory for s1 + n bytes of s2 + null terminator */
	concat = malloc(sizeof(char) * (len1 + n + 1));
	if (concat == NULL)
		return (NULL);

	/* Copy s1 into the newly allocated buffer */
	for (i = 0; i < len1; i++)
		concat[i] = s1[i];

	/* Copy up to n bytes of s2 into the buffer */
	for (j = 0; j < n; j++)
		concat[i + j] = s2[j];

	/* Add null terminator */
	concat[i + j] = '\0';

	return (concat);
}
