#include "main.h"

/**
 * _bi_exit - exit builtin
 * function.
 *
 * @ac: number of args
 * @argv: command args
 * @commands: origin commands
 * @gb: globals
 *
 * Return: 0 = success, 1 = error
 */
int _bi_exit(char **commands, int ac, char **argv, glob_t *gb)
{
	char *endptr;
	long int status = (long int)gb->exit_status;
	long int exit_status;

	if (ac >= 2)
	{
		exit_status = _strtol(argv[1], &endptr, 10);
		if (*endptr != '\0' || _isdigit(argv[1][0]))
		{
			exit_error(argv[1], gb);
			return (2);
		}
		if (exit_status > INT_MAX)
		{
			exit_error(argv[1], gb);
			return (2);
		}
		status = exit_status;
	}
	free_argv(argv);
	free_argv(commands);
	free_env(gb);
	free(gb);
	exit(status % 256);
}
