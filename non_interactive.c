#include "shell.h"

/**
 * c_ignore - custom ignores spaces and newlines
 * (e.g. echo "ls\n ls" | ./a.out)
 * @str: envrionmental variables
 * Return: new string
 */
char *c_ignore(char *str)
{
	while (*str == ' ' || *str == '\n')
		str++;
	return (str);
}

/**
 * non_interactive - handles when user pipes commands into shell via pipeline
 * (e.g. echo "ls/nls -al/n" | ./a.out)
 * @env: envrionmental variables
 */
void non_interactive(list_t *env)
{
	size_t size, i = 0, n = 0;
	int command_line_no = 0, exit_stat = 0;
	char *command = NULL, *n_command = NULL, *n_line, **token;

	i = getline(&command, &size, stdin);
	if (i == 0)
	{
		free(command);
		exit(0);
	}
	n_command = command;
	command = c_ignore(command);
	n_line = strtok(command, "\n"); /* tokenize each command string */
	if (n_command != NULL)
		free(n_command);
	n = 0;
	while (n_line[n] != '\0')
	{
		command_line_no++;
		token = NULL; /* tokenize each command in array of commands */
		*token = strtok(n_line, " ");
		exit_stat = _builtin(token[0])(token, env, command);
		if (exit_stat)
		{
			n++;
			continue;
		}
		exit_stat = execute(token, env);
		n++;
	}
	free(n_line);
	free_list(env);
	exit(exit_stat);
}
