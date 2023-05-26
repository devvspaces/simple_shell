#include "main.h"

/**
 * is_command - checks if a
 * command is a command or a file
 *
 * @cmd: command arg
 *
 * Return: 1 if command else 0
 */
int is_command(char *cmd)
{
	char *ptr = cmd;

	for (; *ptr != '\0'; ptr++)
	{
		if (*ptr != '.' && *ptr != ' ' && *ptr != '/')
			return (1);

		if (*ptr == '/')
			return (0);
	}

	return (1);
}

/**
 * which - finds the path
 * to a command
 *
 * @cmd: command arg
 * @gb: globals
 *
 * Return: pointer to null terminated
 * file path if success else NULL
 */
char *which(char *cmd, glob_t *gb)
{
	char *path_clone, *path, *tok, *file_path;
	size_t cmd_len;
	struct stat file_stat;

	if ((is_command(cmd) == 0) && (stat(cmd, &file_stat) == 0))
		return (clone_str(cmd));
	path = _getenv("PATH", gb);
	if (path)
	{
		cmd_len = _strlen(cmd);
		path_clone = clone_str(path);
		tok = _strtok(path_clone, ":");
		while (tok != NULL)
		{
			file_path = malloc(_strlen(tok) + cmd_len + 2);
			if (file_path == NULL)
			{
				free(file_path);
				return (NULL);
			}
			_strcpy(file_path, tok);
			_strcat(file_path, "/");
			_strcat(file_path, cmd);
			_strcat(file_path, "\0");
			if (stat(file_path, &file_stat) == 0)
			{
				free(path_clone);
				return (file_path);
			}
			tok = _strtok(NULL, ":");
			free(file_path);
		}
		free(path_clone);
	}
	return (NULL);
}
