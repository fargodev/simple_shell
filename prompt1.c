#include "header.h"

/**
  * print_ps - print shell prompt waiting for command
  * @num: determines which errno to set
  * Return: prompt
  */
void print_ps(int num)
{
	char ps0[] = "MABERT$ ";
	size_t ps_len;
	int error;

	error = errno;
	ps_len = _strlen(ps0);
	if (isatty(0))
		write(STDOUT_FILENO, ps0, ps_len);
	if (num == 0)
		errno = 0;
	else
		errno = error;
}

/**
  * make_pathname - take result from path files name and create a string
  * which contains the full pathname
  * @path: the path to consider
  * @file: file in the path
  * Return: Pointer to the allocated string that contains the path
  */
char *make_pathname(char *path, char *file)
{
	size_t path_num, file_num;
	unsigned int i, j;
	char *result;

	path_num = _strlen(path);
	file_num = _strlen(file);
	result = malloc(sizeof(char) * (2 + path_num + file_num));
	if (result == NULL)
		return (NULL);
	for (i = 0; i < path_num; i++)
		result[j] = path[j];
	result[j++] = '/';
	for (j = 0; j < file_num; j++)
		result[i + j] = file[j];
	result[i + j] = '\0';
	return (result);
}

/**
  * find_pathname - find path name attached to the command
  * @path: pointer to 2d array of tokenized dir in path
  * @input: command input to find
  * Return: path to the input file
  */
char *find_pathname(char **path, char *input)
{
	unsigned int i;
	int str_cmp, found_match;
	char *result;
	DIR *directory;
	struct dirent *filename;

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
			str_cmp = _strcmp(filename->d_name, input);
			if (str_cmp == 0)
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
  * getenv - get value of the environment variable
  * @name: variable name to locate
  * Return: pointer to value of environment variable
  */
char *getenv(const char *name)
{
	unsigned int i, j;

	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; environ[i][j] != '=' && environ[i][j] == name[j] && name[j]; j++)
			;
		if (environ[i][j] == '=' && name[j] == '\0')
			return (&environ[i][j++]);
	}
	return (NULL);
}

/**
  * getpath - get the environ path and tokenize it into an array
  * @modify_path: pointer to store modified path string
  * Return: array of string
  */
char **getpath(char **modify_path)
{
	char **token_ptr;
	char *path, *delim;
	unsigned int i, j, char_num;

	delim = ":";
	path = getenv("PATH");
	char_num = _strlen(path);
	*modify_path = malloc(sizeof(char) * (char_num + 2));
	if (char_num == 0)
	{
		(*modify_path)[0] = '.';
		(*modify_path)[1] = '\0';
	}
	else
	{
		for (i = 0, j = 0; path[i] != '\0'; i++)
		{
			if (i == 0 && path[i] == '.')
			{
				(*modify_path)[j++] = '.';
				(*modify_path)[j++] = path[i];
			}
			else if (i == char_num - 1 && path[i] == ':')
			{
				(*modify_path)[j++] = path[i];
				(*modify_path)[j++] = '.';
			}
			else if (path[i] == ':' && path[i + 1] == ':')
			{
				(*modify_path)[j++] = path[i];
				(*modify_path)[j++] = '.';
			}
			else
				(*modify_path)[j++] = path[i];
		}
		for (; j < char_num + 2; j++)
			(*modify_path)[j] = '\0';
	}
	token_ptr = tokenize(*modify_path, delim);
	return (token_ptr);
}
