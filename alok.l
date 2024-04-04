%{
#include <stdio.h>
%}

%%

[A-Z]   { printf("%c is a capital letter\n", yytext[0]); }
[a-z]   { printf("%c is a small letter\n", yytext[0]); }
.       { printf("%c is not a letter\n", yytext[0]); }

%%
int yywrap(){
return 1;}

int main() {
    yylex();
    return 0;
}