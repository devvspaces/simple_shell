#include "main.h"

/**
 * spilt_action - split key=value to key
 * and value
 *
 * @str: string to spilt
 *
 * Return: List of strings [key, value]
 */
char **spilt_action(char *str)
{
	static char *result[2];
	int idx = 1;
	char *value = NULL;

	for (; str[idx] != '\0'; idx++)
	{
		if (str[idx] == '=')
		{
			str[idx] = '\0';
			value = &str[idx + 1];
			break;
		}
	}

	result[0] = str;
	result[1] = value;
	return (result);
}

/**
 * print_alias - print an alias name value
 *
 * @name: alias name
 * @gb: globals
 */
void print_alias(char *name, glob_t *gb)
{
	char *value = get_alias(name, gb);

	if (value != NULL)
		format_alias(name, value);
}

/**
 * _bi_alias - alias builting
 * function
 *
 * @ac: number of args
 * @argv: command args
 * @cmd: origin commands
 * @gb: globals
 *
 * Return: 0 = success, > 1 = error
 */
int _bi_alias(char **cmd, int ac, char **argv, glob_t *gb)
{
	int idx;
	char **action, *temp;
	int exit_status = 0;

	if (ac == 1)
		return (list_alias(gb), 0);

	for (idx = 1; idx < ac; idx++)
	{
		temp = clone_str(argv[idx]);
		if (temp == NULL)
			return (2);
		action = spilt_action(temp);
		if (action[1] != NULL)
			set_alias(action[0], action[1], gb);
		else if (get_alias_idx(action[0], gb) == -1)
		{
			write_stderr("alias: ");
			write_stderr(action[0]);
			write_stderr(" not found\n");
			exit_status = 1;
		}
		free(temp);
	}

	for (idx = 1; idx < ac; idx++)
	{
		action = spilt_action(argv[idx]);
		if (action[1] == NULL)
			print_alias(action[0], gb);
	}

	(void)cmd;
	return (exit_status);
}
