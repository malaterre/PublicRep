/* lisp.y  (requires Bison) */

/* a "pure" api means communication variables like yylval
   won't be global variables, and yylex is assumed to
   have a different signature */

%define api.pure true

/* change prefix of symbols from yy to "lisp" to avoid
   clashes with any other parsers we may want to link */

%define api.prefix {lisp}

/* generate much more meaningful errors rather than the
   uninformative string "syntax error" */

%define parse.error verbose

/* Bison offers different %code insertion locations in
   addition to yacc's %{ %} construct.

   The "top" location is good for headers and feature
   flags like the _XOPEN_SOURCE we use here */

%code top {
	/* XOPEN for strdup */
	#define _XOPEN_SOURCE 600
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>

	/* Bison versions 3.7.5 and above provide the YYNOMEM
	   macro to allow our actions to signal the unlikely
	   event that they couldn't allocate memory. Thanks
	   to the Bison team for adding this feature at my
	   request. :) YYNOMEM causes yyparse() to return 2.

	   The following conditional define allows us to use
	   the functionality in earlier versions too. */

	#ifndef YYNOMEM
	#define YYNOMEM goto yyexhaustedlab
	#endif
}

/* The "requires" code location is designed for defining
   data types that we can use as yylval's for tokens. Code
   in this section is also added to the .tab.h file for
   inclusion by calling code */

%code requires {
	enum sexpr_type {
		SEXPR_ID, SEXPR_NUM, SEXPR_PAIR, SEXPR_NIL
	};

	struct sexpr
	{
		enum sexpr_type type;
		union
		{
			int   num;
			char *id;
		} value;
		struct sexpr *left, *right;
	};
}

/* These are the semantic types available for tokens,
   which we name num, str, and node.

   The %union construction is classic yacc as well. It
   generates a C union and sets its as the YYSTYPE, which
   will be the type of yylval */

%union
{
	int num;
	char *str;
	struct sexpr *node;
}

/* Add another argument in yyparse() so that we
   can communicate the parsed result to the caller.
   We can't return the result directly, since the
   return value is already reserved as an int, with
   0=success, 1=error, 2=nomem

   NOTE
   In our case, the param is a data pointer. However,
   if it were a function pointer (such as a callback),
   then its type would have to be put behind a typedef,
   or else parse-param will mangle the declaration. */

%parse-param {struct sexpr **result}

/* param adds an extra param to yyparse (like parse-param)
   but also causes yyparse to send the value to yylex.
   In our case the caller will initialize their own scanner
   instance and pass it through */

%param {void *scanner}

/* the "provides" location adds the code to our generated
   parser, but also to the .tab.h file for use by callers */

%code provides {
	void sexpr_free(struct sexpr *s);
}

/* unqualified %code is for internal use, things that
   our actions can see. These declarations prevent
   warnings.  Notice the final param in each that came
   from the %param directive above */

%code {
	int lisperror(void *foo, char const *msg, const void *s);
	int lisplex(void *lval, const void *s);
}

/* Now when we declare tokens, we add their type
   in brackets. The type names come from our %union */

%token <str> ID
%token <num> NUM

/* whereas tokens come from the lexer, these
   non-terminals are defined in the parser, and
   we set their types with %type */

%type <node> start sexpr pair list members atom

/* if there's an error partway through parsing, the
   caller wouldn't get a chance to free memory for
   the work in progress. Bison will clean up the memory
   if we provide destructors, though. */

%destructor { free($$); } <str>
%destructor { sexpr_free($$); } <node>

%%

 /* once again we use a dummy non-terminal to perform
    a side-effect, in this case setting *result */

start :
  sexpr   { *result = $$ = $1; return 0; }
;

sexpr :
  atom
| list
| pair
;

list :

  /* This is a shortcut: we use the ascii value for
     parens '('=40, ')'=41 as their token codes.
     Thus we don't have to define a bunch of crap
     manually like LPAREN, RPAREN */

  '(' members ')' { $$ = $2; }

| '('')' {
	struct sexpr *nil = malloc(sizeof *nil);
	if (!nil) YYNOMEM;
	*nil = (struct sexpr){.type = SEXPR_NIL};
	$$ = nil;
  }
;

members :
  sexpr {
	struct sexpr *s = malloc(sizeof *s),
				 *nil = malloc(sizeof *nil);
	if (!s || !nil) {
		free(s), free(nil);
		YYNOMEM;
	}
	*nil = (struct sexpr){.type = SEXPR_NIL};

	/* convention: we assume that a previous parser
	   value like $1 is non-NULL, else it would have
	   died already with YYNOMEM. We're responsible
	   for checking only our own allocations */

	*s = (struct sexpr){
		.type = SEXPR_PAIR,
		.left = $1,
		.right = nil
	};
	$$ = s;
  }
| sexpr members {
	struct sexpr *s = malloc(sizeof *s);

	/* Another important memory convention: we
	   can't trust that our lexer successfully
	   allocated its yylvalue, because the signature
	   of yylex doesn't communicate failure. We
	   assume NULL in $1 means alloc failure and
	   we report that. The only other way to signal
	   from yylex would be to make a fake token to
	   represent out-of-memory, but that's harder */

	if (!s) YYNOMEM;
	*s = (struct sexpr){
		.type = SEXPR_PAIR,
		.left = $1,
		.right = $2
	};
	$$ = s;
  }
;

pair :
  '(' sexpr '.' sexpr ')' {
	struct sexpr *s = malloc(sizeof *s);
	if (!s) YYNOMEM;
	*s = (struct sexpr){
		.type = SEXPR_PAIR,
		.left = $2,
		.right = $4
	};
	$$ = s;
  }
;

atom :
  ID {
	if (!$1) YYNOMEM;

	struct sexpr *s = malloc(sizeof *s);
	if (!s) YYNOMEM;
	*s = (struct sexpr){
		.type = SEXPR_ID,
		.value.id = strdup($1)
	};
	if (!s->value.id)
	{
		free(s);
		YYNOMEM;
	}
	$$ = s;
  }
| NUM {
	struct sexpr *s = malloc(sizeof *s);
	if (!s) YYNOMEM;
	*s = (struct sexpr){
		.type = SEXPR_NUM,
		.value.num = $1
	};
	$$ = s;
  }
;

%%

/* notice the extra parameters required
   by %param and %parse-param */

int lisperror(void *yylval, char const *msg, const void *s)
{
	(void)yylval;
	(void)s;
	return fprintf(stderr, "%s\n", msg);
}

/* useful internally by us, and externally by callers */

void sexpr_free(struct sexpr *s)
{
	if (!s)
		return;
	
	if (s->type == SEXPR_ID)
		free(s->value.id);
	else if (s->type == SEXPR_PAIR)
	{
		sexpr_free(s->left);
		sexpr_free(s->right);
	}
	free(s);
}
