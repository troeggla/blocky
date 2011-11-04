all:
	lex blokk.l
	yacc -d blokk.y -o y.tab.cc
	gcc -c lex.yy.c -o lex.yy.o
	c++ lex.yy.o y.tab.cc -o blokk

clean:
	rm lex.yy.o

debug:
	lex blokk.l
	yacc -vdt blokk.y
	gcc -o blokk lex.yy.c y.tab.c
