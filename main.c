#include "main.h"

int last_command_status;
char *name;
char **environ;
int cmd_count;

/**
 * main - my simple shell
 *
 * @ac: length of args supplied
 * @av: args supplied
 *
 * Return: Always 0.
 */
int main(int ac, char **av)
{
	char *lineptr = NULL;
	size_t n = 0;
	int nstr_read;
	int atty;

	last_command_status = 0;
	name = av[0];
	environ = clone_env();
	cmd_count = 0;

	if (environ == NULL)
		return (1);

	atty = isatty(stdin->_fileno);
	while (1)
	{
		if (atty == 1)
			write_stdout("#cisfun$ ");

		nstr_read = _getline(&lineptr, &n, stdin);
		if (nstr_read == -1)
		{
			free(lineptr);
			free_env();
			exit(last_command_status);
		}
		cmd_count++;
		last_command_status = exec_cmd(lineptr, nstr_read);
		n = 0;
	}

	free(lineptr);
	free_env();
	(void)ac;
	return (last_command_status);
}
