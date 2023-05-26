#include "main.h"

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
