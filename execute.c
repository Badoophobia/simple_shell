#include "shell.h"

/**
 * split_line - splits the data from standard input
 * @line: data from standard input
 * Return: an array of pointers if successful
*/

char **split_line(char *line)
{
	int bufsize = 1024, position = 0;
	char *delimeter =  " \t\r\n\a";
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;
	char *s = malloc(bufsize * sizeof(char));

	_strcpy(s, line);

	if (!tokens)
	{
		perror("allocation error");
		exit(1);
	}

	token = strtok(s, delimeter);
	/*free(s);*/
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += 1024;
			tokens = _realloc(*tokens, token[position], bufsize * sizeof(char *));
			if (!tokens)
			{
				perror("allocation error");
				exit(1);
			}
		}

		token = strtok(NULL, delimeter);
		/*free(tokens);*/
		/*free_double_ptr(tokens);*/
	}
	tokens[position] = NULL;
	return (tokens);
}


/**
  * execute - executes a command
 (* by searching through PATH
  * @argv: array of tokens, ie. argument vectors
  * @linkedlist_path: PATH in LL form
  * Return: 0 on success, -1 on failure
  */
int execute(char *argv[], list_t *linkedlist_path)
{
	pid_t child_pid;
	char *abs_path;
	int status = 0;

	if (access(argv[0], F_OK) == 0) /* check access to abs path */
	{
		abs_path = argv[0];
		status = 1;
	}
	else /* if not, search through the path list */
		abs_path = _which(argv[0], linkedlist_path);
	
	if (access(abs_path, X_OK) != 0) /* if not, executable */
	{
		free_double_ptr(argv);
		return (127);
	}
	else
	{
		child_pid = fork();
		if (child_pid == 0)
		{
			if (execve(abs_path, argv, environ) == -1)
			{
				perror("execution failed\n");
				__exit(argv, linkedlist_path);
			}
		}
		else
		{
			wait(&status);
			if (status == 0)
				free(abs_path);
		}

	}
	return (0);
}

/**
 * ctrl_c - ignore Ctrl-C input and prints prompt again
 * @n: takes in int from signal
 */
void ctrl_c(int n)
{
	(void)n;
	write(STDOUT_FILENO, "\n$ ", 3);
}


/**
 * ctrl_D - exits program if Ctrl-D was pressed
 * @i: characters read via get_line
 * @command: user's typed in command
 * @env: environmental variable linked list
 */
void ctrl_D(int i, char *command, list_t *env)
{
	if (i == 0) /* handles Ctrl+D */
	{
		free(command); /* exit with newline if in shell */
		free_list(env);
		if (isatty(STDIN_FILENO))/* ctrl+d prints newline */
			write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}
}
