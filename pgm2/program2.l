%{
#include <stdio.h>
#include <stdlib.h>
%}

identifier     [a-zA-Z][a-zA-Z0-9]*

%%
#.*                        { printf("\n%s is a preprocessor directive", yytext); }
int                        { printf("\n%s is a keyword", yytext); }
{identifier}\(             { printf("\n\nFUNCTION FOUND: %s", yytext); }
\{                         { printf("\nBLOCK BEGINS"); }
\}                         { printf("\nBLOCK ENDS"); }
{identifier}               { printf("\n%s is an IDENTIFIER", yytext); }
.|\n                       { /* Ignore other characters */ }
%%

int main(int argc, char **argv) {
    FILE *file;

    if(argc > 1) {
        file = fopen(argv[1], "r");
        if(!file) {
            printf("\nCould not open %s\n", argv[1]);
            exit(0);
        }
        yyin = file;  // Set input file for lexer
    }

    yylex();  // Start lexical analysis
    printf("\n\n");
    return 0;
}

int yywrap() {
    return 1;
}