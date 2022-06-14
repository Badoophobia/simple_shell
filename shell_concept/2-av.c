#include <stdio.h>
#include <stdlib.h>
/**
 *main-prototype
 *@ac:argument 1
 *@av:argument 2
 *Return: 0
 */
int main(int __attribute__((__unused__))ac, char **av)
{
	int i = 0;

	for ( i = 1; av[i] != NULL; i++)
	{
		printf("%s\n", av[i]);
	}
	printf("\n");
	return (0);
}
