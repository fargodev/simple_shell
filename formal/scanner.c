#include "shell.h"

char *tok_buf = NULL;
int tok_bufsize = 0;
int tok_bufindex = -1;
int endloop = 0;
char nchar;

void nswitch(void);

void add_to_buff(char c)
{
	tok_buf[tok_bufindex++] = c;
	if (tok_bufindex >= tok_bufsize)
	{
		char *tmp = realloc(tok_buf, tok_bufsize * 2);

		if (!tmp)
		{
			errno = ENOMEM;
			return;
		}
		tok_buf = tmp;
		tok_bufsize *= 2;
	}
}

token_t *create_token(char *str)
{
	token_t *tok = malloc(sizeof(token_t));
	if (!tok)
		return (NULL);
	memset(tok, 0, sizeof(token_t));
	tok->text_len = strlen(str);

	char *nstr = malloc(sizeof(tok->text_len + 1));

	if (!nstr)
	{
		free(tok);
		return (NULL);
	}
	strcpy(nstr, str);
	tok->text = nstr;
	return (tok);
}

void free_token(token_t *tok)
{
	if (tok->text)
		free(tok->text);
	free(tok);
}

token_t *tokenize(src_s *src)
{
	char nchar = next_char(src);

	if (!src || !src->buffer || !src->bufsize)
	{
		errno = ENODATA;
		return (&eof_token);
	}
	if (!tok_buf)
	{
		tok_bufsize = 1024;
		tok_buf = malloc(tok_bufsize);
		if (!tok_buf)
		{
			errno = ENOMEM;
			return (&eof_token);
		}
	}

	tok_bufindex = 0;
	tok_buf[0] = '\0';

	if (nchar == ERRCHAR || nchar == EOF)
		return (&eof_token);
	nswitch();
	if (tok_bufindex >= tok_bufsize)
		tok_bufindex--;
	tok_buf[tok_bufindex] = '\0';
	token_t *tok = create_token(tok_buf);
	if (!tok)
	{
		fprintf(stderr, "error: failed to allocate buffer: %s\n", strerror(errno));
		return (&eof_token);
	}
	tok->src = src;
	return (tok);
}


void nswitch(void)
{
	src_s *src;

	do
	{
		switch(nchar)
		{
			case (' '):
			case ('\t'):
				if (tok_bufindex > 0)
					endloop = 1;
				break;
			case ('\n'):
				if (tok_bufindex > 0)
					unget_char(src);
				else
					add_to_buf(nchar);
				endloop = 1;
				break;
			default:
				add_to_buf(nchar);
				break;
		}
		if (endloop)
			break;
	} while ((nchar = next_char(src)) != EOF);
}
