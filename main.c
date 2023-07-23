#include "shell.h"

/**
  * main - program entry point
  * @argc: argument count
  * @argv: argument vector
  * Return: success
  */
int main(int argc, char **argv)
{
	char *command;

	do {
		command = read_cmd();
		if (!command)
			exit(EXIT_SUCCESS);
		if (command[0] == '\0' || strcmp(command, "\n") == 0)
		{
			free(command);
			continue;
		}
		if (strcmp(command, "exit\n") == 0)
		{
			free(command);
			break;
		}
		printf("%s\n", command);
		free(command);
	} while (1);
	exit(EXIT_SUCCESS);
}

/**
  * read_cmd - read inputed commands
  * Return: result success 0
  */
char *read_cmd(void)
{
	char buffer[1024], *ptr = NULL, *ptr2, ptrlen = 0;
	int bufferlen;

	while (fgets(buffer, 1024, stdin))
	{
		bufferlen = strlen(buffer);
		if (!ptr)
			ptr = malloc(sizeof(bufferlen + 1));
		else
		{
			ptr2 = realloc(ptr, ptrlen + bufferlen + 1);
			if (ptr2)
				ptr = ptr2;
			else
			{
				free(ptr);
				ptr = NULL;
			}
		}
		if (!ptr)
		{
			fprintf(stderr, "error: failed to allocate buffer: %s\n", strerror(errno));
			return (NULL);
		}
		strcpy(ptrlen + ptr, buffer);
		if (buffer[bufferlen - 1] == '\n')
		{
			if (bufferlen == 1 || buffer[bufferlen - 2] != '\\')
				return (ptr);
			ptr[ptrlen + bufferlen - 2] = '\0';
			bufferlen -= 2;
			print_promt2();
		}
		ptrlen += bufferlen;
	}
	return (ptr);
}
