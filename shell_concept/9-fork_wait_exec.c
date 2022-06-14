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
	int id1, id2, id3, status;
	char *argv[] = {"/bin/ls", "-l", "/tmp/", NULL};

	id1 = fork();
	id2 = fork();
	id3 = fork();

	if (id1 == 0)
	{
		if (id2 == 0)
		{
			if (id3 == 0)
			{
				/*printf("1st child\n");*/
				execve(argv[0], argv, NULL);
				sleep(2);
			}
			else
			{
				/*printf("2nd child\n");*/
				execve(argv[0], argv, NULL);
				sleep(2);
			}
		
		}
		else
		{
			if (id3 == 0)
			{
				/*printf("3rd child\n");*/
				execve(argv[0], argv, NULL);
				sleep(2);
			}
			else
				wait(&status);
		}
		
	}
	else
	{
		if (id2 == 0)
		{
			if (id3 == 0)
			{
				/*printf("5th child\n");*/
				execve(argv[0], argv, NULL);
				sleep(2);
			}
			else
			{
				wait(&status);
				sleep(2);
			}

		}

		else
		{
			if (id3 == 0)
			{
				/*printf("4th child\n");*/
				execve(argv[0], argv, NULL);
				sleep(2);
			}
			else
			{
				wait(&status);
				/*printf("Parent\n");*/
			}

		}
	}
	while (wait(NULL) != -1 || errno != ECHILD)
	{
		/*printf("Waited for a child to finish\n");*/
	}
	return (0);
}
