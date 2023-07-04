/*This program works for all those production whereeach variables have only one first and follow.
This also means those productions which have no starting variable on the RHS of production and all 
variables occur only once on the RHS throughout the productions regardless of production they are in.
Here the terminal can be anything other than uppercase due to use of isupper function for variables.*/
#include <stdio.h>
#include <ctype.h>

int i, j, k, l;
int noOfProductions, productionLength[50];
char productions[50][50];
char FIRST[10];
char FOLLOW[10];

char first(char var)
{
    for (j = 0; j < noOfProductions; j++)
    {
        if (var == productions[j][0])
        {
            if (isupper(productions[j][3]))
            {
                return first(productions[j][3]);
            }
            else
            {
                return productions[j][3];
            }
        }
    }
}
char follow(char var)
{
    for (j = 0; j < noOfProductions; j++)
    {
        if (var == productions[0][0])
        {
            return '$';
        }
        else
        {
            for (k = 3; k < productionLength[j]; k++)
            {
                if (k == productionLength[j] - 1 && var == productions[j][k])
                {
                    return follow(productions[j][0]);
                }
                else if (var == productions[j][k])
                {
                    if (isupper(productions[j][k + 1]))
                    {
                        return first(productions[j][k + 1]);
                    }
                    else
                    {
                        return productions[j][k + 1];
                    }
                }
            }
        }
    }
}

int main()
{
    printf("Enter the no of productions:\n");
    scanf("%d", &noOfProductions);
    for (i = 0; i < noOfProductions; i++)
    {
        printf("Enter the length of the productions no. %d in the format E->aB:", i + 1);
        scanf("%d", &productionLength[i]);
        printf("Enter the production no. %d:\n", i + 1);
        for (j = 0; j < productionLength[i]; j++)
        {
            scanf(" %c", &productions[i][j]);
        }
    }
    printf("Variable\tFirst\t\tFollow\n");

    for (i = 0; i < noOfProductions; i++)
    {
        FIRST[i] = first(productions[i][0]);
        FOLLOW[i] = follow(productions[i][0]);
        printf("%c\t\t%c\t\t%c\n", productions[i][0], FIRST[i], FOLLOW[i]);
    }
}

/* Try the following Productions:
Set of Production 1:
5
7
S->ABCD
4
A->b
4
B->c
4
C->d
4
D->e

Set of Production 2:
4
6
S->ABc   
5
A->bC
4
B->c
4
C->d

Set of production 3:
5
5
S->AB
5
A->cC
4
B->d
5
C->De
4
D->b
*/