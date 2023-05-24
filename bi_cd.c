#include "main.h"

/**
 * _bi_cd - change directory builtin
 * function.
 *
 * @ac: number of args
 * @argv: command args
 * @cmd: origin commands
 *
 * Return: 0 = success, 1 = error
 */
int _bi_cd(char **cmd, int ac, char **argv)
{
	char *path;
	char cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("Failed");
		return (1);
	}
	if (ac > 2)
	{
		write_stderr("Invalid arguments\n");
		return (1);
	}
	if (ac == 2)
	{
		if (_strncmp(argv[1], "-", 1) == 0)
		{
			path = _getenv("OLDPWD");
			if (path != NULL)
				write_stdout(path);
			else
				write_stdout(cwd);
			write_stdout("\n");
		}
		else
			path = argv[1];
	}
	else
		path = _getenv("HOME");
	if (path != NULL)
	{
		if (chdir(path) == -1)
		{
			cd_error(path);
			return (2);
		}
		_setenv("OLDPWD", cwd, 1);
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			perror("Failed");
			return (1);
		}
		_setenv("PWD", cwd, 1);
	}
	(void)cmd;
	return (0);
}
