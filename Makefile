all:
	bison -d -o parser.cpp blokk.y
	flex -o tokens.cpp blokk.l
	c++ parser.cpp tokens.cpp -o blokk

clean:
	rm lex.yy.o

debug:
	lex blokk.l
	yacc -vdt blokk.y
	gcc -o blokk lex.yy.c y.tab.c
