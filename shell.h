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

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* for convert_number() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @str: string
 * @num: number field
 * @next: next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - has pseudo arguements for a function,
 * with uniform prototype for function pointer struct
 * @argv: array of strings from arg
 * @line_count - error count
 * @arg: string generated from getline with arguements
 * @path: string path for current command
 * @argc: argument count
 * @err_num: error code for exit()s
 * @linecount_flag: if on count line of input
 * @fname: program filename
 * @env: linked list local copy of environ
 * @environ: modified copy of environ from LL env
 * @histcount: history line number count
 * @readfd: fd to read line input
 * @cmd_buf_type: CMD_type ||, &&, ;
 * cmd_buf: address of pointer to cmd_buf, on if chaining
 * @status: return status of last exec'd command
 * @env_changed: on if environ was changed
 * @alias: alias node
 * @history: history node
 */
typedef struct passinfo
{
	char **argv;
	char *arg;
	char path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory management */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}


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
