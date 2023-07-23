#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/** prompts.c **/
void print_prompt(void);
void print_promt2(void);
char *read_cmd(void);

/** string.c **/
size_t _strlen(char *str);
char *_strdup(char *s);
int _strcmp(char *str1, char *str2);
char **tokenize_str(char *str, char *delim);

#endif
