all: bison flex compile

bison:
	bison -d -rsolved -o parser.cpp blokk.y

flex:
	flex -o tokens.cpp blokk.l

compile:
	c++ parser.cpp tokens.cpp -o blokk

clean:
	@echo -e "removing unused files..."
	@rm -v tokens.cpp parser.* 2>/dev/null || exit 0
