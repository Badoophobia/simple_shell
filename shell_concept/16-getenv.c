#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

int main () {
   printf("PATH : %s\n", _getenv("PATH"));
   printf("HOME : %s\n", _getenv("HOME"));
   printf("ROOT : %s\n", _getenv("ROOT"));

   return(0);
}
