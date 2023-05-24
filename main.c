#include "main.h"

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
	int nstr_read, atty;
	glob_t *gb;

	gb = malloc(sizeof(glob_t));
	if (gb == NULL)
		return (perror("Memory Error"), free(gb), 1);

	gb->name = av[0];
	gb->cmd_count = 0;
	gb->environ = clone_env();
	gb->exit_status = 0;

	if (gb->environ == NULL)
		return (1);

	atty = isatty(stdin->_fileno);
	while (1)
	{
		if (atty == 1)
			write_stdout("#cisfun$ ");

		nstr_read = _getline(&lineptr, &n, stdin);
		if (nstr_read == -1)
			free(lineptr), free_env(gb), exit(gb->exit_status);
		gb->cmd_count++;
		gb->exit_status = exec_cmd(lineptr, nstr_read, gb);
		n = 0;
	}

	free(lineptr), free_env(gb), free(gb);
	(void)ac;
	return (gb->exit_status);
}
