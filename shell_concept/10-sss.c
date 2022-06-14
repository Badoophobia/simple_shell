#include "shell.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 * main - exercise: fork + wait + execve
 *
 * Return: Always 0
 */

int main(void)
{
	char *buffer;
	size_t len = 1024;
	int read, status;
	pid_t child_pid;
	char *argv[] = {"/bin/ls", "-l", "/usr/", NULL};

	buffer = malloc(sizeof(size_t) * len);

	while (1)
	{
		printf("$ ");
		read = getline(&buffer, &len, stdin);
		/*if (read != EOF)
		*	buffer = argv[ac++];*/
		
		child_pid = fork();
		if (child_pid == -1)
			return (1);
		if (child_pid == 0)
		{
			execve(argv[0], argv, NULL);
		}
		else
			wait(&status);

		if (read == EOF)
		{
			free(buffer);
			continue;
		}
		
	}

	return (0);


}
