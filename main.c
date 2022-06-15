#include "shell.h"

/**
 * main - main entry point of the program
 * @ac: number of arguments
 * @av: argument list
 * Return: 0 if successful
*/

int main(void)
	
{
	char *buffer, **commands;
	list_t *linkedlist_path, *env_list;
	int characters;
	size_t bufsize = BUFSIZE;
	
	buffer = (char *)malloc(bufsize * sizeof(char));
	if (buffer == NULL)
	{
		perror("Unable to allocate buffer");
		exit(1);
	}
	
	linkedlist_path = path_list();
	env_list = environ_list();
	while (1)
	{
		if (isatty(STDIN_FILENO)) /* reprompt if in interactive shell */
			write(STDOUT_FILENO, "$ ", 3);
		else
			non_interactive(env_list);

		signal(SIGINT, ctrl_c); /* makes ctrl+c not work */
		characters = getline(&buffer, &bufsize, stdin);
		ctrl_D(characters, buffer, env_list);

		commands = split_line(buffer);
		if (_builtin(commands[0]))
			_builtin(commands[0])(commands, linkedlist_path, buffer);
		else
			execute(commands, linkedlist_path);
		free(commands);
	}

	return (0);
}
