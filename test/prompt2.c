#include "header.h"

/**
  * free_shell - free all elements in struct shell_t
  * @shell_ptr: malloc'd elements structure
  */
void free_shell(shell_t *shell_ptr)
{
	free(shell_ptr->path_values);
	free(shell_ptr->input);
	free(shell_ptr->input_token);
	free(shell_ptr->path_modify);
}

/**
  * print_cmd - print error for failed commands
  * @cmd: user input command
  * @filename: name of file being runned
  */
void print_cmd(char *cmd, char *filename)
{
	char *error_message;
	char *error = ": command not found\n";
	size_t char_num, i = 0;

	(void)filename;
	char_num = _strlen(error) + _strlen(cmd);
	error_message = malloc(sizeof(char) + (char_num++));
	while (*cmd != '\0')
		error_message[i++] = *cmd++;
	while (*error != '\0')
		error_message[i++] = *error++;
	error_message[i] = '\0';
	write(STDERR_FILENO, error_message, char_num);
	free(error_message);
}
