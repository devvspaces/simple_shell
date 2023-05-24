#include "main.h"

/**
 * combined_value - take a name
 * and value of an env to be added
 * or updated and combine into a single
 * string.
 *
 * @name: env key
 * @value: new value
 *
 * Return: pointer to combined value if success,
 * else NULL
 */
char *combined_value(const char *name, const char *value)
{
	char *new_value;
	size_t namelen, varlen;

	namelen = _strlen(name);
	varlen = _strlen(value);

	new_value = malloc(namelen + varlen + 2);
	if (new_value == NULL)
	{
		free(new_value);
		return (NULL);
	}
	_memcpy(new_value, name, namelen);
	new_value[namelen] = '=';
	_memcpy(&new_value[namelen + 1], value, varlen);
	new_value[namelen + varlen + 1] = '\0';
	return (new_value);
}

/**
 * count_nt_list - count the length
 * of a null terminated array
 *
 * @list: array to count
 *
 * Return: pointer to memory if success,
 * else NULL
 */
int count_nt_list(const void *list)
{
	int len = 0;
	char **clist = (char **)list;

	for (; clist[len] != NULL; len++)
		;
	return (len);
}

/**
 * clone_env - clone current enviroment
 *
 * Return: new enviroment
 */
char **clone_env()
{
	int len = 0;
	char **env_clone;

	env_clone = malloc(in_char(count_nt_list(__environ) + 1));
	if (env_clone == NULL)
	{
		free(env_clone);
		return (NULL);
	}

	for (; __environ[len] != NULL; len++)
	{
		env_clone[len] = malloc(in_char(_strlen(__environ[len]) + 1));
		if (env_clone[len] == NULL)
		{
			for (len--; len >= 0; len--)
				free(env_clone[len]);
			free(env_clone);
			return (NULL);
		}
		_strcpy(env_clone[len], __environ[len]);
	}
	env_clone[len] = NULL;
	return (env_clone);
}

/**
 * _setenv - set's a new enviroment
 * variable or update one if overwrite
 * is nonzero
 *
 * @name: env key to set
 * @value: value to add or update
 * @overwrite: if nonzero update env
 *
 * Return: 0 = success, -1 = error
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	char *new_env;
	int len = 0, env_len = count_nt_list(environ);
	size_t namelen;

	new_env = combined_value(name, value);
	if (new_env == NULL)
		return (-1);
	namelen = _strlen(name);

	if (_getenv(name) == NULL)
	{
		environ = _realloc(environ, in_char(env_len + 1), in_char(env_len + 200));
		if (environ == NULL)
		{
			free_env();
			return (-1);
		}
		environ[env_len] = new_env;
		environ[env_len + 1] = NULL;
	}
	else if (overwrite > 0)
	{
		for (; environ[len] != NULL; len++)
			if (_strncmp(environ[len], name, namelen) == 0)
			{
				free(environ[len]);
				environ[len] = new_env;
			}
	}
	else
		free(new_env);
	return (0);
}
