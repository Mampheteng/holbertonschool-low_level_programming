#include "main.h"

/**
 * rev_string - Reverses a string
 * @s: Pointer to the string
 *
 * Return: Nothing
 */
void rev_string(char *s)
{
	int start;
	int end;
	char temp;

	start = 0;
	end = 0;

	while (s[end] != '\0')
	{
		end++;
	}

	end--;

	while (start < end)
	{
		temp = s[start];
		s[start] = s[end];
		s[end] = temp;

		start++;
		end--;
	}
}
