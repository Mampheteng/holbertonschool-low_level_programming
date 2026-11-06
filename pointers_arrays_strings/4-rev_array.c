#include "main.h"

/**
 * reverse_array - Reverses the content of an integer array
 * @a: Pointer to the array
 * @n: Number of elements in the array
 *
 * Return: Nothing
 */
void reverse_array(int *a, int n)
{
	int start;
	int end;
	int temp;

	start = 0;
	end = n - 1;

	while (start < end)
	{
		temp = a[start];
		a[start] = a[end];
		a[end] = temp;

		start++;
		end--;
	}
}
