#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>

/**
 * struct list - linked list for environmental variables
 * @var: holds environmental variable string
 * @next: points to next node
 */
typedef struct list
{
	char *var;
	struct list *next;

} list_t;

#define MAXARGS 128 /* maxargs in struct can't be variable, use define */

struct command{
	int argc; /* number of args */
	char *argv[MAXARGS]; /* arguments list */
	enum built_t{ /* is argv[0] a builtin command? */
		NONE, QUIT, JOBS, BG, FG
	} builtin;
};

char *_getenv(const char *name);
void eval(char *cmdline);
int parse(const char *cmdline, struct command *cmd);
void runSystemCommand(struct command *cmd, int bg);
list_t *env_linked_list(char **env);
list_t *add_end_node(list_t **head, char *str);
size_t print_list(list_t *h);
int delete_nodeint_at_index(list_t **head, int index);
void free_linked_list(list_t *list);

#endif
