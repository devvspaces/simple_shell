#include "main.h"

/**
 * _bi_env - env builtin
 * function.
 *
 * @ac: number of args
 * @argv: command args
 * @cmd: origin commands
 *
 * Return: 0 = success, 1 = error
 */
int _bi_env(char **cmd, int ac, char **argv)
{
	int i = 0;

	while (__environ[i] != NULL)
	{
		write_stdout(__environ[i]);
		write_stdout("\n");
		i++;
	}

	(void)ac;
	(void)argv;
	(void)cmd;
	return (0);
}
