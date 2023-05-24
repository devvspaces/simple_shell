#include "main.h"

/**
 * _bi_cd - change directory builtin
 * function.
 *
 * @ac: number of args
 * @argv: command args
 * @cmd: origin commands
 * @gb: globals
 *
 * Return: 0 = success, 1 = error
 */
int _bi_cd(char **cmd, int ac, char **argv, glob_t *gb)
{
	char *path;
	char cwd[1024];

	(void)cmd;
	(void)gb;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (perror("Failed"), 1);
	if (ac > 2)
		return (write_stderr("Invalid arguments\n"), 1);
	if (ac == 2)
		if (_strncmp(argv[1], "-", 1) == 0)
		{
			path = _getenv("OLDPWD", gb);
			if (path != NULL)
				write_stdout(path);
			else
				write_stdout(cwd);
			write_stdout("\n");
		}
		else
			path = argv[1];
	else
		path = _getenv("HOME", gb);
	if (path != NULL)
	{
		if (chdir(path) == -1)
			return (cd_error(path, gb), 2);
		_setenv("OLDPWD", cwd, 1, gb);
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			return (perror("Failed"), 1);
		_setenv("PWD", cwd, 1, gb);
	}
	return (0);
}
