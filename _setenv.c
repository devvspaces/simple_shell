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
		env_clone[len] = malloc(_strlen(__environ[len]) + 1);
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
 * @gb: globals
 *
 * Return: 0 = success, -1 = error
 */
int _setenv(const char *name, const char *value, int overwrite, glob_t *gb)
{
	char *new_env;
	int env_len = count_nt_list(gb->environ), idx;
	char **new_mem;

	new_env = combined_value(name, value);
	if (new_env == NULL)
		return (-1);

	idx = _getenv_idx(name, gb);
	if (idx == -1)
	{
		new_mem = _realloc(gb->environ, in_char(env_len + 1), in_char(env_len + 2));
		if (new_mem == NULL)
			return (free(new_mem), -1);
		gb->environ = new_mem;
		gb->environ[env_len] = new_env;
		gb->environ[env_len + 1] = NULL;
	}
	else if (overwrite > 0)
	{
		free(gb->environ[idx]);
		gb->environ[idx] = new_env;
	}
	else
		free(new_env);
	return (0);
}
