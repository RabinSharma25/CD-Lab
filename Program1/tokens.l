/*generation of tokens using lex tool*/

%{
	#include<stdio.h>
%}

%%
"auto"|"else"|"long"|"break"|"enum"|"case"|"extern"|"register"|"return"|"char"|"float"|"short"|"const"|"for"|"signed"|"continue"|"goto"|"sizeof"|"static"|"if"|"default"|"struct"|"int"|"do"|"double"|"_Packed"|"while"|"volatile"|"void"|"unsigned"|"union"|"typedef"|"switch" {printf("Keyword");}
"!="|"=="|"<>"|">"|"<"|">="|"<=" {printf("Relational operator");}
"-"|"+"|"/"|"*"|"=" {printf("Operator");}
[0-9]+ { printf("Number");}
[A-Za-z_]([A-Za-z_]|[0-9_])* {printf("Identifier");}
.* { printf("Not an identifier");}
%%      

int yywrap()
{
	return 1;
}

int main()
{
	printf("Enter the code:");
	yylex();
	return 0;
}