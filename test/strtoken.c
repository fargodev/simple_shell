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
	static char *begin, *str_end, *end;
	unsigned int i, j;
	int word_found = 0;

	if (str == NULL)
	{
		if (begin == NULL || end == NULL)
			return (NULL);
		str = end + 1;
	}
	else
		str_end = str + _strlen(str);
	for (i = 0; str + i < str_end; i++)
	{
		for (j = 0; delim != NULL && delim[j] != '\0'; j++)
		{
			if (str[i] == delim[j])
			{
				if (word_found == 1)
				{
					str[i] = '\0';
					end = str + i;
					return (begin);
				}
				break;
			}
		}
		if (delim[j] == '\0' && word_found == 0)
		{
			word_found = 1;
			begin = str + i;
		}
	}
	end = NULL;
	if (word_found == 1)
		return (begin);
	return (NULL);
}
