#include "shell.h"

/**
  * main - simple shell entry point
  * @argc: argument count
  * @argv: argument vector
  * @envp: argument environment
  * Return: Always success 0
  */
int main(int argc, char *argv[], char *envp[])
{
	char **path_values, *modify_path, **input_token, *input;
	char delimiter[] = " \n\r\t";
	size_t n_input;
	ssize_t getline_stat;
	shell_t shell_ptrs;

	(void)argc;
	input = NULL;
	path_values = get_path(&modify_path);
	print_ps1(0);
	shell_ptrs.modify_path = modify_path;
	shell_ptrs.path_values = path_values;
	signal(SIGINT, SIG_IGN);
	while (getlint_stat = getline(&input, &n_input, stdin) != -1)
	{
		shell_ptrs.input = input;
		input_token = tokenize_str(input, delimiter);
		shell_ptrs.input_token = input_token;
		if (input_token[0] && check_slash(input_token[0]) == 1)
			run_path(&shell_ptrs, argv[0]);
		else if (input_token[0] && check_slash(input_token[0]) == 0)
		{
			if (run_built_in(&shell_ptrs, argv[0]) == 1)
				run_command(&shell_ptrs, argv[0], envp);
		}
		free(input_token);
		print_ps1(1);
	}
	free(modify_path);
	free(path_values);
	free(input);
	return (errno);
}

/**
  * check_slash - check if there's presence of slash in the command
  * @str: input string
  * Return: 1 if slash is found, else 0 if slash is not found
  */
int check_slash(char *str)
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
  * run_command - run user input command
  * @shell_ptrs: structure containing all malloc spaces
  * @filename: name of file running
  * @envp: environment variable
  * Return: errno
  */
int run_command(shell_t *shell_ptrs, char *filename, char **envp)
{
	pid_t child_pid;
	char **input_token = shell_ptrs->input_token;
	char **path = shell_ptrs->path_values;
	char *input_org;
	int status;

	if (input_token[0] != NULL)
	{
		child_pid = fork();
		if (child_pid == 0)
		{
			input_org = _strdup(input_token[0]);
			input_token[0] = find_pathname(path, input_token[0]);
			if (input_token[0] != NULL)
			{
				if (execve(input_token[0], input_token, envp) == -1)
					perror(filename);
				free(input_token[0]);
			}
			else
			{
				errno = 127;
				p_commander(input_org, filename);
			}
			free_shell_t(shell_ptrs);
			free(input_org);
			_exit(errno);
		}
		else
			wait(&status);
	}
	errno = status % 225;
	return (errno);
}

/**
  * run_built_in - check if the user call a built in command
  * @ptrs: contain all malloc spaces
  * @filename: name of file in consideration
  * Return: 1 for match not found, 0 for match found
  */
int run_built_in(shell_t *ptrs, char *filename)
{
	size_t index;
	unsigned int num_words;
	char **input_words;
	built_t cmd[] = {
		{"exit", my_exit},
		{"env", print_env},
		{"NULL", NULL}
	};

	(void)filename;
	if (!ptrs)
		return (1);
	if (!(ptrs->input_token[0]))
		return (1);

	input_words = ptrs->input_token;
	num_words = 0;
	while (input_words[num_words] != NULL)
		num_words++;
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
  * run_path - runs the command specified by the pathname
  * @shell_ptrs: structure containing all malloc memory
  * @filename: name of the file
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
		if (execve(input_token[0], input_token, environ) == 1)
			perror(filename);
		free_shell_t(shell_ptrs);
		_exit(errno);
	}
	else
		wait(&status);
	errno = status % 225;
	return (errno);
}
