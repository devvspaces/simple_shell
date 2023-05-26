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
 *
 * @gb: globals
 */
void free_env(glob_t *gb)
{
	int i = 0;

	for (; gb->environ[i] != NULL; i++)
		free(gb->environ[i]);
	free(gb->environ);
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
		/* printf("Freeing: %s %p--\n", argv[i], (void *)argv[i]); */
		free(argv[i]);
	free(argv);
}

/**
 * free_alias - clear aliases
 *
 * @gb: globals
 */
void free_alias(glob_t *gb)
{
	int i = 0;

	for (; gb->aliases[i]->name != NULL; i++)
	{
		free(gb->aliases[i]->name);
		free(gb->aliases[i]->value);
		free(gb->aliases[i]);
	}
	free(gb->aliases[i]);
	free(gb->aliases);
}

/**
 * free_gb - free globals
 * , it env and aliases
 *
 * @gb: globals
 */
void free_gb(glob_t *gb)
{
	free_env(gb), free_alias(gb), free(gb);
}
