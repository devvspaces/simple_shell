#include "main.h"

/**
 * is_builtin - find builtin func
 * if it exits
 *
 * @name: command name
 *
 * Return: a builtin function
 */
int (*is_builtin(char *name))(char **, int, char **)
{
	_builtin builtins[] = {
		{"exit", _bi_exit},
		{"env", _bi_env},
		{"setenv", _bi_setenv},
		{"unsetenv", _bi_unsetenv},
		{"cd", _bi_cd},
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
 *
 * Return: 0 = success, 1 = error, 2 = not builtin
 */
int exec_builtin(char **cmd, int (*bf)(char **, int, char **), char **av)
{
	return (bf(cmd, count_nt_list(av), av));
}
