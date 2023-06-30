/*vowel and consonent*/
%{
#include<stdio.h>
int vowel = 0;
int consonent = 0;
%}

%%
"a"|"e"|"i"|"o"|"u"|"A"|"E"|"I"|"O"|"U" {printf("It is a vowel\n");vowel++;}
[a-zA-Z] {printf("It is a consonent\n");consonent++;}
%%

int yywrap()
{
	return 1;
}
int main()
{
	printf("Enter Character:\n");
	yylex();
	printf("Vowel count = %d and Consonent count = %d.",vowel,consonent);
	return 0;
}
