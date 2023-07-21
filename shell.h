#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>

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
  * struct built_in_cmd - structure for different built-in commands
  * @cmd_name: name of commands
  * @cmd: function pointer to run the command
  *
  * Description: structure for different built in command in our shell
  */
typedef struct built_in_cmd
{
	char *cmd_name;
	void (*cmd)(shell_t *);
} built_t;

/** main.c **/
int run_built_in(shell_t *, char *);
int run_cmd(shell_t *, char *, char **);
int run_path(shell_t *, char *);
int check_slash(char *);

/** exit_shell.c **/
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/** env_shell.c **/
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int _populate_env_list(info_t *);


#endif /** SHELL **/
