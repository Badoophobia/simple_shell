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
	int i = 1, status;
	pid_t child_pid;

	child_pid = fork();
	if (child_pid != 0)
	{
		wait(&status);
		child_pid = fork();
		i++;
	}

	if (child_pid != 0)
	{
		wait(&status);
		child_pid = fork();
		i++;
	}

	if (child_pid != 0)
	{
		wait(&status);
		child_pid = fork();
		i++;
	}

	if (child_pid != 0)
	{
		wait(&status);
		child_pid = fork();
		i++;
	}

	if (child_pid != 0)
		wait(&status);

	if (child_pid == 0)
		printf("Child process %d\n", i);
	else
		printf("Parent process\n");

	return (0);
	
}
