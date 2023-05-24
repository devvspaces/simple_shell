#include "main.h"

/**
 * which - finds the path
 * to a command
 *
 * @cmd: command arg
 *
 * Return: pointer to null terminated
 * file path if success else NULL
 */
char *which(char *cmd)
{
	char *path_clone, *path, *tok, *file_path;
	size_t cmd_len;
	struct stat file_stat;

	if (stat(cmd, &file_stat) == 0)
		return (clone_str(cmd));
	path = _getenv("PATH");
	if (path)
	{
		cmd_len = _strlen(cmd);
		path_clone = strdup(path);
		tok = strtok(path_clone, ":");
		while (tok != NULL)
		{
			file_path = malloc(_strlen(tok) + cmd_len + 2);
			if (file_path == NULL)
			{
				free(file_path);
				return (NULL);
			}
			_strcpy(file_path, tok);
			strcat(file_path, "/");
			strcat(file_path, cmd);
			strcat(file_path, "\0");
			if (stat(file_path, &file_stat) == 0)
			{
				free(path_clone);
				return (file_path);
			}
			tok = strtok(NULL, ":");
			free(file_path);
		}

		free(path_clone);
	}
	return (NULL);
}
