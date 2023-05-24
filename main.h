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

/* Global variables */
extern int last_command_status;

/* Global Shell name */
extern char *name;

/* Global Enviroment */
extern char **environ;

/* Global cmd count */
extern int cmd_count;

size_t in_char(int n);
int count_nt_list(const void *list);
char **clone_env();
void free_env(void);
int (*is_builtin(char *name))(char **, int, char **);
int _isdigit(char c);
void *_calloc(unsigned int nmemb, unsigned int size);
char *_strcat(char *dest, const char *src);
int _strncmp(const char *s1, const char *s2, int n);
int _strcmp(const char *s1, const char *s2);
char *_strcpy(char *dest, char *src);
char *_memcpy(void *dest, const void *src, unsigned int n);
int _strlen(const char *str);
char *_getenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
char **parse_commands_delim(char *command, int cmd_len, char *delim);
char **parse_command(char *command, int cmd_len);
char **parse_commands(char *command, int cmd_len);
int runcmd(char **cmd, char **argv);
char *clone_str(char *val);
char *which(char *cmd);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
int is_delim(char c, const char *delim);
char *_strtok(char *val, char *delim);
int exec_cmd(char *line, int len);
int _unsetenv(const char *name);
int write_fd(int fd, const char *buf);
int write_stderr(const char *buf);
int write_stdout(const char *buf);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void *_calloc(unsigned int nmemb, unsigned int size);
char *_itoa(int num);
void cd_error(char *path);
void free_argv(char **argv);

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
	int (*func)(char **, int ac, char **argv);
} _builtin;

int exec_builtin(char **cmd, int (*f)(char **, int, char **), char **av);

int _bi_exit(char **cmd, int ac, char **argv);
int _bi_env(char **cmd, int ac, char **argv);
int _bi_setenv(char **cmd, int ac, char **argv);
int _bi_unsetenv(char **cmd, int ac, char **argv);
int _bi_cd(char **cmd, int ac, char **argv);

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
