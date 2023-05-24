#include "main.h"

/**
 * _unsetenv - unset enviroment
 * variable
 *
 * @name: variable name
 *
 * Return: 0 = success, -1 = error
 */
int _unsetenv(const char *name)
{
	char **env_clone, *temp;
	int len_env = 0, i = 0;
	size_t namelen;

	namelen = _strlen(name);
	if (_getenv(name) != NULL)
	{
		for (; __environ[len_env] != NULL; len_env++)
			;
		env_clone = _calloc(len_env + 2, sizeof(char *));
		if (env_clone == NULL)
		{
			free(env_clone);
			return (-1);
		}
		len_env = 0;
		for (; __environ[len_env] != NULL; len_env++)
		{
			if (_strncmp(__environ[len_env], name, namelen))
			{
				temp = malloc(_strlen(__environ[len_env]) + 1);
				if (temp == NULL)
				{
					free(env_clone);
					free(temp);
					return (-1);
				}
				_strcpy(temp, __environ[len_env]);
				env_clone[i] = temp;
				i++;
			}
		}
		env_clone[i] = NULL;
		__environ = env_clone;
	}

	return (0);
}
