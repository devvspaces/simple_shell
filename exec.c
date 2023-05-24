#include "main.h"

/**
 * runcmd - execute shell
 * command
 *
 * @argv: command args
 * @commands: origin commands
 * @gb: globals
 *
 * Return: 0 = success, 1 = error
 */
int runcmd(char **commands, char **argv, glob_t *gb)
{
	pid_t pid;
	int status;
	char *cmd_path;
	int (*builtin_func)(char **, int, char **, glob_t *) = is_builtin(argv[0]);

	if (builtin_func != NULL)
		return (exec_builtin(commands, builtin_func, gb, argv));

	cmd_path = which(argv[0], gb);
	if (cmd_path == NULL)
	{
		cmd_404_error(argv[0], gb);
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Error creating process:");
		return (1);
	}
	if (pid == 0)
	{
		if (execve(cmd_path, argv, gb->environ) == -1)
			perror(gb->name);
		exit(1);
	}
	else
	{
		wait(&status);
		free(cmd_path);
		return (WEXITSTATUS(status));
	}
	free(cmd_path);
	return (0);
}
