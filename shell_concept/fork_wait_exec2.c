#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void create_child_wait(pid_t child_pid, int status, int i);

/**
 * main - exercise: fork + wait + execve
 *
 * Return: Always 0
 */
int main(void)
{
	int i = 1, status;
	char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};
	pid_t child_pid;

	child_pid = fork();

	create_child_wait(child_pid, status, i);
	create_child_wait(child_pid, status, i);
	create_child_wait(child_pid, status, i);
	create_child_wait(child_pid, status, i);		

	if (child_pid != 0)
		wait(&status);

	if (child_pid == 0)
	{
		printf("Child process %d\n", i);
		if (execve(argv[0], argv, NULL) == -1)
			perror("Error");
	}
	else
		printf("Parent process\n");

	return (0);
	
}

void create_child_wait(pid_t *child_pid, int *status, int *i)
{
	if (child_pid != 0)
	{
		wait(&(*status));
		*child_pid = fork();
		*i = *i + 1;
	}
}
