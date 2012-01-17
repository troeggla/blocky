%{
#include <stdio.h>

#include <iostream>
#include <string>
#include <map>

#include "src/numExpression.hpp"
#include "src/boolExpression.hpp"
#include "parser.hpp"

#define YYDEBUG 1

extern FILE* yyin;
extern int yylineno;

extern int yylex();

void yyerror(const char *s) {
    std::cerr << "ERROR: " << s << " in line " << yylineno-1 << std::endl;
}
%}

%union {
    std::string *string;
    int token;
    NumExpression *expr;
    BoolExpression *boolean;
}

%token <expr> T_VAR T_FLOAT T_INT;
%token <boolean> T_BOOL;
%token <string> T_STRING;

%token <token> T_EQUAL T_AND T_OR T_GE T_LE T_NE
%token <token> T_NIL T_SEP T_RETURN T_DO T_END T_PUTS T_GLOBAL
%token <token> T_IF T_UNLESS T_ELSE T_WHILE T_TIMES

%type <expr> expression identifier
%type <boolean> bool_stmt

%nonassoc IFX
%nonassoc T_ELSE

%left T_AND T_OR
%left T_GE T_LE T_NE T_EQUAL '<' '>'
%left '+' '-'
%left '*' '/'

%nonassoc UNARY

%start program

%%

program : statements
        ;

statements : statement
           | statements statement
           ;

statement : expression 
          | assignment 
          | loop 
          | condition
          | T_PUTS expression { std::cout << $2->evaluate() << std::endl; }
          | T_PUTS bool_stmt {  std::string val = ($2->evaluate() == true) ? "true" : "false";
                                std::cout << "bool:" << val << std::endl; }
          | T_SEP
          ;

identifier : T_VAR { $$ = $1; }
           | T_FLOAT { $$ = $1; }
           | T_INT { $$ = $1; }
           /*| T_STRING { $$ = $1; }*/
           ;

expression : identifier { $$ = $1; }
           | '-' expression %prec UNARY { $$ = new NumExpression($2, new NumExpression(-1), '*'); }
           | expression '+' expression { $$ = new NumExpression($1, $3, '+'); }
           | expression '-' expression { $$ = new NumExpression($1, $3, '-'); }
           | expression '*' expression { $$ = new NumExpression($1, $3, '*'); }
           | expression '/' expression { $$ = new NumExpression($1, $3, '/'); }
           | '(' expression ')' { $$ = $2; }
           ;

assignment : T_VAR '=' expression
           | T_GLOBAL T_VAR '=' expression
           ;

loop : T_WHILE expression T_DO statements T_END
     | T_INT T_TIMES T_DO statements T_END
     ;

bool_stmt : T_BOOL { $$ = $1; }
          | bool_stmt T_AND bool_stmt { $$ = new BoolExpression($1, $3, 1); }
          | bool_stmt T_OR bool_stmt  { $$ = new BoolExpression($1, $3, 2); }
          | '(' bool_stmt ')' { $$ = $2; }
          | expression T_EQUAL expression { $$ = new BoolExpression($1, $3, 3); }
          | expression T_GE expression { $$ = new BoolExpression($1, $3, 4); }
          | expression T_LE expression { $$ = new BoolExpression($1, $3, 5); }
          | expression T_NE expression { $$ = new BoolExpression($1, $3, 6); }
          | expression '>' expression { $$ = new BoolExpression($1, $3, 7); }
          | expression '<' expression { $$ = new BoolExpression($1, $3, 8); }
          | '!' bool_stmt %prec UNARY { $$ = new BoolExpression($2, 0, 9); }
          ;

condition : T_IF bool_stmt T_DO statements T_END 
          | T_IF bool_stmt T_DO statements T_ELSE statements T_END
          | T_UNLESS bool_stmt T_DO statements T_END 
          | T_UNLESS bool_stmt T_DO statements T_ELSE statements T_END
          ;

%%

int main(int argc, char *argv[]) {
    //yydebug = 1;

    if (argc == 2) {
        yyin = fopen(argv[1], "r");
        yyparse();
    } else {
        std::cerr << "No input file!" << std::endl;
    }
}
