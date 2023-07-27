#include "header.h"

/**
  * print_ps - print primary shell prompt
  * @num: determined which error value to be set
  */
void print_ps(int num)
{
	char ps0[] = "MABERT$ ";
	size_t len_ps0;
	int org_error;

	org_error = errno;
	len_ps0 = _strlen(ps0);
	if (isatty(0))
		write(STDOUT_FILENO, ps0, len_ps0);
	if (num == 0)
		errno = 0;
	else
		errno = org_error;
}

/**
  * getpath - get env path and tokenize it into an arrray
  * @path_modify: pointer to store modified path string
  * Return: array of string
  */
char **getpath(char **path_modify)
{
	char **ptr_token;
	char *path, *delim;
	unsigned int i, j, char_num;

	delim = ":";
	path = _getenv("PATH");
	char_num = _strlen(path);
	*path_modify = malloc(sizeof(char) * (char_num + 2));
	if (char_num == 0)
	{
		(*path_modify)[0] = '.';
		(*path_modify)[1] = '\0';
	}
	else
	{
		for (i = 0, j = 0; path[i] != '\0'; i++)
		{
			if (i == 0 && path[i] == ':')
			{
				(*path_modify)[j++] = '.';
				(*path_modify)[j++] = path[i];
			}
			else if (i == char_num - 1 && path[i] == ':')
			{
				(*path_modify)[j++] = path[i];
				(*path_modify)[j++] = '.';
			}
			else if (path[i] == ':' && path[i + 1] == ':')
			{
				(*path_modify)[j++] = path[i];
				(*path_modify)[j++] = '.';
			}
			else
				(*path_modify)[j++] = path[i];
		}
		for (; j < char_num + 2; j++)
			(*path_modify)[j] = '\0';
	}
	ptr_token = tokenize(*path_modify, delim);
	return (ptr_token);
}

/**
  * find_pathname - locate pathname attached to the associated cmd
  * @path: 2d array pointer to tokenized directory in path
  * @input: input to locate
  * Return: path to input file
  */
char *find_pathname(char **path, char *input)
{
	unsigned int i;
	int cmp_str, found_match;
	struct dirent *filename;
	char *result;
	DIR *directory;

	filename = NULL;
	found_match = 0;
	for (i = 0; path[i] != NULL; i++)
	{
		directory = opendir(path[i]);
		if (directory == NULL)
		{
			errno = EBADF;
			return (NULL);
		}
		while ((filename = readdir(directory)) != NULL)
		{
			cmp_str = _strcmp(filename->d_name, input);
			if (cmp_str == 0)
			{
				found_match = 1;
				break;
			}
		}
		if (found_match == 1)
			break;
		closedir(directory);
	}
	if (found_match == 1)
	{
		result = make_pathname(path[i], input);
		if (access(result, R_OK) != -1)
			errno = EACCES;
		closedir(directory);
		return (result);
	}
	errno = EBADF;
	return (NULL);
}

/**
  * make_pathname - take result from pathname and create a string
  * which contains the fullname path
  * @path: file path
  * @file: file in path
  * Return: pointer to the alloc string which contains the full pathname
  */
char *make_pathname(char *path, char *file)
{
	size_t path_num, file_num;
	unsigned int i, j;
	char *result;

	path_num = _strlen(path);
	file_num = _strlen(file);
	result = malloc(sizeof(char) * (path_num + file_num + 2));
	if (result == NULL)
		return (NULL);
	for (i = 0; i < path_num; i++)
		result[i] = path[i];
	result[i++] = '/';
	for (j = 0; j < file_num; j++)
		result[i + j] = file[j];
	result[i + j] = '\0';
	return (result);
}

/**
  * _getenv - get environment variable
  * @name: variable name to find
  * Return: pointer to the value of environment variable
  */
char *_getenv(const char *name)
{
	unsigned int i, j;

	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; environ[i][j] != '=' && environ[i][j] == name[j] && name[j]; j++)
			;
		if (environ[i][j] == '=' && name[j] == '\0')
			return (&environ[i][++j]);
	}
	return (NULL);
}
