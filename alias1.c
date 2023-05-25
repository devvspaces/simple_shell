#include "main.h"

/**
 * get_alias_idx - get an alias name index
 *
 * @name: alias name
 * @gb: globals
 *
 * Return: index if found else -1
 */
int get_alias_idx(char *name, glob_t *gb)
{
	int idx;
	int namelen = _strlen(name);

	for (idx = 0; gb->aliases[idx]->name != NULL; idx++)
		if (_strncmp(gb->aliases[idx]->name, name, namelen) == 0)
			return (idx);
	return (-1);
}

/**
 * get_alias - get an alias name value
 *
 * @name: alias name
 * @gb: globals
 *
 * Return: alias value if found else NULL
 */
char *get_alias(char *name, glob_t *gb)
{
	int idx = get_alias_idx(name, gb);

	if (idx != -1)
		return (gb->aliases[idx]->value);
	return (NULL);
}

/**
 * count_aliases - count aliases
 *
 * @aliases: aliases
 *
 * Return: amount of aliases
 */
int count_aliases(alias_t **aliases)
{
	int idx;

	for (idx = 0; aliases[idx]->name != NULL; idx++)
		;
	return (idx);
}

/**
 * set_alias - get an alias name value
 *
 * @name: alias key
 * @value: alias value
 * @gb: globals
 *
 * Return: 0 if successful else 1
 */
int set_alias(char *name, char *value, glob_t *gb)
{
	int idx, len = count_aliases(gb->aliases);
	alias_t **new_mem;

	idx = get_alias_idx(name, gb);
	if (idx == -1)
	{
		free(gb->aliases[len]);
		new_mem = _realloc(gb->aliases, in_char(len + 1), in_char(len + 2));
		if (new_mem == NULL)
			return (free(new_mem), 1);
		new_mem[len] = new_alias(name, value);
		if (new_mem[len] == NULL)
		{
			free(new_mem[len]);
			return (free(new_mem), 1);
		}
		new_mem[len + 1] = null_alias();
		if (new_mem[len + 1] == NULL)
		{
			free(new_mem[len]);
			free(new_mem[len + 1]);
			return (free(new_mem), 1);
		}
		gb->aliases = new_mem;
	}
	else
	{
		free(gb->aliases[idx]->value);
		gb->aliases[idx]->value = clone_str(value);
		if (gb->aliases[len]->value)
			return (free(gb->aliases[len]->value), 1);
	}
	return (0);
}

/**
 * list_alias - writes all aliases to
 * stdout
 *
 * @gb: globals
 */
void list_alias(glob_t *gb)
{
	int idx = 0;

	for (; gb->aliases[idx]->name != NULL; idx++)
		format_alias(gb->aliases[idx]->name, gb->aliases[idx]->value);
}
