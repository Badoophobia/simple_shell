#include "shell.h"

/**
 * _strchr - checks for a char in a string
 * @s: the string
 * @c: the char being searched for
 * Return: pointer to char on success, NULL on failure
 */
char *_strchr(char *s, char c)
{
	int len, n;

	len = _strlen(s);
	for (n = 0; n < len; n++)
	{
		if (*(s + n) == c)
			return (s + n);
	}
	s = '\0';
	return (s);
}
/**
 * _strspn - gets length of a substring
 *
 * @s: string to be searched
 * @accept: string to match
 * Return: number of matching bytes
 */
unsigned int _strspn(char *s, char *accept)
{
	int s_len, n, result;

	s_len = _strlen(s);
	n = 0;
	result = 0;
	while (n < s_len)
	{
		if (_strchr(accept, *(s + n)))
			result++, n++;
		else
			return (result);
	}
	return (result);
}
/**
 * _strpbrk - searches through a string for any set of bytes.
 * @s: string to search through
 * @delims: bytes to search for in the string.
 * Return: pointer to first occurence in s of anything in accept
 */
char *_strpbrk(char *s, char *delims)
{
	char *temp;

	temp = delims;
	for (; *s != '\0'; s++)
	{
		while (*delims != '\0')
		{
			if (*s == *delims)
				return (s);
			delims++;
		}
		delims = temp;
	}
	if (*s == '\0')
		return (0);

	return (s);
}
/**
 * _strtok- replicates strtok, a tokenizer
 * @s: string to be tokenized
 * @delim: delimiter that determines where we split s
 * (@save_ptr: saves index in tokenized s so that repeated
 * fn calls fetch tokens
 * Return: pointer to next token
 */
char *_strtok(char *s, char *delim)
{
	char *token;

	if (s == NULL)
		return (NULL);

	s += _strspn(s, delim);
	if (*s == '\0')
		return (NULL);

	token = s;
	s = _strpbrk(token, delim);
	if (s != NULL)
		*s = '\0';

	return (token);
}
