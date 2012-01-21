%{
#include <stdlib.h>

#include <iostream>
#include <string>

#include "src/statement.hpp"
#include "src/assignStatement.hpp"
#include "src/blockStatement.hpp"
#include "src/putStatement.hpp"
#include "src/blockScope.hpp"
#include "src/numExpression.hpp"
#include "src/boolExpression.hpp"
#include "parser.hpp"

#define YYDEBUG 1

extern FILE* yyin;
extern int yylineno;
extern YYSTYPE yylval;

BlockScope *global = new BlockScope();
BlockScope *current = global;

extern int yylex();

void yyerror(const char *s) {
    std::cerr << "ERROR: " << s << " in line " << yylineno-1 << ". Unexpected token " << yylval.token << std::endl;
    exit(1);
}
%}

%union {
    std::string *string;
    int token;
    NumExpression *expr;
    BoolExpression *boolean;
    Statement *statement;
}

%token <expr> T_FLOAT T_INT;
%token <boolean> T_BOOL;
%token <string> T_STRING T_VAR;

%token <token> T_EQUAL T_AND T_OR T_GE T_LE T_NE
%token <token> T_NIL T_SEP T_RETURN T_DO T_END T_PUTS T_GLOBAL
%token <token> T_IF T_UNLESS T_ELSE T_WHILE T_TIMES

%type <expr> expression identifier
%type <boolean> bool_stmt
%type <statement> statement assignment loop condition puts;

%nonassoc IFX
%nonassoc T_ELSE

%left T_EQUAL T_NE
%left T_AND T_OR
%left T_GE T_LE '<' '>'
%left '+' '-'
%left '*' '/'

%nonassoc UNARY

%start program

%%

program : statements
        ;

statements : statement { current->add_statement($1); }
           | statements statement { current->add_statement($2); }
           ;

statement : assignment T_SEP
          | loop T_SEP
          | condition T_SEP
          | puts T_SEP
          ;

puts      : T_PUTS expression { $$ = new PutStatement($2); }
          | T_PUTS bool_stmt {  $$ = new PutStatement($2); }
          | T_PUTS T_STRING { $$ = new PutStatement($2); }
          ;

identifier : T_VAR { $$ = new NumExpression(current, *$1); }
           | T_FLOAT { $$ = $1; }
           | T_INT { $$ = $1; }
           ;

expression : identifier { $$ = $1; }
           | '-' expression %prec UNARY { $$ = new NumExpression($2, new NumExpression(-1), '*'); }
           | expression '+' expression { $$ = new NumExpression($1, $3, '+'); }
           | expression '-' expression { $$ = new NumExpression($1, $3, '-'); }
           | expression '*' expression { $$ = new NumExpression($1, $3, '*'); }
           | expression '/' expression { $$ = new NumExpression($1, $3, '/'); }
           | '(' expression ')' { $$ = $2; }
           ;

assignment : T_VAR '=' expression { $$ = new AssignStatement(current, *$1, $3); }
           | T_GLOBAL T_VAR '=' expression { $$ = new AssignStatement(global, *$2, $4); }
           ;

block : T_DO T_SEP statements T_END
      ;

loop : T_WHILE bool_stmt block 
     | expression T_TIMES block
     ;

bool_stmt : T_BOOL { $$ = $1; }
          | bool_stmt T_AND bool_stmt { $$ = new BoolExpression($1, $3, 1); }
          | bool_stmt T_OR bool_stmt  { $$ = new BoolExpression($1, $3, 2); }
          | '(' bool_stmt ')' { $$ = $2; }
          | bool_stmt T_EQUAL bool_stmt { $$ = new BoolExpression($1, $3, 3); }
          | expression T_EQUAL expression { $$ = new BoolExpression($1, $3, 3); }
          | expression T_GE expression { $$ = new BoolExpression($1, $3, 4); }
          | expression T_LE expression { $$ = new BoolExpression($1, $3, 5); }
          | expression T_NE expression { $$ = new BoolExpression($1, $3, 6); }
          | expression '>' expression { $$ = new BoolExpression($1, $3, 7); }
          | expression '<' expression { $$ = new BoolExpression($1, $3, 8); }
          | '!' bool_stmt %prec UNARY { $$ = new BoolExpression($2, 0, 9); }
          ;

condition : T_IF bool_stmt block { $$ = new BlockStatement(1, $2, current); current = current->get_parent(); }
          | T_IF bool_stmt T_DO statements T_ELSE statements T_END
          | T_UNLESS bool_stmt block { $$ = new BlockStatement(2, $2, current); current = current->get_parent(); }
          | T_UNLESS bool_stmt T_DO statements T_ELSE statements T_END
          ;

%%

int main(int argc, char *argv[]) {
    //yydebug = 1;

    if (argc == 2) {
        yyin = fopen(argv[1], "r");
        yyparse();

        global->evaluate();
    } else {
        std::cerr << "No input file!" << std::endl;
    }
}
