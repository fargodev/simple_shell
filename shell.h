#ifndef SHELL
#define SHELL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/type.h>
#include <sys/wait.h>

/**
  * struct shell_env - stores address for pointer to free
  * @path_values: pointer to the path values of cmd
  * @input: pointer to buffer that get lines create upon run
  * @input_token: pointer for input tokens
  * @modify_path: pointer to the path after it has been modified
  *
  * Description: provide a storage for all elements that are
  * allocated in the memory
  */
typedef struct shell_env
{
	char **path_values;
	char *input;
	char **input_token;
	char *modify_path;
} shell_t;

/**
  * struct built-in-cmd - structure for different built-in commands
  * @cmd_name: name of commands
  * @cmd: function pointer to run the command
  *
  * Description: structure for different built in command in our shell
  */
typedef struct built-in-cmd
{
	char *cmd_name;
	void (*cmd)(shell_t *);
} built_t;


#endif /** SHELL **/
