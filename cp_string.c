#include "main.h"

/**
 * clone_str - copy val to
 * malloc'd new dest
 *
 * @val: string to clone
 *
 * Description: Pointer returned must be
 * free'd by the caller.
 *
 * Return: the pointer to the dest
 */
char *clone_str(char *val)
{
	char *dest;

	dest = malloc(_strlen(val) + 1);
	dest = _strcpy(dest, val);
	return (dest);
}
