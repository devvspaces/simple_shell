#include "main.h"

/**
 * format_alias - print name and value to
 * stdout using alias format
 *
 * @name: alias name
 * @value: alias value
 */
void format_alias(char *name, char *value)
{
	write_stdout(name);
	write_stdout("='");
	write_stdout(value);
	write_stdout("'\n");
}

/**
 * new_alias - create new alias mem
 *
 * @name: alias key
 * @value: alias value
 *
 * Return: pointer to memory is success else NULL
 */
alias_t *new_alias(char *name, char *value)
{
	alias_t *mem = malloc(sizeof(alias_t));

	if (mem == NULL)
	{
		free(mem);
		return (NULL);
	}

	mem->name = clone_str(name);
	if (mem->name == NULL)
		return (NULL);

	mem->value = clone_str(value);
	if (mem->value == NULL)
		return (NULL);

	return (mem);
}

/**
 * null_alias - create new null alias mem
 *
 * Return: pointer to memory is success else NULL
 */
alias_t *null_alias(void)
{
	alias_t *mem = malloc(sizeof(alias_t));

	if (mem == NULL)
	{
		free(mem);
		return (NULL);
	}

	mem->name = NULL;
	mem->value = NULL;
	return (mem);
}

/**
 * init_aliases - initialize a new null
 * terminated alias array with an initial
 * null alias.
 *
 * Return: initialized aliases if success
 * else NULL
 */
alias_t **init_aliases(void)
{
	alias_t **init, *null;

	init = malloc(in_char(1));
	if (init == NULL)
	{
		free(init);
		return (NULL);
	}

	null = null_alias();
	if (null == NULL)
	{
		free(null);
		return (NULL);
	}

	init[0] = null;
	return (init);
}
