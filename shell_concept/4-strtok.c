#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 *main-prototype
 *Return: 0
 */
int main(void)
{
	char *buffer;
	size_t len = 1024;
	char *token;
	int read;
	
	buffer = malloc(sizeof(size_t) * len);
	while (1)
	{
		printf("$ ");
		read = getline(&buffer, &len, stdin);
		if (read != EOF)
			printf("buffer getline: %s", buffer);
	
		token = strtok(buffer, " ");
		while (token)
		{
			printf("buffer strtok: %s\n", token);
			token = strtok(NULL, " ");
		}
	}
	return (0);
}
