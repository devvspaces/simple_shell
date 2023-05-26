#include "main.h"

/**
 * file_open_error - print file
 * open error
 *
 * @path: file path
 * @gb: globals
 */
void file_open_error(char *path, glob_t *gb)
{
	char *cmd_count_str;

	cmd_count_str = _itoa(gb->cmd_count);
	write_stderr(gb->name);
	write_stderr(": ");
	write_stderr(cmd_count_str);
	write_stderr(": cannot open ");
	write_stderr(path);
	write_stderr(": No such file\n");
	free(cmd_count_str);
}
