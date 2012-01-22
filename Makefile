all: bison flex compile

bison: grammar/blocky.y
	bison -d -o grammar/parser.cpp $^

flex: grammar/blocky.l grammar/parser.hpp
	flex -o grammar/tokens.cpp grammar/blocky.l

compile: grammar/parser.cpp grammar/tokens.cpp grammar/src/*.cpp -lSDL -lSDL_gfx
	c++ $^ -o blocky

clean:
	@echo -e "removing unused files..."
	@rm -v grammar/tokens.cpp grammar/parser.* 2>/dev/null || exit 0
