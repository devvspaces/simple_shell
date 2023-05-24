#include "main.h"

/**
 * _strlen - get the length of
 * a string
 *
 * @str: string to count
 *
 * Return: the length of str
 */
int _strlen(const char *str)
{
	int i = 0;

	for (; str[i] != '\0'; i++)
		;
	return (i);
}
