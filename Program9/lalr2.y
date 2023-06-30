%{
#include<stdio.h>
#include<stdlib.h>
%}

%token A B NL
%%
stmt: S NL {printf("valid string\n");
exit(0);};

S: A S B |;
%%
int yyerror(char *msg)
{
    printf("Invalid\n");
    exit(0);
}

main()
{
    printf("Enter string\n");
    yyparse();
}