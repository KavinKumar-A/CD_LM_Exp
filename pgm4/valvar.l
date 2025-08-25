%{
#include "valvar.tab.h"
%}

%%
[a-zA-Z]        { return LET; }       // Single alphabet
[0-9]           { return DIG; }       // Single digit
\n              { return 0; }         // End of input
.               { return yytext[0]; } // Any other character
%%

int yywrap() {
    return 1;
}