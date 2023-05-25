#include "main.h"

/**
 * ctrl_c_handler - Prints a new prompt upon
 * ctrl-c signal.
 *
 * @sig: The signal.
 */
void ctrl_c_handler(int sig)
{
	(void)sig;
	write_stdout("\n#cisfun$ ");
}

/**
 * create_glob - create glob struct
 * for storing globals
 *
 * @name: shell name.
 *
 * Return: intialized pointer to glob.
 */
glob_t *create_glob(char *name)
{
	glob_t *gb;

	gb = malloc(sizeof(glob_t));
	if (gb == NULL)
		return (perror("Memory Error"), free(gb), NULL);

	gb->name = name;
	gb->cmd_count = 0;
	gb->exit_status = 0;

	gb->environ = clone_env();
	if (gb->environ == NULL)
		return (perror("Memory Error"), free(gb), NULL);

	gb->aliases = init_aliases();
	if (gb->aliases == NULL)
		return (perror("Memory Error"), free(gb), NULL);

	return (gb);
}

/**
 * open_file - create glob struct
 * for storing globals
 *
 * @path: file path
 * @gb: globals
 *
 * Return: file descriptor or -1.
 */
int open_file(char *path, glob_t *gb)
{
	int fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (file_open_error(path, gb), -1);
	return (fd);
}

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
	int nstr_read, atty, ext, fd;
	glob_t *gb;

	signal(SIGINT, ctrl_c_handler);

	gb = create_glob(av[0]);
	if (gb == NULL)
		return (1);

	fd = ac != 1 ? open_file(av[1], gb) : STDIN_FILENO;
	if (fd == -1)
		return (1);
	
	atty = isatty(fd);
	while (1)
	{
		if (atty == 1)
			write_stdout("#cisfun$ ");

		nstr_read = _getline(&lineptr, &n, fd);
		ext = gb->exit_status;
		if (nstr_read == -1)
		{
			if (atty == 1)
				write_stdout("\n");
			free(lineptr), free_env(gb), free_alias(gb), free(gb), exit(ext);
		}
		gb->cmd_count++;
		gb->exit_status = exec_cmd(lineptr, nstr_read, gb);
		n = 0;
	}
	free(lineptr), free_env(gb), free_alias(gb), free(gb);
	(void)ac;
	return (gb->exit_status);
}
