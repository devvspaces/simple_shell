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

/**
 * rstrip - strips toks from the right
 * of a string.
 *
 * @val: string to be striped
 * @tok: tokens to strip away
 *
 * Return: the pointer to the striped
 * string.
 */
char *rstrip(char *val, char *tok)
{
	int len = _strlen(val);

	for (; len >= 0; --len)
		if (is_delim(val[len], tok) == 0)
			val[len] = '\0';
		else
			break;
	return (val);
}

/**
 * strip - strips toks from the right
 * and left of a string.
 *
 * @val: string to be striped
 * @tok: tokens to strip away
 *
 * Return: the pointer to the striped
 * string.
 */
char *strip(char *val, char *tok)
{
	val = lstrip(val, tok);
	val = rstrip(val, tok);
	return (val);
}
