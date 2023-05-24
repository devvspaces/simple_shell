#include "main.h"

/**
 * print_err - print a sh format
 * error.
 *
 * @cmd: executable or builtin command name
 */
void print_err(char *cmd)
{
	char *cmd_count_str;

	cmd_count_str = _itoa(cmd_count);
	write_stderr(name);
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
 */
void cd_error(char *path)
{
	print_err("cd");
	write_stderr("can't cd to ");
	write_stderr(path);
	write_stderr("\n");
}
