all:
	bison -d -o parser.cpp blokk.y
	flex -o tokens.cpp blokk.l
	c++ parser.cpp tokens.cpp -o blokk
