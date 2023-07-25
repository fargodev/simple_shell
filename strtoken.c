#include "header.h"

/**
  * _strtok - string tokenization
  * @str: string to tokenize
  * @delim: string whitespaces or terminating point
  *
  * Return: pointer to string position with null terminator
  */
char *_strtok(char *str, const char *delim)
{
	static char *str_begin, *str_end, *end;
	unsigned int i, j;
	int word_found = 0;

	if (str == NULL)
	{
		if (str_begin == NULL || str_end == NULL)
			return (NULL);
		str = end + 1;
	}
	else
		str_end = str + _strlen(str);
	for (i = 0; str + i < str_end; 
