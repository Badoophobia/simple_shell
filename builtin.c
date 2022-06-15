#include "shell.h"

/**
  * _builtin - checks if cmd is a builtin
  * @cmd: command to find
  * Return: On success - pointer to function, On Failure - NULL pointer
 (* other useful shell builtins:
 (* pwd, echo, pushd, popd, type
 (* * requires ^Z
 (* fg, bg
 (*  * Requires ^R
 (* reverse-i-search **HISTORY**
*/
int (*_builtin(char *cmd))()
{
	unsigned int i;
	builtin_t builds[] = {
		{"alias", _alias},
		{"cd", _cd},
		{"env", current_env},
		{"exit", _exit_builtin},
		{"history", _history},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{NULL, NULL}
	};

	i = 0;
	while (*builds[i].fun != NULL)
	{
		if (_strncmp(builds[i].cmd_str, cmd, _strlen(builds[i].cmd_str)) == 0)
			return (builds[i].fun);
		i++;
	}
	return (NULL);
}
/**
  * _exit_builtin - Frees any remaining malloc'd spaces, and exits
  * @linkedlist_path: Linked list to free.
  * @buffer: buffer to free
  * @tokens: Check for other inputs
 (* * CHANGE TO VARIADIC LIST.
  * Return: -1 if exit fails.
  */
int _exit_builtin(char **tokens, list_t *linkedlist_path, char *buffer)
{
	unsigned char exit_status;
	int i;

	for (i = 0; tokens[1] && tokens[1][i]; i++)
	{
		if (!_isnumber(tokens[1][i]))
		{
			_puts("numeric argument required, exiting\n");
			break;
		}
	}
	exit_status = tokens[1] && i >= _strlen(tokens[1]) ? _atoi(tokens[1]) : 0;
	if (linkedlist_path && buffer && tokens)
	{
		free_list(linkedlist_path);
		linkedlist_path = NULL;
		free(buffer);
		buffer = NULL;
		free(tokens);
		tokens = NULL;
	}
	exit(exit_status);
	return (-1);
}

/**
  * _cd - changes working directory
  * @tokens: argument list
  * Return: 0 on success
  */
int _cd(char **tokens)
{
	char *target;
	char pwd[BUFSIZE];
	char *home;

	home = _getenv("HOME");
	if (tokens[1])
	{
		if (tokens[1][0] == '~' && !tokens[1][1])
			target = home;
		else if (tokens[1][0] == '-' && !tokens[1][1])
			target = _getenv("OLDPWD");
		else
			target = tokens[1];
	}
	else
		target = home;
	if (target == home)
		chdir(target);
	else if (access(target, F_OK | R_OK) == 0)
		chdir(target);
	else
		_puts("Could not find directory\n");
	setenv("OLDPWD", _getenv("PWD"), 1);
	setenv("PWD", getcwd(pwd, sizeof(pwd)), 1);
	return (0);
}


/**
  * _alias - sets aliases or prints them out when no options are supplied
  * Return: 0
  */
int _alias(void)
{
	_puts("alias: usage: alias [-p] [name[=value] ... ]\n");
	_puts("\tSet or view aliases.\n\tSet with name=value\n");
	_puts("\tView list of aliases with no arugments or -p\n");
	return (0);
}
/**
  * _history - prints out history with no options,
  *  or clears history with -c
  * Return: 0 on success, 1 if history cannot be cleared.
  */
int _history(void)
{
	_puts("history: usage: history [-c]\n");
	_puts("\tView the history of commands\n ");
	_puts("\t'history -c' clears the history\n");
	return (0);
}

