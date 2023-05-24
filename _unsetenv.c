#include "main.h"

/**
 * _unsetenv - unset enviroment
 * variable
 *
 * @name: variable name
 * @gb: globals
 *
 * Return: 0 = success, -1 = error
 */
int _unsetenv(const char *name, glob_t *gb)
{
	int idx = _getenv_idx(name, gb);

	if (idx == -1)
		return (-1);

	free(gb->environ[idx]);
	for (; gb->environ[idx] != NULL; ++idx)
		gb->environ[idx] = gb->environ[idx + 1];

	return (0);
}
