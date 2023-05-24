#include "main.h"

/**
 * _getenv_idx - Get the index of the env
 * variable or -1 if it doesn't exist
 *
 * @name: env name to get
 * @gb: globals
 *
 * Return: idx of envariable NAME,
 * or -1 if it doesn't exist.
 */
int _getenv_idx(const char *name, glob_t *gb)
{
	int i = 0;
	int len = _strlen(name);

	for (; gb->environ[i] != NULL; i++)
		if (_strncmp(gb->environ[i], name, len) == 0)
			return (i);
	return (-1);
}

/**
 * _getenv - Return the value of envariable
 * NAME, or NULL if it doesn't exist.
 *
 * @name: env name to get
 * @gb: globals
 *
 * Return: value of envariable NAME,
 * or NULL if it doesn't exist.
 */
char *_getenv(const char *name, glob_t *gb)
{
	int i;
	char *temp;

	i = _getenv_idx(name, gb);
	if (i != -1)
	{
		temp = gb->environ[i];
		temp += (_strlen(name) + 1);
		return (temp);
	}
	return (NULL);
}
