%{
#include<stdio.h>
%}

%%

"+"|"-"|"/"|"*"  printf("It is an operator\n",yytext);
"if"|"else"|"for"|"int"|"while"|"bool"|"float"|"return"|"main"|"char"|"string"       printf("It is a keyword\n",yytext);
-?[0-9]*(\.[0-9]+)?                                                                  printf("It is a number\n",yytext);
[a-zA-Z_][0-9a-zA-Z]*                                                                printf("It is an identifier\n",yytext);
[0-9][0-9a-zA-Z]*                                                                    printf("It is not an identifier\n",yytext);

%%
int yywrap(){
return 1;}

int main()
{
    yylex();
    return 0;

}
