#include "shell.h"

/**
 * env_linked_list - creates a linked list from environmental variables
 * @env: environmental variables
 * Return: linked list
 */
list_t *env_linked_list(char **env)
{
	list_t *head;
	int i = 0;

	head = NULL;
	while (env[i] != NULL)
	{
		add_end_node(&head, env[i]);
		i++;
	}
	return (head);
}

int main(int __attribute__((__unused__))ac, char **env)
{
	list_t *head;
	
	head = NULL;
	*env = _getenv("PATH");
	/*char **p = &(_getenv("PATH"));*/
	
	env_linked_list(env);
	print_list(head);

	return (0);
	
}
