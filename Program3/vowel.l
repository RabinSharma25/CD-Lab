/*vowel and consonent*/
%{
#include<stdio.h>
int vowel = 0;
int consonent = 0;
%}

%%
"a"|"e"|"i"|"o"|"u"|"A"|"E"|"I"|"O"|"U" {printf("Vowel\n");vowel++;}
[a-zA-Z] {printf("Consonent\n");consonent++;}
\n  {printf("\nVowel count:%d\nConsonent Count:%d\n",vowel,consonent);vowel=0;consonent=0;}
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
