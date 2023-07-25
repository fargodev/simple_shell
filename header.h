#ifndef HEADER_H
#define HEADER_H

/** System header libraries **/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>

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

/** string.c **/
size_t _strlen(char *);
int _strcmp(char *, char *);
char *_strdup(char *);
char **tokenize(char *, char *);

/** prompt1.c **/
void print_ps(int);
char *make_pathname(char *, char *);
char *find_pathname(char **, char *);
char *getenv(const char *);
char **getpath(char **);

/** prompt2.c **/
void free_shell(shell_t *);
void print_cmd(char *, char *);

/** builtin.c **/
int _myexit(info_t);
int _mycd(info_t);
int _myhelp(info_t);
void made_exit(shell_t *);
void print_env(shell_t *);

/** main.c **/
int run_built_ins(shell_t *, char *);
int run_cmd(shell_t *, char *, char **);
int run_path(shell_t *, char *);
int slash_checker(char *);

/** function prototypes **/
char *_strtok(char *, const char *);
ssize_t get_line(char **, size_t *, FILE *);

#endif /** HEADER_H **/
