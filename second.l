%{
    #include <stdio.h>
    int counter = 0;
%}

%%
if|else|string|for|while|int|float|char|double {counter ++; printf("%s is a keyword\n" ,yytext);}
[a-zA-Z_][a-zA-Z_0-9]* {counter ++; printf("%s is an identifier\n" ,yytext);}
-?[0-9]+(.[0-9]+)? {counter ++; printf("%s is a number\n" ,yytext);}
\n {return 0;}
%%

int yywrap(){
return 1;
}

int main(){
printf("Enter the input: ");
yylex();
printf("Total number of tokens are:%d", counter) ;
return 0;
}