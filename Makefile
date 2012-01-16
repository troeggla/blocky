all: bison flex compile

bison: blokk.y
	bison -d -rsolved -t -o parser.cpp $^

flex: blokk.l parser.hpp
	flex -o tokens.cpp blokk.l

compile: parser.cpp tokens.cpp src/expression.cpp
	c++ $^ -o blokk

clean:
	@echo -e "removing unused files..."
	@rm -v tokens.cpp parser.* 2>/dev/null || exit 0
