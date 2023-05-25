#include "main.h"

/**
 * print_err - print a sh format
 * error.
 *
 * @cmd: executable or builtin command name
 * @gb: globals
 */
void print_err(char *cmd, glob_t *gb)
{
	char *cmd_count_str;

	cmd_count_str = _itoa(gb->cmd_count);
	write_stderr(gb->name);
	write_stderr(": ");
	write_stderr(cmd_count_str);
	write_stderr(": ");
	write_stderr(cmd);
	write_stderr(": ");
	free(cmd_count_str);
}

/**
 * cd_error - print cd error
 *
 * @path: executable or builtin command name
 * @gb: globals
 */
void cd_error(char *path, glob_t *gb)
{
	print_err("cd", gb);
	write_stderr("can't cd to ");
	write_stderr(path);
	write_stderr("\n");
}

/**
 * cmd_404_error - print which
 * command not found error
 *
 * @path: executable name
 * @gb: globals
 */
void cmd_404_error(char *path, glob_t *gb)
{
	print_err(path, gb);
	write_stderr("not found\n");
}

/**
 * exit_error - print exit error
 *
 * @val: illegal number provided
 * @gb: globals
 */
void exit_error(char *val, glob_t *gb)
{
	print_err("exit", gb);
	write_stderr("Illegal number: ");
	write_stderr(val);
	write_stderr("\n");
}

/**
 * syntax_error - print syntax error
 *
 * @val: error provided
 * @gb: globals
 */
void syntax_error(char *val, glob_t *gb)
{
	print_err("Syntax error", gb);
	write_stderr("\"");
	write_stderr(val);
	write_stderr("\" ");
	write_stderr("unexpected\n");
	errno = 127;
}
