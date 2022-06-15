#ifndef SHELL_H
#define SHELL_H
#include <signal.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <wait.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>

#define BUFSIZE 1024
extern char **environ;

/**
  * struct builtin_commands - stuct for function pointers to builtin commands
  * @cmd_str: commands (env, cd, alias, history)
  * @fun: function
  */
typedef struct builtin_commands
{
	char *cmd_str;
	int (*fun)();
} builtin_t;


/**
 * struct env_path - linked list for environmental variables
 * @str: holds environmental variable string
 * @len: holds the length of the string
 * @next: points to next node
 */
typedef struct env_path
{
	char *str;
	unsigned int len;
	struct env_path *next;

} list_t;

/* In builtin.c */
int (*_builtin(char *cmd))();
int _exit_builtin(char **tokens, list_t *linkedlist_path, char *buffer);
int _cd(char **tokens);
int _alias(void);
int _history(void);

/* env_func.c */
char *_getenv(char *name);
int _setenv(char **tokens);
int _unsetenv(char **tokens);
int current_env(char **tokens, list_t *environment);

/* linkedlist.c */
list_t *add_node(list_t **head, char *str, unsigned int len);
list_t *path_list(void);
list_t *environ_list(void);
char *_which(char *cmd, list_t *linkedlist_path);
void free_list(list_t *head);

/* execute.c */
int execute(char *argv[], list_t *linkedlist_path);
char **split_line(char *line);
void ctrl_D(int i, char *cammand, list_t *env);
void ctrl_c(int n);

/* memory.c */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void free_double_ptr(char **str);
void __exit(char **str, list_t *env);

/* strings2.c*/
char *_strcpy(char *dest, char *src);
int _putchar(char c);
void _puts(char *str);
int _isnumber(int c);
int _strlen(char *s);

/* strtok.c */
char *_strchr(char *s, char c);
unsigned int _strspn(char *s, char *accept);
char *_strpbrk(char *s, char *delims);
char *_strtok(char *s, char *delim);

/* string1.c */
int _strcmp(char *s1, char *s2);
int _strncmp(char *s1, char *s2, size_t bytes);
char *_strcat(char *dest, char *src);
char *_strdup(char *src);
int _atoi(char *s);

/* non_interactive */
char *c_ignore(char *str);
void non_interactive(list_t *env);

#endif
