#include "main.h"

/**
 * is_builtin - find builtin func
 * if it exits
 *
 * @name: command name
 *
 * Return: a builtin function
 */
int (*is_builtin(char *name))(char **, int, char **, glob_t *)
{
	_builtin builtins[] = {
		{"exit", _bi_exit},
		{"env", _bi_env},
		{"setenv", _bi_setenv},
		{"unsetenv", _bi_unsetenv},
		{"cd", _bi_cd},
		{"alias", _bi_alias},
		{NULL, NULL}};
	int i = 0;

	while (builtins[i].name != NULL)
	{
		if (_strcmp(builtins[i].name, name) == 0)
			break;
		i++;
	}

	return (builtins[i].func);
}

/**
 * exec_builtin - execute builtin
 * function
 *
 * @bf: builtin function
 * @av: command args
 * @cmd: origin commands
 * @gb: globals
 *
 * Return: 0 = success, 1 = error, 2 = not builtin
 */
int exec_builtin(
	char **cmd,
	int (*bf)(char **, int, char **, glob_t *),
	glob_t *gb, char **av)
{
	return (bf(cmd, count_nt_list(av), av, gb));
}
