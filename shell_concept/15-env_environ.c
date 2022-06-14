#include <stdio.h>
#include <unistd.h>

/**
 * main - prints the environment
 *
 * Return: Always 0.
 */
int main(int ac, char **av, char **env)
{
    unsigned int i;
    extern char **environ;
	
    i = 0;
    (void)ac;
    (void)av;
    if (env[i] != NULL && environ[i] != NULL)
    {
        printf("env address: %p\n", &(**env));
	printf("environ address: %p\n", &(**environ));
        i++;
    }
    return (0);
}
