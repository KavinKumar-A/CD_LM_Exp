%{
#include <stdio.h>
#include <stdlib.h>    // for exit()
int yylex();
void yyerror(const char *s);
%}

%token ID DIG
%left '+' '-'
%left '*' '/'
%right UMINUS

%%

stmt: expn            { printf("Valid Expression\n"); }
    ;

expn: expn '+' expn
    | expn '-' expn
    | expn '*' expn
    | expn '/' expn
    | '-' expn %prec UMINUS
    | '(' expn ')'
    | DIG
    | ID
    ;

%%

int main() {
    printf("Enter the Expression: ");
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    printf("Invalid Expression\n");
    exit(0);
}