%{
#include <string>
#include "parser.hpp"

extern "C" int yywrap() {}
%}

%%

^#.*\n     ;
[ \t]+\n   ;
.          return yytext[0];

%%
