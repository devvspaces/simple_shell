#include "main.h"

/**
 * _getenv - Return the value of envariable
 * NAME, or NULL if it doesn't exist.
 *
 * @name: env name to get
 *
 * Return: value of envariable NAME,
 * or NULL if it doesn't exist.
 */
char *_getenv(const char *name)
{
	int i = 0;
	int len = _strlen(name);
	char *temp;

	for (; environ[i] != NULL; i++)
		if (_strncmp(environ[i], name, len) == 0)
		{
			temp = environ[i];
			temp += (len + 1);
			return (temp);
		}
	return (NULL);
}
