%{
#include <stdio.h>

#include <iostream>
#include <string>
#include <map>

using namespace std;

extern int yylex();

void yyerror(const char *s) {
    fprintf(stderr, "ERROR: %s\n", s);
}
%}

%left '+' '-'
%left '*' '/'

%%

statements: ;

%%

extern FILE* yyin;

int main(int argc, char *argv[]) {
    if (argc == 2) {
        yyin = fopen(argv[1], "r");
        yyparse();
    } else {
        fprintf(stderr, "No input file!\n");
    }
}
