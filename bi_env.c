#include "main.h"

/**
 * _bi_env - env builtin
 * function.
 *
 * @ac: number of args
 * @argv: command args
 * @cmd: origin commands
 * @gb: globals
 *
 * Return: 0 = success, 1 = error
 */
int _bi_env(char **cmd, int ac, char **argv, glob_t *gb)
{
	int i = 0;

	while (gb->environ[i] != NULL)
	{
		write_stdout(gb->environ[i]);
		write_stdout("\n");
		i++;
	}

	(void)ac;
	(void)argv;
	(void)cmd;
	return (0);
}
