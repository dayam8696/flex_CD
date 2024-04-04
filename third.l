%{
    #include <stdio.h>
    int counter = 0;
%}

%%
if|else|string|for|while|int|float|char|double {counter ++; printf("%s is a keyword\n" ,yytext);}
[a-zA-Z_][a-zA-Z_0-9]* {counter ++; printf("%s is an identifier\n" ,yytext);}
-?[0-9]+(.[0-9]+)? {counter ++; printf("%s is a number\n" ,yytext);}
. ;
%%
int main(){
extern FILE *yyin;
yyin = fopen("Read_Me.txt","r");
if (yyin == NULL) {
    perror("Error opening file");
    return 1;
}
yylex() ;
printf("Total number Of tokens are: %d", counter);
fclose(yyin);
return 0;
}

int yywrap(){
return 1;
}