/* lisp.l */

/* disable unused functions so we don't
   get compiler warnings about them */

%option noyywrap nounput noinput
%option noyyalloc noyyrealloc noyyfree

/* change our prefix from yy to lisp */

%option prefix="lisp"

/* use the pure parser calling convention */

%option reentrant bison-bridge

%{
#include "lisp.tab.h"

#define YY_EXIT_FAILURE ((void)yyscanner, EXIT_FAILURE)

/* XOPEN for strdup */
#define _XOPEN_SOURCE 600
#include <limits.h>
#include <stdlib.h>
#include <string.h>

/* seems like a bug that I have to do this, since flex
   should know prefix=lisp and match bison's LISPSTYPE */
#define YYSTYPE LISPSTYPE

int lisperror(const char *msg);
%}

%%

[[:alpha:]][[:alnum:]]* {
	/* The memory that yytext points to gets overwritten
	   each time a pattern matches. We need to give the caller
	   a copy. Also, if strdup fails and returns NULL, it's up
	   to the caller (the parser) to detect that.

	   Notice yylval is a pointer to union now.  It's passed
	   as an arg to yylex in pure parsing mode */

	yylval->str = strdup(yytext);
	return ID;
}

[-+]?[[:digit:]]+ {
	long n = strtol(yytext, NULL, 10);

	if (n < INT_MIN || n > INT_MAX)
		lisperror("Number out of range");
	yylval->num = (int)n;
	return NUM;
}

[[:space:]]  ; /* ignore */

/* this is a handy rule to return the ASCII value
   of any other character. Importantly, parens */

. { return *yytext; }
Finally, here’s how to call the parser from a regular program.

/* driver_lisp.c */

#include <stdio.h>
#include <stdlib.h>

#define YYSTYPE LISPSTYPE
#include "lisp.tab.h"
#include "lisp.lex.h"

void sexpr_print(struct sexpr* s, unsigned depth)
{
	for (unsigned i = 0; i < depth; i++)
		printf("  ");
	switch (s->type)
	{
		case SEXPR_ID:
			puts(s->value.id);
			break;
		case SEXPR_NUM:
			printf("%d\n", s->value.num);
			break;
		case SEXPR_PAIR:
			puts(".");
			sexpr_print(s->left, depth+1);
			sexpr_print(s->right, depth+1);
			break;
		case SEXPR_NIL:
			puts("()");
			break;
		default:
			abort();
	}
}

int main(void)
{
	int i;
	struct sexpr *expr;
	yyscan_t scanner;

	if ((i = lisplex_init(&scanner)) != 0)
		exit(i);

	int e = lispparse(&expr, scanner);
	printf("Code = %d\n", e);
	if (e == 0 /* success */)
	{
		sexpr_print(expr, 0);
		sexpr_free(expr);
	}

	lisplex_destroy(scanner);
	return 0;
}
