/*generation of tokens using lex tool*/


%{
	#include<stdio.h>
	int num;
%}

%%
"auto"|" else"|"long"|"break"|"enum"|"case"|" extern "|"register"|"return"|"char"|"float"|"short"|"const"|"for"|"signed"|"continue"|"goto"|"sizeof"|"static"|"if"|"default"|"struct"|"int"|"do"|"double"|"_Packed"|"while"|"volatile"|"void"|"unsigned"|"union"|"typedef"|"switch" {printf("Keyword");}
"!="|"=="|"<>"|">"|"<"|">="|"<=" {printf("relational op");}
"-"|"+"|"/"|"*"|"=" {printf("operator");}
[0-9]+ {num = atoi(yytext);
		printf("%d",num);
		}
[A-Za-z_(A-Za-z_0-9)*]+ {printf("Identifier");}

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
