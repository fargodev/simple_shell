#include "shell.h"

/**
  * unget_char - unget last character from input
  * @src: input source
  * Return: last char back to source
  */
void unget_char(src_s *src)
{
	if (src->curpos < 0)
		return;
	src->curpos--;
}

/**
  * next_char - get next char from input
  * @src: input source
  * Return: next char
  */
char next_char(src_s *src)
{
	if (!src || !src->buffer)
	{
		errno = ENODATA;
		return (-ERRCHAR);
	}
	char c1 = 0;

	if (src->curpos == INIT_SRC_POS)
		src->curpos = -1;
	else
		c1 = src->buffer[src->curpos];
	if (++src->curpos >= src->bufsize)
	{
		src->curpos = src->bufsize;
		return (EOF);
	}
	return (src->buffer[src->curpos]);
}

/**
  * peek_char - lookout for the next input inline
  * @src: input source
  * Return: success 0
  */
char peek_char(src_s *src)
{
	if (!src || !src->buffer)
	{
		errno = ENODATA;
		return (-ERRCHAR);
	}
	long pos = src->curpos;

	if (pos == INIT_SRC_POS)
		pos++;
	pos++;
	if (pos >= src->bufsize)
		return (EOF);
	return (src->buffer[pos]);
}

/**
  * skip_white_spaces - skip all whitespace such as tab
  * @src: input source
  * Return: success 0
  */
void skip_white_spaces(src_s *src)
{
	char c;

	if (!src || !src->buffer)
		return;
	while (((c = peek_char(src)) != EOF) && (c == ' ' || c == '\t'))
		next_char(src);
}

