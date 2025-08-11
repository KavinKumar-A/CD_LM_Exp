#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void keyword(char str[100])
{
    if (strcmp("for", str) == 0 || strcmp("while", str) == 0 || strcmp("do", str) == 0 ||
        strcmp("int", str) == 0 || strcmp("float", str) == 0 || strcmp("char", str) == 0 ||
        strcmp("double", str) == 0 || strcmp("printf", str) == 0 || strcmp("switch", str) == 0 ||
        strcmp("case", str) == 0)
        printf("\n%s is a keyword", str);
    else
        printf("\n%s is an identifier", str);
}

int main()
{
    FILE *f1, *f2, *f3;
    char c, str[100];     // safer buffer size
    int num[1000];        // store numbers
    int lineno = 0, tokenvalue = 0, i = 0, j = 0, k = 0;

    // Open input file
    f1 = fopen("input", "r");
    if (!f1) {
        perror("Error opening input file");
        return 1;
    }

    // Open output files
    f2 = fopen("identifier", "w");
    if (!f2) {
        perror("Error opening identifier file");
        fclose(f1);
        return 1;
    }

    f3 = fopen("specialchar", "w");
    if (!f3) {
        perror("Error opening specialchar file");
        fclose(f1);
        fclose(f2);
        return 1;
    }

    // Lexical analysis
    while ((c = getc(f1)) != EOF)
    {
        if (isdigit(c))
        {
            tokenvalue = c - '0';
            c = getc(f1);
            while (isdigit(c))
            {
                tokenvalue = tokenvalue * 10 + (c - '0');
                c = getc(f1);
            }
            num[i++] = tokenvalue;
            ungetc(c, f1);
        }
        else if (isalpha(c))
        {
            putc(c, f2);
            c = getc(f1);
            while (isdigit(c) || isalpha(c) || c == '_' || c == '$')
            {
                putc(c, f2);
                c = getc(f1);
            }
            putc(' ', f2);  // separate identifiers by space
            ungetc(c, f1);
        }
        else if (c == ' ' || c == '\t')
        {
            // Ignore whitespace
        }
        else if (c == '\n')
        {
            lineno++;
        }
        else
        {
            putc(c, f3);  // special characters
        }
    }

    fclose(f1);
    fclose(f2);
    fclose(f3);

    // Print numbers found
    printf("\nThe numbers in the program are:");
    for (j = 0; j < i; j++)
        printf("\t%d", num[j]);
    printf("\n");

    // Process identifiers and check keywords
    f2 = fopen("identifier", "r");
    if (!f2) {
        perror("Error reopening identifier file");
        return 1;
    }

    k = 0;
    printf("The keywords and identifiers are:");
    while ((c = getc(f2)) != EOF)
    {
        if (c != ' ')
        {
            str[k++] = c;
            if (k >= 99) k = 99;  // prevent overflow
        }
        else
        {
            str[k] = '\0';
            keyword(str);
            k = 0;
        }
    }
    fclose(f2);

    // Print special characters
    f3 = fopen("specialchar", "r");
    if (!f3) {
        perror("Error reopening specialchar file");
        return 1;
    }

    printf("\nSpecial Characters are:");
    while ((c = getc(f3)) != EOF)
        printf("\t%c", c);
    printf("\n");
    fclose(f3);

    printf("Total number of lines: %d\n", lineno);
    return 0;
}