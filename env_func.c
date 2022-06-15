#include "shell.h"


/**
 * _getenv - gets the environmental variable as user defines
 * @name: name of environmental variable
 * Return: environmental variable if sucessful, NULL otherwise
*/


char *_getenv(char *name)
{
	int index, len;
	/*extern char **environ;*/

	len = _strlen(name);
	for (index = 0; environ[index]; index++)
	{
		if (_strncmp(name, environ[index], len) == 0)
			return (environ[index]);
	}

	return (NULL);

}


/**
  * _setenv - sets environmental variables as user defines
  * @tokens: KEY=VALUE pair
  * Return: 0 on success, -1 on failure
*/

int _setenv(char **tokens)
{
	int i, status, wc;
	char *key, *value;

	for (i = 0, wc = 1; tokens[1][i]; i++)
		if (tokens[1][i] == '=')
			wc++;
	for (i = 0; tokens[i]; i++)
		;
	if (!tokens[1] || i == 0 || wc != 2)
	{
		_puts("setenv: Usage: setenv KEY=VALUE\n");
		return (-1);
	}
	key = strtok(tokens[1], "=");
	value = strtok(NULL, "=");
	status = setenv(key, value, 0);
	if (status == 0)
		return (status);
	return (-1);
}

/**
  * _unsetenv - unsets environmental variables as user defines
  * @tokens: KEY=VALUE pair
  * Return: 0 on success, -1 on failure
*/

int _unsetenv(char **tokens)
{
	int i, status, wc;
	char *key;

	for (i = 0, wc = 1; tokens[1][i]; i++)
		if (tokens[1][i] == '=')
			wc++;
	for (i = 0; tokens[i]; i++)
		;
	if (!tokens[1] || i == 0 || wc != 2)
	{
		_puts("unsetenv: Usage: unsetenv KEY=VALUE\n");
		return (-1);
	}
	key = strtok(tokens[1], "=");
	/*value = strtok(NULL, "=");*/
	status = unsetenv(key);
	if (status == 0)
		return (status);
	return (-1);
}


/**
  * current_env - prints out the current environment
  * @tokens: tokenized strings
  * @environment: linked list environment
i  * Return: 0 on success, -1 on catastrophic failure
*/

int current_env(char **tokens, list_t *environment)
{
	char **envir;

	if (tokens[1])
		_puts("No arguments are necessary\n");
	envir = environ;
	if (!envir || !environ)
		return (-1);
	for ( ; *envir; envir++)
	{
		write(STDOUT_FILENO, *envir, _strlen(*envir));
		write(STDOUT_FILENO, "\n", 1);
	}
	environment++;
	return (0);
}
