/* generation of tokens using lex tool using odd and even numbers*/ 

%{
	#include<stdio.h>
	int num;
%}

%%
[0-9]+ {num = atoi(yytext);
		if(num%2==0)
		{printf("%d is Even ",num);
		 }
		else
		{printf("%d is Odd",num);
		 }
		}
%%

int yywrap() 
{
	return 1;
}
int main()
{
	
	printf("Enter Number:\n");
	yylex();
	return 0;
}
