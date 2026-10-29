#include <stdio.h>
/**
 * main - prints hexadecimal numbers in lowercase
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	int number;

	for (number = 0; number <= 9; number++)
		putchar(number + '0');

	for (number = 'a'; number <= 'f'; number++)
		putchar(number);

	putchar('\n');

	return (0);
}

