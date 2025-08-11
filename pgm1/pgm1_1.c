#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Check if a string is a keyword
int isKeyword(const char *str) {
    const char *keywords[] = {
        "auto","break","case","char","const","continue","default","do","double","else","enum",
        "extern","float","for","goto","if","int","long","register","return","short","signed",
        "sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while","printf"
    };
    int n = sizeof(keywords)/sizeof(keywords[0]);
    for (int i = 0; i < n; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

// Check if character is an operator
int isOperator(char c) {
    return (c=='+'||c=='-'||c=='*'||c=='/'||c=='='||c=='%'||c=='<'||c=='>'||c=='!'||c=='&'||c=='|');
}

// Check if character is a special symbol (punctuation)
int isSpecialSymbol(char c) {
    return (c=='{'||c=='}'||c=='('||c==')'||c=='['||c==']'||c==';'||c==','||c=='#');
}

int main() {
    FILE *f1;
    char filename[100] = "input";
    char c, buffer[100];
    int index = 0, lineno = 1;

    f1 = fopen(filename, "r");
    if (!f1) {
        perror("Error opening input file");
        return 1;
    }

    printf("\n%-15s | %-10s | %-5s\n", "Lexeme", "Token Type", "Line");
    printf("----------------------------------------\n");

    while ((c = fgetc(f1)) != EOF) {
        // Track line number
        if (c == '\n') { lineno++; continue; }

        // Skip whitespace
        if (isspace(c)) continue;

        // Identifier or keyword
        if (isalpha(c) || c == '_') {
            index = 0;
            buffer[index++] = c;
            while ((c = fgetc(f1)) != EOF && (isalnum(c) || c=='_')) {
                buffer[index++] = c;
            }
            buffer[index] = '\0';
            ungetc(c, f1);

            if (isKeyword(buffer))
                printf("%-15s | %-10s | %-5d\n", buffer, "Keyword", lineno);
            else
                printf("%-15s | %-10s | %-5d\n", buffer, "Identifier", lineno);
        }
        // Number literal
        else if (isdigit(c)) {
            index = 0;
            buffer[index++] = c;
            while ((c = fgetc(f1)) != EOF && isdigit(c)) {
                buffer[index++] = c;
            }
            buffer[index] = '\0';
            ungetc(c, f1);
            printf("%-15s | %-10s | %-5d\n", buffer, "Literal", lineno);
        }
        // Operator
        else if (isOperator(c)) {
            char op[3] = {c, '\0', '\0'};
            char next = fgetc(f1);
            // Handle 2-char operators: ++, --, ==, <=, >=, !=, &&, ||
            if ((c=='+' && next=='+') || (c=='-' && next=='-') ||
                (c=='=' && next=='=') || (c=='!' && next=='=') ||
                (c=='<' && next=='=') || (c=='>' && next=='=') ||
                (c=='&' && next=='&') || (c=='|' && next=='|')) {
                op[1] = next;
            } else {
                ungetc(next, f1);
            }
            printf("%-15s | %-10s | %-5d\n", op, "Operator", lineno);
        }
        // Special symbol
        else if (isSpecialSymbol(c)) {
            char symbol[2] = {c, '\0'};
            printf("%-15s | %-10s | %-5d\n", symbol, "Special", lineno);
        }
        // Ignore unknown characters silently
    }

    fclose(f1);
    return 0;
}