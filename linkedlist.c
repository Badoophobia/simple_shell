#include "shell.h"


/**
  * add_node - adds a new node to the end of a linked list
  * @head: head of the linked list
  * @str: string
  * @len: length of the string
  * Return: pointer to the current position in the list
  **/
list_t *add_node(list_t **head, char *str, unsigned int len)
{
	list_t *new, *holder;
	char *dupstr;

	if (str == NULL)
		return (NULL);
	dupstr = strdup(str);
	if (dupstr == NULL)
	{
		/*free(dupstr);*/
		return (NULL);
	}
	new = malloc(sizeof(list_t));
	if (new == NULL)
		return (NULL);
	new->str = dupstr;
	new->len = len;
	new->next = NULL;

	if (*head == NULL)
	{
		*head = new;
		return (*head);
	}
	holder = *head;
	while (holder->next != NULL)
		holder = holder->next;
	holder->next = new;
	/*free(dupstr);*/
	return (*head);
}
/**
  * path_list - builds a linked list from PATH
  * Return: pointer to linked list
  */
list_t *path_list(void)
{
	unsigned int len, i, j;
	char *env;
	char buffer[1024];
	list_t *dir;

	dir = NULL;
	/*buffer = malloc(sizeof(char) * BUFSIZE);*/
	len = i = j = 0;
	env = _getenv("PATH");
	while (*env)
	{
		buffer[j++] = *env;
		len++;
		if (*env == ':')
		{
			len--;
			buffer[j - 1] = '/';
			buffer[j] = '\0';
			add_node(&dir, buffer, len);
			len = j = 0;
		}
		env++;
		/*free(buffer);*/
	}
	return (dir);
}

/**
  * environ_list - builds a linked list from PATH
  * Return: pointer to linked list
  */
list_t *environ_list(void)
{
	int i, j;
	char **env;
	list_t *path;

	path = NULL;
	i = j = 0;
	env = environ;
	while (env[i])
	{
		add_node(&path, env[i], (unsigned int)_strlen(env[i]));
		i++;
	}
	return (path);
}



/**
 * _which - finds the path of a command
 * @cmd: command
 * @linkedlist_path: linked list from the PATH
 * Return: absolute path if successful, NULL otherwise
*/

char *_which(char *cmd, list_t *linkedlist_path)
{
	int status;
	char *abs_path;
	list_t *path;

	path = linkedlist_path;
	if (path == NULL || cmd == NULL)
		return (NULL);
	if ((_strncmp(cmd, "/", 1) == 0
			|| _strncmp(cmd, "./", 2) == 0)
			&& access(cmd, F_OK | X_OK) == 0)
	{
		abs_path = _strdup(cmd);
		return (abs_path);
		/*free(abs_path);*/
	}
	while (path != NULL)
	{
		abs_path = strdup(path->str);
		if (abs_path == NULL)
		{
			/*free(abs_path);*/
			return (NULL);
		}
		/*free(abs_path);*/
		abs_path = _strcat(abs_path, cmd);
		if (abs_path == NULL)
			return (NULL);
		status = access(abs_path, F_OK | X_OK);
		if (status == 0)
			return (abs_path);
		free(abs_path);
		path = path->next;
	}
	return (NULL);
}

/**
  * free_list - frees a list
  * @head: beginning of the list
  */
void free_list(list_t *head)
{
	list_t *holder;

	while (head != NULL)
	{
		holder = head;
		head = head->next;
		free(holder->str);
		free(holder);
	}
}
