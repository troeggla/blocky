%{
#include "y.tab.hh"
%}

%%

^#.*\n     ;
[ \t]+\n   ;
.          return yytext[0];

%%
