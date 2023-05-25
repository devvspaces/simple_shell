#include "main.h"

/**
 * syntax_format - print syntax error
 * with cause
 *
 * @cause: syntax problem cause
 * @gb: globals
 *
 * Return: next token before operator
 */
void *syntax_format(char cause, glob_t *gb)
{
	if (cause == '&')
		syntax_error("&", gb);
	else
		syntax_error("|", gb);
	return (NULL);
}

/**
 * parse_logical_op - parse out logical
 * operations
 *
 * @cmd: command line input
 * @op: pointer to logical operator
 * @gb: globals
 *
 * Return: next token before operator
 */
char *parse_logical_op(char *cmd, unsigned int *op, glob_t *gb)
{
	char *ptr, prev_delim = 0;
	static char *next;
	int i = 0;
	const char *delim = "&|";

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
				else
					return (syntax_format(ptr[i], gb));
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
 * check_logical_tokens - checks for command
 * syntax error before execution.
 *
 * @cmd: command line input
 * @gb: globals
 *
 * Return: exit status 0 or 2
 */
int check_logical_tokens(char *cmd, glob_t *gb)
{
	char *tok, *cmd_copy;
	unsigned int op = 0;
	int token_count;

	cmd_copy = clone_str(cmd);
	tok = parse_logical_op(cmd_copy, &op, gb);
	while (tok != NULL)
	{
		if (errno == 127)
		{
			errno = 0;
			return (free(cmd_copy), 2);
		}
		token_count++;
		tok = parse_logical_op(NULL, &op, gb);
	}
	if (errno == 127)
	{
		errno = 0;
		return (free(cmd_copy), 2);
	}
	free(cmd_copy);
	return (0);
}

/**
 * exec_logical_cmd - executes
 * commands logically if required
 *
 * @cmd: command line input
 * @pcmd: parent origin commands
 * @gb: globals
 *
 * Return: 0 = success, 1 = error
 */
int exec_logical_cmd(char **pcmd, char *cmd, glob_t *gb)
{
	char **argv, *tok;
	unsigned int op = 0;
	int exit_status = 0;

	exit_status = check_logical_tokens(cmd, gb);
	if (exit_status == 2)
		return (exit_status);

	tok = parse_logical_op(cmd, &op, gb);
	while (tok != NULL)
	{
		argv = get_str_tokens(tok, " ");
		if (argv == NULL)
			return (1);
		exit_status = runcmd(pcmd, argv, gb);
		free_argv(argv);
		if ((char)op == '&' && exit_status != 0)
			break;
		else if ((char)op == '|' && exit_status == 0)
			break;
		tok = parse_logical_op(NULL, &op, gb);
	}
	return (exit_status);
}

/**
 * exec_cmd - execute shell
 * commands
 *
 * @line: command line input
 * @len: command line length
 * @gb: globals
 *
 * Return: 0 = success, 1 = error
 */
int exec_cmd(char *line, int len, glob_t *gb)
{
	char **commands, *line_copy;
	int ptr;
	int exit_status = 0;

	line_copy = clone_str(line);
	if (line_copy == NULL)
		return (free(line_copy), free(line), 1);
	commands = get_str_tokens(line_copy, ";");
	free(line_copy);
	if (commands == NULL)
		return (free(line), 1);
	for (ptr = 0; commands[ptr] != NULL; ptr++)
	{
		if (_strncmp(commands[ptr], "&&", 2) == 0)
			syntax_error("&&", gb);
		else if (_strncmp(commands[ptr], "||", 2) == 0)
			syntax_error("||", gb);
		else if (commands[ptr][0] == '&')
			syntax_error("&", gb);
		else if (commands[ptr][0] == '|')
			syntax_error("|", gb);
		if (errno == 127)
		{
			errno = 0;
			return (free_argv(commands), free(line), 2);
		}
	}
	free_argv(commands);

	commands = get_str_tokens(line, ";");
	free(line);
	if (commands == NULL)
		return (1);
	for (ptr = 0; commands[ptr] != NULL; ptr++)
		exit_status = exec_logical_cmd(commands, commands[ptr], gb);
	free_argv(commands), (void)len;
	return (exit_status);
}
