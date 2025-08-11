%{
#include <stdio.h>
#include "y.tab.h"   // Include the tokens from Yacc
%}

%%
[a-zA-Z][0-9a-zA-Z]*    { return ID; }      // Identifier
[0-9]+                  { return DIG; }     // Number
[ \t]+                  { /* Ignore spaces */ }
.                       { return yytext[0]; }  // Return character for operators
\n                      { return 0; }       // End of input
%%

int yywrap() {
    return 1;
}