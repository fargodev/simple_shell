#include "header.h"

/**
  * myexit - implementation of simple exit
  * @ptr: pointer containing all malloc'd
  * Return: return success
  */
void myexit(shell_t *ptr)
{
	char *str_exit;
	unsigned int i;

	str_exit = ptr->input_token[1];
	if (str_exit != NULL || ptr != NULL)
	{
		errno = 0;
		for (i = 0; str_exit[i] != '\0'; i++)
			errno = (errno * 10) + (str_exit[i] - '0');
	}
	free_shell(ptr);
	if (errno > 255)
		errno %= 256;
	exit(errno);
}

/**
  * printenv - print current environment
  * @ptr: pointer containin all malloc'd
  * Return: success
  */
void printenv(shell_t *ptr)
{
	char newline = '\n';
	unsigned int i, k;

	(void)ptr;
	if (environ == NULL)
		return;
	for (i = 0; environ[i] != NULL; i++)
	{
		k = _strlen(environ[i]);
		if (k != 0)
		{
			write(STDOUT_FILENO, environ[i], k);
			write(STDOUT_FILENO, &newline, 1);
		}
	}
	errno = 0;
}
