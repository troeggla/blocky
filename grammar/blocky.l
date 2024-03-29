%{
#include <string>
#include <stdlib.h>

#include "src/statement.hpp"
#include "src/numExpression.hpp"
#include "src/boolExpression.hpp"
#include "parser.hpp"

#define TOKEN(t) (yylval.token = t)

extern BlockScope* global;
extern BlockScope* current;
extern BlockScope* ifBlock;

extern "C" int yywrap() {}
%}

%%

[ \t]*                ;
#[^\n]*               ;

\$[a-z][a-zA-Z0-9_]*  yylval.string = new std::string(yytext, yyleng); return T_VAR;
[0-9]+\.[0-9]+        yylval.expr = new NumExpression(atof(yytext)); return T_FLOAT;
[0-9]+                yylval.expr = new NumExpression(atof(yytext)); return T_INT;
\"[^"]*\"|'[^']*'     yylval.string = new std::string(yytext, yyleng); return T_STRING;
true                  yylval.boolean = new BoolExpression(true); return T_BOOL;
false                 yylval.boolean = new BoolExpression(false); return T_BOOL;

"nil"               return TOKEN(T_NIL);
"and"               return TOKEN(T_AND);
"or"                return TOKEN(T_OR);
"=="                return TOKEN(T_EQUAL);
">="                return TOKEN(T_GE);
"<="                return TOKEN(T_LE);
"!="                return TOKEN(T_NE);

"if"                return TOKEN(T_IF);
"unless"            return TOKEN(T_UNLESS);
"else"              ifBlock = current; current = new BlockScope(ifBlock->get_parent()); return TOKEN(T_ELSE);
"while"             return TOKEN(T_WHILE);
"times"             return TOKEN(T_TIMES);
"global"            return TOKEN(T_GLOBAL);
"puts"              return TOKEN(T_PUTS);
"put"               return TOKEN(T_PUT);
"do"                current = new BlockScope(current); return TOKEN(T_DO);
"end"               return TOKEN(T_END);

"scope.dump"        return TOKEN(SCOPE_DUMP);
"scope.dumpall"     return TOKEN(SCOPE_DUMPALL);

"pen.goto"          return TOKEN(PEN_GOTO);
"pen.turn"          return TOKEN(PEN_TURN);
"pen.line"          return TOKEN(PEN_DRAW);
"pen.lineTo"        return TOKEN(PEN_LINETO);
"pen.delay"         return TOKEN(PEN_DELAY);
"pen.color"         return TOKEN(PEN_COLOR);
"pen.direction"     return TOKEN(PEN_DIRECTION);
"pen.move"          return TOKEN(PEN_MOVE);

\n                  yylineno++; return TOKEN(T_SEP);
;                   return TOKEN(T_SEP);
.                   return TOKEN(yytext[0]);

%%
