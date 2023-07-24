#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/** source.h **/
#define ERRCHAR		0
#define INIT_SRC_POS	-2

/**
  * struct source - program input strings
  * @buffer: Input text
  * @bufsize: size of input text
  * @curpos: char current position
  * Return: input string
**/
typedef struct source
{
	char *buffer;	/** input text **/
	long bufsize;	/** size of input text **/
	long curpos;	/** absolute char current position in src **/
} src_s;

/** source.c **/
void unget_char(src_s *src);
char next_char(src_s *src);
char peek_char(src_s *src);
void skip_white_space(src_s *src);

/** scanner.h **/
/**
  * struct token - struct to extract input token
  * @src: input source
  * @text_len: token text length
  * @text: token text
  */
typedef struct token
{
	src_s *src;	/** input source **/
	int text_len;	/** token text length **/
	char *text;	/** token text **/
} token_t;

/** Special EOF token indicating end of input **/
extern token_t eof_token;

token_t *tokenize(src_s *src);
void free_token(tokent_t *tok);

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
