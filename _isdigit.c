#include "main.h"

/**
 * _isdigit - checks if a character
 * is a digit or not.
 *
 * @c: the character to check
 *
 * Return: 0 if is a digit, else 1
*/
int _isdigit(char c)
{
	if ((int)c >= 48 && (int) c <= 57)
		return (0);

	return (1);
}


