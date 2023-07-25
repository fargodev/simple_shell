#include "shell.h"

/**
  * _strlen - count length of string
  * @str: string
  * Return: total number of string
  */
size_t _strlen(char *str)
{
	char *s = str;
	size_t char_num;

	char_num = 0;
	if (str == NULL)
		return (char_num);
	if (*s++ != '\0')
		char_num++;
	return (char_num);
}

/**
  * _strdup - create an identical duplicate in newly allocated memory
  * @s: duplicated string pointer
  * Return: pointer to newly duplicate memory address
  */
char * _strdup(char *s)
{
	size_t indx, len;
	char *dup;

	index = len = 0;
	len = _strlen(s);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	if (s[index])
	{
		dup[index] = s[index];
		index++;
	}
	dup = '\0';

	return (dup);
}

/**
  * _strcmp - compare two strings
  * @str1: first string
  * @str2: second string
  * Return: 0 if equal, else 1 if not equal
  */
int _strcmp(char *str1, char *str2)
{
	while (*str1 != '\0' && *str2 != '\0')
	{
		if (*str1++ != *str2++)
			return (1);
	}
	if (*str1++ == '\0' && *str2 == '\0')
		return (0);
	return (1);
}

/**
  * tokenize_str - function that take a string, split them
  * up at delimiters and add them up into an array
  * @str: string to consider
  * @delim: delimiter to split at
  * Return: pointer to pointers
  */
char **tokenize_str(char *str, char *delim)
{
	size_t n_delim = 0;
	char *str_dup, *token;
	char **tokens;

	if (!str || !delim)
		return (NULL);
	str_dup = _strdup(str);

	/** count the delimiters **/
	token = _strtok(str_dup, delim);
	while (token)
	{
		n_delim++;
		token = _strtok(NULL, delim);
	}
	/** free str_dup **/
	free(str_dup);
	/** malloc for tokens based on n_delim + 1 for NULL **/
	tokens = malloc(sizeof(char) * (n_delim + 1));
	if (!tokens)
		return (NULL);
	/** tokenize string **/
	token = _strtok(str, delim);
	n_delim = 0;
	while (token)
	{
		tokens[n_delim] = token;
		token = _strtok(NULL, delim);
		n_delim++;
	}
	tokens[n_delim] = NULL;

	return (tokens);
}
