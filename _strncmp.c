#include "main.h"

/**
 * _strncmp - compares the first n bytes
 * of two strings
 *
 * @s1: string 1 input to compare
 * @s2: against this other string 2
 * @n: the number of bytes to check
 *
 * Return: 0 if s1 and s2 are equal
 */
int _strncmp(const char *s1, const char *s2, int n)
{
	int i = 0, r;

	while (s1[i] != '\0' && s2[i] != '\0' && n != 0)
	{
		if (s1[i] != s2[i])
		{
			r = s1[i] - s2[i];
			break;
		}
		else
			r = s1[i] - s2[i];
		i++;
		n--;
	}

	return (r);
}

/**
 * _strcmp - compares s1 and s2
 *
 * @s1: string 1 input to compare
 * @s2: against this other string 2
 *
 * Return: 0 if s1 and s2 are equal
 */
int _strcmp(const char *s1, const char *s2)
{
	int max = _strlen(s1);
	int min = _strlen(s2);

	if (min > max)
		max = min;
	return (_strncmp(s1, s2, max));
}
