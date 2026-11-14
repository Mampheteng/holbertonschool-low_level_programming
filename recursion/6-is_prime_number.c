#include "main.h"

/**
 * find_prime - checks whether a number is divisible
 * @n: number to check
 * @divisor: possible divisor
 *
 * Return: 1 if prime, otherwise 0
 */
int find_prime(int n, int divisor)
{
	if (divisor > n / divisor)
		return (1);

	if (n % divisor == 0)
		return (0);

	return (find_prime(n, divisor + 1));
}

/**
 * is_prime_number - checks if an integer is prime
 * @n: number to check
 *
 * Return: 1 if prime, otherwise 0
 */
int is_prime_number(int n)
{
	if (n <= 1)
		return (0);

	return (find_prime(n, 2));
}

