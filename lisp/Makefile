LEX=flex
YACC=bison

# put together object files from lexer and parser, and
# link the yacc and lex libraries (in that order, to pick
# main() from yacc's library rather than lex's)

lisp : lisp.tab.o lisp.lex.o driver_lisp.o
	$(CC) -o $@ driver_lisp.o lisp.tab.o lisp.lex.o -ly -ll

# tell make which files yacc will generate
#
# an explanation of the arguments:
# -b lisp  -  name the files lisp.tab.*
# -d        -  generate a .tab.h file too

lisp.tab.h lisp.tab.c : lisp.y
	$(YACC) -d -b lisp $?

# the object file relies on the generated lexer, and
# on the token constants 

lisp.lex.o : lisp.tab.h lisp.lex.c

driver_lisp.o : driver_lisp.c
	$(CC) -o driver_lisp.o $?

# can't use the default suffix rule because we're
# changing the name of the output to .lex.c

lisp.lex.c : lisp.l
	$(LEX) -t $? > $@
