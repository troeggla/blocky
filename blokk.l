%{
#include <string>
#include "parser.hpp"

#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t) (yylval.token = t)

extern "C" int yywrap() {}
%}

%%

[ \t\n]         ;
\$[a-zA-Z]+     SAVE_TOKEN; return T_VAR;
[0-9]+\.[0-9]+  SAVE_TOKEN; return T_FLOAT;
[0-9]+          SAVE_TOKEN; return T_INT;
".*"|'.*'       SAVE_TOKEN; return T_STRING;
true|false      SAVE_TOKEN; return T_BOOL;

nil             return TOKEN(T_NIL);

%%
