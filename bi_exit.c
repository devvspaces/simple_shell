#include "main.h"

/**
 * _bi_exit - exit builtin
 * function.
 *
 * @ac: number of args
 * @argv: command args
 * @commands: origin commands
 *
 * Return: 0 = success, 1 = error
 */
int _bi_exit(char **commands, int ac, char **argv)
{
	char *endptr;
	int status = last_command_status;
	long int exit_status;

	if (ac > 2)
	{
		write_stderr("Usage: exit [status]\n");
		return (1);
	}

	if (ac == 2)
	{
		exit_status = strtol(argv[1], &endptr, 10);
		if (*endptr != '\0' || _isdigit(argv[1][0]))
		{
			dprintf(STDERR_FILENO, "exit: Illegal number: %s\n", argv[1]);
			return (2);
		}
		status = (int)exit_status;
	}
	free_argv(argv);
	free_argv(commands);
	free_env();
	exit(status % 256);
	(void)ac;
}
