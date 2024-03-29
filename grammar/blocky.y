%{
#include <stdlib.h>

#include <iostream>
#include <string>

#include "src/statement.hpp"
#include "src/assignStatement.hpp"
#include "src/blockStatement.hpp"
#include "src/putStatement.hpp"
#include "src/penStatement.hpp"

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
BlockScope *ifBlock = 0;

extern int yylex();

void yyerror(const char *s) {
    std::cerr << "ERROR: " << s << " in line " << yylineno << ". Unexpected token " << yylval.token << std::endl;
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

%token <token> T_EQUAL T_AND T_OR T_GE T_LE T_NE T_NIL
%token <token> T_SEP T_DO T_END T_PUTS T_GLOBAL T_PUT
%token <token> T_IF T_UNLESS T_ELSE T_WHILE T_TIMES
%token <token> PEN_GOTO PEN_TURN PEN_DRAW PEN_DELAY PEN_COLOR PEN_DIRECTION PEN_MOVE PEN_LINETO
%token <token> SCOPE_DUMP SCOPE_DUMPALL

%type <expr> expression identifier
%type <boolean> bool_stmt
%type <statement> statement assignment loop condition puts put pen_cmd scope_cmd

%nonassoc IFX
%nonassoc T_ELSE

%left T_EQUAL T_NE
%left T_AND T_OR
%left T_GE T_LE '<' '>'
%left '+' '-'
%left '*' '/' '%'
%left '^'

%nonassoc UNARY

%start program

%%

program : statements
        ;

statements : statement { current->add_statement($1); }
           | statements statement { current->add_statement($2); }
           | T_SEP
           | statements T_SEP
           ;

statement : assignment T_SEP
          | loop T_SEP
          | condition T_SEP
          | puts T_SEP
          | put T_SEP
          | pen_cmd T_SEP
          | scope_cmd T_SEP
          ;

scope_cmd : SCOPE_DUMP { $$ = new BlockStatement(7, current); }
          | SCOPE_DUMPALL { $$ = new BlockStatement(8, current); }
          ;

pen_cmd : PEN_GOTO expression ',' expression { $$ = new PenStatement(1, $2, $4); }
        | PEN_TURN expression { $$ = new PenStatement(2, $2); }
        | PEN_DRAW expression { $$ = new PenStatement(3, $2); }
        | PEN_DELAY expression { $$ = new PenStatement(4, $2); }
        | PEN_COLOR expression ',' expression ',' expression { $$ = new PenStatement(5, $2, $4, $6); }
        | PEN_DIRECTION expression { $$ = new PenStatement(6, $2); }
        | PEN_MOVE expression { $$ = new PenStatement(7, $2); }
        | PEN_LINETO expression ',' expression { $$ = new PenStatement(8, $2, $4); }
        ;

puts      : T_PUTS expression { $$ = new PutStatement(1, $2); }
          | T_PUTS bool_stmt {  $$ = new PutStatement(1, $2); }
          | T_PUTS T_STRING { $$ = new PutStatement(1, $2); }
          | T_PUTS { $$ = new PutStatement(1, new std::string("")); }
          ;

put       : T_PUT expression { $$ = new PutStatement(2, $2); }
          | T_PUT bool_stmt {  $$ = new PutStatement(2, $2); }
          | T_PUT T_STRING { $$ = new PutStatement(2, $2); }
          ;

identifier : T_VAR { $$ = new NumExpression(current, *$1); }
           | T_FLOAT { $$ = $1; }
           | T_INT { $$ = $1; }
           ;

expression : identifier { $$ = $1; }
           | '-' expression %prec UNARY { $$ = new NumExpression($2, new NumExpression(-1), '*'); }
           | expression '^' expression { $$ = new NumExpression($1, $3, '^'); }
           | expression '+' expression { $$ = new NumExpression($1, $3, '+'); }
           | expression '-' expression { $$ = new NumExpression($1, $3, '-'); }
           | expression '*' expression { $$ = new NumExpression($1, $3, '*'); }
           | expression '/' expression { $$ = new NumExpression($1, $3, '/'); }
           | expression '%' expression { $$ = new NumExpression($1, $3, '%'); }
           | '(' expression ')' { $$ = $2; }
           ;

assignment : T_VAR '=' expression { $$ = new AssignStatement(current, *$1, $3); }
           | T_VAR '=' T_NIL { $$ = new AssignStatement(current, *$1); }
           | T_GLOBAL T_VAR '=' expression { $$ = new AssignStatement(global, *$2, $4); }
           ;

block : T_DO T_SEP statements T_END
      ;

loop : T_WHILE bool_stmt block { $$ = new BlockStatement(4, $2, current); current = current->get_parent(); } 
     | expression '.' T_TIMES block { $$ = new BlockStatement(3, $1, current); current = current->get_parent(); }
     ;

bool_stmt : T_BOOL { $$ = $1; }
          | bool_stmt T_AND bool_stmt { $$ = new BoolExpression($1, $3, 1); }
          | bool_stmt T_OR bool_stmt  { $$ = new BoolExpression($1, $3, 2); }
          | '(' bool_stmt ')' { $$ = $2; }
          | bool_stmt T_EQUAL bool_stmt { $$ = new BoolExpression($1, $3, 3); }
          | T_VAR '.' T_NIL '?' { $$ = new BoolExpression(current, *$1, 10); }
          | expression T_EQUAL expression { $$ = new BoolExpression($1, $3, 3); }
          | expression T_GE expression { $$ = new BoolExpression($1, $3, 4); }
          | expression T_LE expression { $$ = new BoolExpression($1, $3, 5); }
          | expression T_NE expression { $$ = new BoolExpression($1, $3, 6); }
          | expression '>' expression { $$ = new BoolExpression($1, $3, 7); }
          | expression '<' expression { $$ = new BoolExpression($1, $3, 8); }
          | '!' bool_stmt %prec UNARY { $$ = new BoolExpression($2, 0, 9); }
          ;

condition : T_IF bool_stmt block { $$ = new BlockStatement(1, $2, current); current = current->get_parent(); }
          | T_IF bool_stmt T_DO T_SEP statements T_ELSE T_SEP statements T_END { $$ = new BlockStatement(5, $2, ifBlock, current); 
                                                                                 current = current->get_parent(); ifBlock = 0; }
          | T_UNLESS bool_stmt block { $$ = new BlockStatement(2, $2, current); current = current->get_parent(); }
          | T_UNLESS bool_stmt T_DO T_SEP statements T_ELSE T_SEP statements T_END { $$ = new BlockStatement(6, $2, ifBlock, current); 
                                                                                     current = current->get_parent(); ifBlock = 0; }
          ;

%%

int main(int argc, char *argv[]) {
    //yydebug = 1;

    if (argc == 2) {
        yyin = fopen(argv[1], "r");
        yyparse();

        try {
            global->evaluate();

            Pen::instance()->close_listener();
        } catch (const std::exception &e) {
            std::cerr << std::endl << ">> ----------------------------------- <<" << std::endl;
            std::cerr << "   Runtime exception! Program aborted: " << std::endl;
            std::cerr << "       " << e.what() << std::endl;
            std::cerr << ">> ----------------------------------- <<" << std::endl << std::endl;
        }
    } else {
        std::cerr << "No input file!" << std::endl;
    }
}
