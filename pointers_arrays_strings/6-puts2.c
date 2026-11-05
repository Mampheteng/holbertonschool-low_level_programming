#include "main.h"

/**
 * puts2 - Prints every other character of a string
 * @str: Pointer to the string
 *
 * Return: Nothing
 */
void puts2(char *str)
{
	int i;
	int length;

	length = 0;

	while (str[length] != '\0')
	{
		length++;
	}

	for (i = 0; i < length; i += 2)
	{
		_putchar(str[i]);
	}

	_putchar('\n');
}

