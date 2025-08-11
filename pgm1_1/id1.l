%{
#include<stdio.h>
%}

%%
if|else|while|int|switch|for      { printf("%s is a keyword\n", yytext); }
[a-zA-Z]([a-zA-Z0-9])*            { printf("%s is an identifier\n", yytext); }
[0-9]+                            { printf("%s is a number\n", yytext); }
%%

int main() {
    yylex();
    return 0;
}

int yywrap() { return 1; }