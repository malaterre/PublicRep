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
