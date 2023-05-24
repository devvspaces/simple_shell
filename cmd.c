#include "main.h"

/**
 * parse_logical_op - parse out logical
 * operations
 *
 * @cmd: command line input
 * @op: pointer to logical operator
 *
 * Return: next token before operator
 */
char *parse_logical_op(char *cmd, unsigned int *op)
{
	char *ptr;
	static char *next;
	int i = 0;
	const char *delim = "&|";
	char prev_delim = 0;

	if (cmd != NULL)
	{
		ptr = cmd;
		next = ptr;
	}
	else
	{
		if (next == NULL)
			return (NULL);
		ptr = next;
	}
	for (; ptr[i] != '\0'; i++)
		if (is_delim(ptr[i], delim) == 0)
		{
			if (prev_delim == 0)
				prev_delim = ptr[i];
			else
			{
				if (prev_delim == ptr[i])
				{
					*op = (unsigned int)ptr[i];
					ptr[i - 1] = '\0';
					ptr[i] = '\0';
				}
				i++;
				break;
			}
		}
	next = ptr + i;
	if (ptr[i] == '\0')
		next = NULL;
	return (ptr);
}

/**
 * exec_logical_cmd - executes
 * commands logically if required
 *
 * @cmd: command line input
 * @pcmd: parent origin commands
 *
 * Return: 0 = success, 1 = error
 */
int exec_logical_cmd(char **pcmd, char *cmd)
{
	char **argv;
	char *tok;
	unsigned int op = 0;
	int exit_status = 0;

	tok = parse_logical_op(cmd, &op);
	while (tok != NULL)
	{
		argv = parse_command(tok, _strlen(tok));
		if (argv == NULL)
			return (1);
		exit_status = runcmd(pcmd, argv);
		free_argv(argv);
		if ((char)op == '&' && exit_status != 0)
			break;
		else if ((char)op == '|' && exit_status == 0)
			break;
		tok = parse_logical_op(NULL, &op);
	}
	return (exit_status);
}

/**
 * exec_cmd - execute shell
 * commands
 *
 * @line: command line input
 * @len: command line length
 *
 * Return: 0 = success, 1 = error
 */
int exec_cmd(char *line, int len)
{
	char **commands;
	int ptr = 0;
	int exit_status;

	commands = parse_commands(line, len);
	free(line);
	if (commands == NULL)
		return (1);
	for (; commands[ptr] != NULL; ptr++)
		exit_status = exec_logical_cmd(commands, commands[ptr]);
	free_argv(commands);
	return (exit_status);
}
