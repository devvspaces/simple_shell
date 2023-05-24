#include "main.h"

/**
 * is_delim - check if 'c' is in
 * 'delim'
 *
 * @c: character to be checked
 * @delim: delimiter bytes
 *
 * Return: 0 if true, else 1
 */
int is_delim(char c, const char *delim)
{
	int i = 0;

	while (delim[i] != '\0')
	{
		if (delim[i] == c)
			return (0);
		i++;
	}

	return (1);
}

/**
 * _strtok - my version of strtok
 *
 * @val: value to be tokenized
 * @delim: delimiter bytes
 *
 * Return: next token else NULL
 */
char *_strtok(char *val, char *delim)
{
	char *ptr;
	static char *next;
	int i = 0;

	if (val != NULL)
	{
		ptr = val;
		for (; *ptr != '\0'; ptr++)
			if (is_delim(*ptr, delim) != 0)
			{
				next = ptr;
				break;
			}
	}
	else
	{
		if (next == NULL)
			return (NULL);
		ptr = next;
	}
	for (; ptr[i] != '\0'; i++)
		if (is_delim(ptr[i], delim) == 0)
		{
			ptr[i] = '\0';
			i++;
			break;
		}
	for (; ptr[i] != '\0'; i++)
		if (is_delim(ptr[i], delim) != 0)
		{
			next = ptr + i;
			break;
		}
	if (ptr[i] == '\0')
		next = NULL;
	return (ptr);
}
