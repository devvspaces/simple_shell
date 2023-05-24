#include "main.h"

/**
 * in_char - get the sizeof
 * char * x the number, n.
 *
 * @n: number of char *
 *
 * Return: size in char *
 */
size_t in_char(int n)
{
	return (sizeof(char *) * n);
}

/**
 * free_env - clear global env
 * memory
 */
void free_env(void)
{
	int i = 0;

	for (; environ[i] != NULL; i++)
		free(environ[i]);
	free(environ);
}

/**
 * free_argv - clearn argv commands
 *
 * @argv: argv commands types, null
 * terminated array of strings
 */
void free_argv(char **argv)
{
	int i = 0;

	for (; argv[i] != NULL; i++)
		free(argv[i]);
	free(argv);
}
