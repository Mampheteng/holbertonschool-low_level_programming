#include "main.h"

/**
 * cap_string - Capitalizes the first letter of every word
 * @str: String to capitalize
 *
 * Return: Pointer to the modified string
 */
char *cap_string(char *str)
{
	int i;
	int j;
	char separators[] = " \t\n,;.!?\"(){}";

	i = 0;

	while (str[i] != '\0')
	{
		if (i == 0 || str[i - 1] == ' ')
		{
			if (str[i] >= 'a' && str[i] <= 'z')
				str[i] = str[i] - 32;
		}

		for (j = 0; separators[j] != '\0'; j++)
		{
			if (str[i] == separators[j])
			{
				if (str[i + 1] >= 'a' && str[i + 1] <= 'z')
					str[i + 1] = str[i + 1] - 32;
			}
		}

		i++;
	}

	return (str);
}
