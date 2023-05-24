#include "main.h"

/**
 * _bi_setenv - setenv builtin
 * function.
 *
 * @ac: number of args
 * @argv: command args
 * @cmd: origin commands
 *
 * Return: 0 = success, 1 = error
 */
int _bi_setenv(char **cmd, int ac, char **argv)
{
	if (ac != 3)
	{
		write_stderr("Invalid arguments; Usage: setenv VARIABLE VALUE\n");
		return (1);
	}

	if (_setenv(argv[1], argv[2], 1) == -1)
	{
		perror("Failed to setenv");
		return (1);
	}
	(void)cmd;
	return (0);
}

/**
 * _bi_unsetenv - unset env builtin
 * function.
 *
 * @ac: number of args
 * @argv: command args
 * @cmd: origin commands
 *
 * Return: 0 = success, 1 = error
 */
int _bi_unsetenv(char **cmd, int ac, char **argv)
{
	if (ac != 2)
	{
		write_stderr("Invalid arguments; Usage: unsetenv VARIABLE\n");
		return (1);
	}

	if (_unsetenv(argv[1]) == -1)
	{
		perror("Failed to unsetenv");
		return (1);
	}
	(void)cmd;
	return (0);
}
