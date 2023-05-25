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
 * struct alias - A structure that holds information
 * about an alias
 *
 * @name: Alias name
 * @value: alias value
 */
typedef struct alias
{
	char *name;
	char *value;
} alias_t;

/**
 * struct glob - struct containing data
 * that are dependencies in deep functions
 *
 * @name: name of the shell
 * @cmd_count: current command count
 * @exit_status: previous exit status
 * @environ: global enviroment variable
 * @aliases: aliases variable
 */
typedef struct glob
{
	char *name;
	int cmd_count;
	int exit_status;
	char **environ;
	alias_t **aliases;
} glob_t;

/* Utilities */
size_t in_char(int n);
int count_nt_list(const void *list);
int _isdigit(char c);
char *_itoa(int num);

/* Memory freeing utility */
void free_alias(glob_t *gb);
void free_env(glob_t *gb);
void free_argv(char **argv);

/* String helpers */
char *_strcat(char *dest, const char *src);
int _strncmp(const char *s1, const char *s2, int n);
int _strcmp(const char *s1, const char *s2);
char *_strcpy(char *dest, char *src);
int _strlen(const char *str);
char *clone_str(char *val);
char *lstrip(char *val, char *tok);
char *rstrip(char *val, char *tok);
char *strip(char *val, char *tok);
long _strtol(const char *nptr, char **endptr, int base);
char *_strncpy(char *dest, const char *src, int n);
char *_strstr(char *haystack, const char *needle);
char *replace(char *str, const char *tok, const char *replacement);

/* Enviroment helpers */
char **clone_env();
int _getenv_idx(const char *name, glob_t *gb);
char *_getenv(const char *name, glob_t *gb);
int _setenv(const char *name, const char *value, int overwrite, glob_t *gb);
int _unsetenv(const char *name, glob_t *gb);

/* Parser functions */
char **parse_commands_delim(char *command, int cmd_len, char *delim);
char **get_str_tokens(char *command, char *delim);

/* Command helpers */
char *which(char *cmd, glob_t *gb);
int runcmd(char **cmd, char **argv, glob_t *gb);
int exec_cmd(char *line, int len, glob_t *gb);
char *replace_variables(char *cmd, glob_t *gb);
int check_syntax_error(char *line, glob_t *gb);
void handle_comment(char *input);
void *syntax_format(char cause, glob_t *gb);

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
int _bi_alias(char **cmd, int ac, char **argv, glob_t *gb);

/* Aliases helpers */
char **spilt_action(char *str);
void format_alias(char *name, char *value);
alias_t *new_alias(char *name, char *value);
alias_t *null_alias(void);
alias_t **init_aliases(void);
int get_alias_idx(char *name, glob_t *gb);
char *get_alias(char *name, glob_t *gb);
int set_alias(char *name, char *value, glob_t *gb);
void list_alias(glob_t *gb);

#endif
