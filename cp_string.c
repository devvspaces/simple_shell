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
	if (dest == NULL)
	{
		free(dest);
		return (NULL);
	}
	dest = _strcpy(dest, val);
	return (dest);
}

/**
 * lstrip - strips toks from the left
 * of a string.
 *
 * @val: string to be striped
 * @tok: tokens to strip away
 *
 * Return: the pointer to the striped
 * string.
 */
char *lstrip(char *val, char *tok)
{
	while (*val != '\0')
		if (is_delim(*val, tok) == 0)
			val++;
		else
			break;
	return (val);
}
