#ifndef __MAIN_H__
#define __MAIN_H__
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/wait.h>
#include <limits.h>
#include <errno.h>

/**
 * struct glob - struct containing data
 * that are dependencies in deep functions
 *
 * @name: name of the shell
 * @cmd_count: current command count
 * @exit_status: previous exit status
 * @environ: global enviroment variable
 */
typedef struct glob
{
	char *name;
	int cmd_count;
	int exit_status;
	char **environ;
} glob_t;

/* Utilities */
size_t in_char(int n);
int count_nt_list(const void *list);
int _isdigit(char c);
char *_itoa(int num);

/* String helpers */
char *_strcat(char *dest, const char *src);
int _strncmp(const char *s1, const char *s2, int n);
int _strcmp(const char *s1, const char *s2);
char *_strcpy(char *dest, char *src);
int _strlen(const char *str);
char *clone_str(char *val);
char *lstrip(char *val, char *tok);
long _strtol(const char *nptr, char **endptr, int base);

/* Enviroment helpers */
char **clone_env();
void free_env(glob_t *gb);
int _getenv_idx(const char *name, glob_t *gb);
char *_getenv(const char *name, glob_t *gb);
int _setenv(const char *name, const char *value, int overwrite, glob_t *gb);
int _unsetenv(const char *name, glob_t *gb);

/* Parser functions */
char **parse_commands_delim(char *command, int cmd_len, char *delim);
char **parse_command(char *command, int cmd_len);
char **parse_commands(char *command, int cmd_len);

/* Command helpers */
char *which(char *cmd, glob_t *gb);
int runcmd(char **cmd, char **argv, glob_t *gb);
int exec_cmd(char *line, int len, glob_t *gb);
void free_argv(char **argv);

/* Read helpers */
char *_strtok(char *val, char *delim);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
int is_delim(char c, const char *delim);

/* Write helpers */
int write_fd(int fd, const char *buf);
int write_stderr(const char *buf);
int write_stdout(const char *buf);

/* Memory helpers */
char *_memcpy(void *dest, const void *src, unsigned int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void *_calloc(unsigned int nmemb, unsigned int size);

/* Error helpers */
void print_err(char *cmd, glob_t *gb);
void cd_error(char *path, glob_t *gb);
void cmd_404_error(char *path, glob_t *gb);
void exit_error(char *val, glob_t *gb);
void syntax_error(char *val, glob_t *gb);

/* Builtins */

/**
 * struct builtin - A structure that holds information
 * about a builtin function
 *
 * @name: The name of the function
 * @func: Function pointer to the
 * builtin function to run
 */
typedef struct builtin
{
	char *name;
	int (*func)(char **, int ac, char **argv, glob_t *);
} _builtin;

int (*is_builtin(char *name))(char **, int, char **, glob_t *);
int exec_builtin(
	char **cmd,
	int (*f)(char **, int, char **, glob_t *),
	glob_t *gb, char **av);

int _bi_exit(char **cmd, int ac, char **argv, glob_t *gb);
int _bi_env(char **cmd, int ac, char **argv, glob_t *gb);
int _bi_setenv(char **cmd, int ac, char **argv, glob_t *gb);
int _bi_unsetenv(char **cmd, int ac, char **argv, glob_t *gb);
int _bi_cd(char **cmd, int ac, char **argv, glob_t *gb);

/* Aliases */

/**
 * struct alias - A structure that holds information
 * about an alias
 *
 * @name: The name of the function
 * @value: alias value
 */
typedef struct alias
{
	char *name;
	char *value;
} _alias;

#endif
