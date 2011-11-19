all: bison flex compile

bison:
	@echo -e "Building parser...\n"
	bison -d -o parser.cpp blokk.y

flex:
	@echo -e "Building lexer...\n"
	flex -o tokens.cpp blokk.l

compile:
	@echo -e "Compiling...\n"
	c++ parser.cpp tokens.cpp -o blokk

clean:
	@echo -e "Cleanup...\n"
	@rm -v tokens.cpp parser.* 2>/dev/null || exit 0
