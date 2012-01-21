all: bison flex compile

bison: blokk.y
	bison -d -o parser.cpp $^

flex: blokk.l parser.hpp
	flex -o tokens.cpp blokk.l

compile: parser.cpp tokens.cpp src/numExpression.cpp src/boolExpression.cpp src/blockScope.cpp src/putStatement.cpp src/assignStatement.cpp src/blockStatement.cpp
	c++ $^ -o blokk

clean:
	@echo -e "removing unused files..."
	@rm -v tokens.cpp parser.* 2>/dev/null || exit 0
