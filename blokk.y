%{
#include <stdio.h>

#include <iostream>
#include <string>
#include <map>

#include "src/numExpression.hpp"

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
}

%token <expr> T_VAR T_FLOAT T_INT T_STRING T_BOOL

%token <token> T_EQUAL T_AND T_OR T_GE T_LE T_NE
%token <token> T_NIL T_SEP T_RETURN T_DO T_END T_PUTS T_GLOBAL
%token <token> T_IF T_UNLESS T_ELSE T_WHILE T_TIMES

%type <expr> expression identifier

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

bool_stmt : T_BOOL
          | bool_stmt T_AND bool_stmt
          | bool_stmt T_OR bool_stmt
          | '(' bool_stmt ')'
          | expression T_EQUAL expression
          | expression T_GE expression
          | expression T_LE expression
          | expression T_NE expression
          | expression '>' expression
          | expression '<' expression
          | '!' bool_stmt %prec UNARY
          ;

condition : T_IF bool_stmt T_DO statements T_END 
          | T_IF bool_stmt T_DO statements T_ELSE statements T_END
          | T_UNLESS bool_stmt T_DO statements T_END 
          | T_UNLESS bool_stmt T_DO statements T_ELSE statements T_END
          | assignment T_IF bool_stmt
          | assignment T_UNLESS bool_stmt
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
