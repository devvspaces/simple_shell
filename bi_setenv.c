#include "main.h"

/**
 * _bi_setenv - setenv builtin
 * function.
 *
 * @ac: number of args
 * @argv: command args
 * @cmd: origin commands
 * @gb: globals
 *
 * Return: 0 = success, 1 = error
 */
int _bi_setenv(char **cmd, int ac, char **argv, glob_t *gb)
{
	if (ac != 3)
	{
		write_stderr("Invalid arguments; Usage: setenv VARIABLE VALUE\n");
		return (1);
	}

	if (_setenv(argv[1], argv[2], 1, gb) == -1)
	{
		perror("Failed to setenv");
		return (1);
	}
	(void)cmd;
	(void)gb;
	return (0);
}

/**
 * _bi_unsetenv - unset env builtin
 * function.
 *
 * @ac: number of args
 * @argv: command args
 * @cmd: origin commands
 * @gb: globals
 *
 * Return: 0 = success, 1 = error
 */
int _bi_unsetenv(char **cmd, int ac, char **argv, glob_t *gb)
{
	if (ac != 2)
	{
		write_stderr("Invalid arguments; Usage: unsetenv VARIABLE\n");
		return (1);
	}

	if (_unsetenv(argv[1], gb) == -1)
	{
		perror("Failed to unsetenv");
		return (1);
	}
	(void)cmd;
	(void)gb;
	return (0);
}
