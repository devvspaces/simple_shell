#include "main.h"

/**
 * count_tokens_delim - count possible
 * tokens
 *
 * @command: command to be counted
 * @delim: token delimeter
 *
 * Return: number of tokens
 */
int count_tokens_delim(char *command, char *delim)
{
	char *dup_command, *tok;
	int i = 0;

	dup_command = clone_str(command);

	tok = _strtok(dup_command, delim);
	while (tok != NULL)
	{
		tok = _strtok(NULL, delim);
		i++;
	}

	free(dup_command);
	return (i);
}

/**
 * count_tokens - count possible
 * tokens
 *
 * @command: command to be counted
 *
 * Return: number of tokens
 */
int count_tokens(char *command)
{
	return (count_tokens_delim(command, " "));
}

/**
 * parse_commands_delim - parses command to list
 * of strings.
 *
 * @command: command to be parsed
 * @cmd_len: length of chars in command
 * @delim: command delim
 *
 * Return: null terminated array of strings
 */
char **parse_commands_delim(char *command, int cmd_len, char *delim)
{
	char **argv, *tok;
	int i = 0;

	/* Nullify the last new line character */
	if (command[cmd_len - 1] == '\n')
		command[cmd_len - 1] = '\0';
	argv = malloc(in_char(count_tokens_delim(command, delim) + 1));
	if (argv == NULL)
		return (free(argv), NULL);
	tok = _strtok(command, delim);
	while (tok != NULL)
	{
		tok = lstrip(tok, " ");
		if (tok[0] != '\0')
		{
			argv[i] = malloc(_strlen(tok) + 1);
			if (argv[i] == NULL)
			{
				for (; i >= 0; i--)
					free(argv[i]);
				free(argv);
				return (NULL);
			}
			_strcpy(argv[i], tok);
		}
		else
			argv[i] = NULL;

		tok = _strtok(NULL, delim);
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

/**
 * parse_command - parses command to list
 * of strings.
 *
 * @command: command to be parsed
 * @cmd_len: length of chars in command
 *
 * Return: list of strings
 */
char **parse_command(char *command, int cmd_len)
{
	return (parse_commands_delim(command, cmd_len, " "));
}

/**
 * parse_commands - parses command to list
 * of strings.
 *
 * @command: command to be parsed
 * @cmd_len: length of chars in command
 *
 * Return: array of null terminated commands
 */
char **parse_commands(char *command, int cmd_len)
{
	return (parse_commands_delim(command, cmd_len, ";"));
}
