%{
#include <stdio.h>
#include <stdlib.h>

// Declare functions so Bison knows about them
int yylex(void);
int yyerror(const char *s);
%}

%token LET DIG

%%
variable : var
         ;

var : var LET
    | var DIG
    | LET
    ;
%%

int main() {
    printf("Enter the variable: ");
    if (yyparse() == 0) {
        printf("✅ Valid variable\n");
    }
    return 0;
}

int yyerror(const char *s) {
    printf("❌ Invalid variable\n");
    exit(1);
}