// recursive descent parser 

//E-->TE'
//E'-->+TE'|NULL
//T-->FT'
//T'-->*FT'|NULL
//F-->(E)|a

#include <stdio.h>
#include<stdlib.h>
#include<string.h>

int i;
char expression[1000];
void E();
void Eds();
void T();
void Tds();
void F();

int main()
{
    printf("Enter the string to be checked for acceptance:\n");
    gets(expression);
    E();
    if(i == strlen(expression))
    {
        printf("The string %s is accepted.\n",expression);
    }
    else
    {
        printf("The string %s is rejected\n",expression);
    }

    return 0;
}
void T()
{
    F();
    Tds();
}
void E()
{
    T();
    Eds();
}



void Eds()
{
    if(expression[i]== '+')
    {
        i++;
        T();
        Eds();
    }
    else
    {

        return ;
    }
}

void F()
{
    if(expression[i]=='(')
    {
        i++;
        E();
        if(expression[i]==')')
        {
            i++;
        }
        else
        {
            printf("The string is rejected.\n");
            exit(0);
        }
    }
    else if(expression[i]=='a')
    {
        i++;
    }
    else
    {
        printf("The string is rejected.\n");
        exit(0);
    }
}
void Tds()
{
    if(expression[i]=='*')
    {
        i++;
        F();
        Tds();
    }
    else
    {
        return ;
    }
}




