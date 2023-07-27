#define _SHELL_H_
#ifndef _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sysy/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/**
 * struct passinfo - has pseudo-arguements to pass into function,
 * allowing uniform prototype for function pointer struct
 * @arg: string generated from getline containing arguements
 * @argv: an array of strings generated from arg
 * @argc: argument count
 * @path: string path for current command
 * @line_count: error count
 * @err_num: error code for exit()s
 * @linecount_flag: if on count this lineof input
 * @fname: program file name
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: history node
 * @histcount: history line number count
 * @alias: alias node
 * @readfd: fd from which to read line input
 * @env_changed: on if environ changed
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @status: return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
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
	int cmd_buf_type; /* CMD_type ||, &&, */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
  * struct shell_env - store shell environment addresses
  * @path_values: pointer to values of the shell path
  * @input: input token
  * @input_token: pointer for the cmd tokens
  * @path_modify: path pointer after modification
  *
  * Description: provide storage for all malloc'd elements
  */
typedef struct shell_env
{
	char **path_values;
	char *input;
	char **input_token;
	char *path_modify;
} shell_t;

/**
  * struct built_in_cmd - handles shell built in cmds
  * @cmd_name: name of built in commands
  * @cmd: function pointer to run the built in cmds
  *
  * Description: struct for handling our shell built in cmds
  */
typedef struct built_in_cmd
{
	char *cmd_name;
	void (*cmd)(shell_t *);
} built_t;

/**
 * struct builtin - has builtin string and related function
 * @func: function
 * @type: builtin command flag
 */
typedef struct builtin
{
        char *type;
        int (*func)(info_t *);
} builtin_table;


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

/** builtin.c **/
void made_exit(shell_t *);
void print_env(shell_t *);
int _myexit(shell_t *);
int _mycd(info_t);
int _myhelp(info_t);

/** env_shell.c **/
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/** function prototypes **/
char *_strtok(char *, const char *);
ssize_t get_line(char **, size_t *, FILE *);
void print_list_str(const char **list);
int starts_with(const char *str, const char *prefix);
void print_env(char **env);

#endif
