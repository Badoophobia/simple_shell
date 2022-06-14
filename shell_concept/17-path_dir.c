#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

char *_getenv(const char *name)
{
	int index, len;
	extern char **environ;

	len = strlen(name);
	for (index = 0; environ[index]; index++)
	{
		if (strncmp(name, environ[index], len) == 0)
			return (environ[index]);
	}

	return (NULL);

}

int path_dir(char *env)
{
	char *token, *var; 
	
	var = _getenv(env);
	token = strtok(var, ":");
	while (token != NULL)
	{
		printf("%s\n", token);
		token = strtok(NULL, ":");
	}

   	return(0);
}

int main ()
{
	path_dir("PATH");
	printf("\n");
	printf("\n");
	path_dir("HOME");
	printf("\n");
	printf("\n");
	path_dir("ROOT");

return (0);

}
