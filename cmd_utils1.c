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
 * replace_variables - replace variables in a command
 *
 * @cmd: command to replace
 * @gb: globals
 *
 * Return: pointer to new command
 */
char *replace_variables(char *cmd, glob_t *gb)
{
	int pid, idx = 0;
	char *pid_str, *exit_status, *temp, *env, **actions, *name;

	pid = (int)getpid();
	pid_str = _itoa(pid);
	temp = replace(cmd, "$$", pid_str);
	if (temp == NULL)
		return (NULL);
	free(pid_str), free(cmd), cmd = temp;

	exit_status = _itoa(gb->exit_status);
	temp = replace(cmd, "$?", exit_status);
	if (temp == NULL)
		return (NULL);
	free(exit_status), free(cmd), cmd = temp;

	for (; gb->environ[idx] != NULL; idx++)
	{
		env = clone_str(gb->environ[idx]);
		if (env == NULL)
			return (NULL);
		actions = spilt_action(env);
		name = malloc(_strlen(actions[0]) + 2);
		if (name == NULL)
			return (free(name), NULL);
		name = _strcpy(name, "$");
		name = _strcat(name, actions[0]);
		temp = replace(cmd, name, actions[1]);
		if (temp == NULL)
			return (free(name), NULL);
		free(name), free(env), free(cmd), cmd = temp;
	}
	return (cmd);
}

/**
 * check_syntax_error - check command for
 * syntax error.
 *
 * @line: command to replace
 * @gb: globals
 *
 * Return: 0 if success else >= 1
 */
int check_syntax_error(char *line, glob_t *gb)
{
	char **commands, *line_copy;
	int ptr;

	line_copy = clone_str(line);
	if (line_copy == NULL)
		return (1);

	commands = get_str_tokens(line_copy, ";");
	free(line_copy);
	if (commands == NULL)
		return (1);

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
			return (free_argv(commands), 2);
		}
	}
	free_argv(commands);
	return (0);
}
