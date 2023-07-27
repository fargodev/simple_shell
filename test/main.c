#include "header.h"

extern char **environ;

/**
  * main - program entry point
  * @argc: argument count
  * @argv: argument vector
  * @argenv: argument environment
  * Return: success 0
  */
int main(int argc, char *argv[], char *argenv[])
{
	char **path_values, **input_token, *input, *path_modify;
	char delimiters[] = " \n\r\t";
	size_t input_num;
	ssize_t getline_stat;
	shell_t shell_ptrs;

	(void)argc;
	input = NULL;
	path_values = getpath(&path_modify);
	print_ps(0);
	shell_ptrs.path_modify = path_modify;
	shell_ptrs.path_values = path_values;
	signal(SIGINT, SIG_IGN);
	while ((getline_stat = getline(&input, &input_num, stdin)) != -1)
	{
		shell_ptrs.input = input;
		input_token = tokenize(input, delimiters);
		shell_ptrs.input_token = input_token;
		if (input_token[0] && slash_checker(input_token[0]) == 1)
			run_path(&shell_ptrs, argv[0]);
		else if (input_token[0] && slash_checker(input_token[0]) == 0)
		{
			if (run_built_ins(&shell_ptrs, argv[0]) == 1)
				run_cmd(&shell_ptrs, argv[0], argenv);
		}
		free(input_token);
		print_ps(1);
	}
	free(path_modify);
	free(path_values);
	free(input);
	return (errno);
}

/**
  * slash_checker - check if there's availability of slash in the input command
  * @str: input string
  * Return: 0 if slash is not found, and 1 if found
  */
int slash_checker(char *str)
{
	while (*str != '\0')
	{
		if (*str == '/')
			return (1);
		str++;
	}
	return (0);
}

/**
  * run_cmd - run input commands inputed by user
  * @shell_ptrs: struct containing all malloc'd spaces
  * @filename: name of file being run
  * @env: environment variable
  * Return: errno value
  */
int run_cmd(shell_t *shell_ptrs, char *filename, char **argenv)
{
	pid_t child_pid;
	int status;
	char *input_org;
	char **input_token = shell_ptrs->input_token;
	char **path = shell_ptrs->path_values;

	if (input_token[0] != NULL)
	{
		child_pid = fork();
		if (child_pid == 0)
		{
			input_org = _strdup(input_token[0]);
			input_token[0] = find_pathname(path, input_token[0]);
			if (input_token[0] != NULL)
			{
				if (execve(input_token[0], input_token, argenv) == -1)
					perror(filename);
				free(input_token[0]);
			}
			else
			{
				errno = 127;
				print_cmd(input_org, filename);
			}
			free_shell(shell_ptrs);
			free(input_org);
			_exit(errno);
		}
		else
			wait(&status);
	}
	errno = status % 255;
	return (errno);
}

/**
  * run_built_ins - check if user call built in commands
  * @ptrs: structure containing all malloc'd memory
  * @filename: name of file
  * Return: 0 if match found, and 1 if not found
  */
int run_built_ins(shell_t *ptrs, char *filename)
{
	size_t index;
	unsigned int words_num;
	char **words_input;
	built_t cmd[] = {
		{"exit", myexit},
		{"env", printenv},
		{NULL, NULL},
	};

	(void)filename;
	if (!ptrs)
		return (1);
	if (!(ptrs->input_token[0]))
		return (1);
	words_input = ptrs->input_token;
	words_num = 0;
	while (words_input[words_num] != NULL)
		words_num++;
	index = 0;
	while (cmd[index].cmd_name)
	{
		if (!_strcmp(ptrs->input_token[0], cmd[index].cmd_name))
		{
			(cmd[index].cmd)(ptrs);
			return (0);
		}
		index++;
	}
	return (1);
}

/**
  * run_path - run command specified by pathname
  * @shell_ptrs: structure containing all malloc'd memory
  * @filename: name of file
  * Return: undetermined
  */
int run_path(shell_t *shell_ptrs, char *filename)
{
	pid_t child_pid;
	int status;
	char **input_token = shell_ptrs->input_token;

	child_pid = fork();
	if (child_pid == 0)
	{
		if (execve(input_token[0], input_token, environ) == -1)
			perror(filename);
		free_shell(shell_ptrs);
		_exit(errno);
	}
	else
		wait(&status);
	errno = status % 255;
	return (errno);
}
