#include <stdio.h>
/**
 * main - prints the alphabet in reverse
 *
 * Return: Always 0 (Success)
 */
int main(void)
	{
	int letter;

	for (letter = 'z'; letter >= 'a'; letter--)
		putchar(letter);

	putchar('\n');

	return (0);
}
