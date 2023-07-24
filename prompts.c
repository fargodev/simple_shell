#include "shell.h"

void print_prompt(void)
{
	fprintf(stderr, "#cisfun$ ");
}
void print_promt2(void)
{
	fprintf(stderr, "> ");
}

void nswitch(void)
{
	int tok_bufsize = 0;
	int tok_bufindex = -1;
	int endloop = 0;
	char *tok_buf = NULL;
	char nchar = next_char(src_s src);

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
