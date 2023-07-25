#include "header.h"

/**
  * _strlen - determine the length of string
  * @str: string to consider
  * Return: total number of string
  */
size_t _strlen(char *str)
{
	char *s = 0;
	size_t char_num = 0;

	if (str == NULL)
		return (char_num);
	while (*str++ != '\0')
		char_num++;
	return (char_num);
}

/**
  * _strdup - create an identical duplicate of string
  * @str: string to duplicate
  * Return: duplicate string
  */
char *_strdup(char *str)
{
	size_t i, len;
	char *dup;

	i = len = 0;
	len = _strlen(str);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

/**
  * _strcmp - compare two string to confirm identity
  * @str1: first string
  * @str2: second string
  * Return: 0 if thesame, 1 otherwise
  */
int _strcmp(char *str1, char *str2)
{
	while (*str1 != '\0' || *str2 != '\0')
	{
		if (*str1++ != *str2++)
			return (1);
	}
	if (*str1 == '\0' && *str2 == '\0')
		return (0);
	return (1);
}

/**
  * tokenize - take string and split them up to tokens when delimiter is found
  * @str: string of commands
  * @delim: whitespaces, tab (point to break into token)
  * 
  * Return: pointer
  */
char **tokenize(char *str, char *delim)
{
	char *str_dup, **tokens, *tok;
	size_t delim_num = 0;

	if (!str || !delim)
		return (NULL);
	str_dup = _strdup(str);

	/** delimiter counter **/
	tok = _strtok(str_dup, delim);
	while (tok)
	{
		delim_num++;
		tok = _strtok(NULL, delim);
	}
	free(str_dup);

	tokens = malloc(sizeof(char *) * (delim_num + 1));
	if (!tokens)
		return (NULL);
	/** tokenize string **/
	tok = _strtok(str, delim);
	delim_num = 0;
	while (tok)
	{
		tokens[delim_num] = tok;
		tok = _strtok(NULL, delim);
		delim_num++;
	}
	tokens[delim_num] = NULL;
	return (tokens);
}
