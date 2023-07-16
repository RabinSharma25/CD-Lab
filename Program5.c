/*
This program works for all first and all follow calculation except for a situation where the epsilon need to be
brought above in previous production and the follows needs to be special here.
In first and follow functions Stacks are used to store the return address of j or k which might change by doing recursion
and as Stack follows Last In First Out methods hence its easier to implement in resursion as it return address has
similar concept.
*/

#include <stdio.h>
#include <ctype.h>

int i, j, k, l, state;
int noOfProductions, productionLength[50];
char productions[50][50];
char FIRST[10];
char FOLLOW[10];
char stack[100];
int top, top1 = 0;
int STACK1[100];
char vari[100];
int noOfVari, noOfFirst, noOfFollow;

void first(char var)
{
    for (j = 0; j < noOfProductions; j++)
    {
        if (var == productions[j][0])
        {
            if (isupper(productions[j][3]))
            {
                top1++;
                STACK1[top1] = j; // Storing the return address as the variable j changes when going inside first function
                first(productions[j][3]);
                j = STACK1[top1];
                top1--;
            }
            else
            {
                top++;
                stack[top] = productions[j][3];
            }
        }
    }
}

char follow(char var)
{
    if (var == productions[0][0])
    {
        top++;
        stack[top] = '$';
    }

    for (j = 0; j < noOfProductions; j++)
    {
        for (k = 3; k < productionLength[j]; k++)
        {
            if (k == productionLength[j] - 1 && var == productions[j][k])
            {
                if (var == productions[j][0])
                {
                    continue;
                }

                top1++;
                STACK1[top1] = j;
                top1++;
                STACK1[top1] = k;
                follow(productions[j][0]);
                k = STACK1[top1];
                top1--;
                j = STACK1[top1];
                top1--;
            }
            else if (var == productions[j][k])
            {
                if (isupper(productions[j][k + 1]))
                {
                    top1++;
                    STACK1[top1] = j;
                    first(productions[j][k + 1]);
                    j = STACK1[top1];
                    top1--;
                }
                else
                {
                    top++;
                    stack[top] = productions[j][k + 1];
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
        printf("Enter the production no. %d and enter \"#\" instead of epsilon:\n", i + 1);
        for (j = 0; j < productionLength[i]; j++)
        {
            scanf(" %c", &productions[i][j]);
        }
    }
    k = -1;
    for (i = 0; i < noOfProductions; i++)
    {
        state = 0;
        for (j = 0; j <= k; j++)
        {
            if (vari[j] == productions[i][0])
            {
                state = 1;
                break;
            }
        }
        if (state == 0)
        {
            k++;
            vari[k] = productions[i][0];
        }
    }
    noOfVari = k + 1;

    for (i = 0; i < noOfVari; i++)
    {
        top = 0;
        first(vari[i]);

        // Removing the first duplicates
        k = -1;
        for (j = 1; j <= top; j++)
        {
            state = 0;
            for (l = 0; l <= k; l++)
            {
                if (FIRST[l] == stack[j])
                {
                    state = 1;
                    break;
                }
            }
            if (state == 0)
            {
                k++;
                FIRST[k] = stack[j];
            }
        }
        noOfFirst = k + 1;

        top = 0;
        follow(vari[i]);

        // Removing the follow duplicates
        k = -1;
        for (j = 1; j <= top; j++)
        {
            state = 0;
            for (l = 0; l <= k; l++)
            {
                if (FOLLOW[l] == stack[j])
                {
                    state = 1;
                    break;
                }
            }
            if (state == 0)
            {
                k++;
                FOLLOW[k] = stack[j];
            }
        }
        noOfFollow = k + 1;

        printf("%c FIRST->\t", vari[i]);
        for (int j = 0; j < noOfFirst; j++)
        {
            if (j == noOfFirst - 1)
            {
                printf("%c", FIRST[j]);
            }
            else
            {
                printf("%c,", FIRST[j]);
            }
        }
        printf("\n");

        printf("%c FOLLOW->\t", vari[i]);
        for (int j = 0; j < noOfFollow; j++)
        {
            if (j == noOfFollow - 1)
            {
                printf("%c", FOLLOW[j]);
            }
            else
            {
                printf("%c,", FOLLOW[j]);
            }
        }
        printf("\n\n");
    }
}

/* Try the following Productions:
Set of Production 1:
4
4
S->A
4
A->b
4
S->c
4
A->d

Set of Production 2:
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

Set of Production 3:
4
6
S->ABc
5
A->bC
4
B->c
4
C->d

Set of production 4:
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

Set of Production 5:
5
4
S->a
4
A->B
4
B->b
4
S->A
4
A->c

Set of Production 6:
5
7
S->ABSC
4
A->a
6
B->bCa
5
C->BA
4
A->d


8
5
E->TS
6
S->+TS
4
S->#
5
T->FR
6
R->*FR
4
R->#
6
F->(E)
4
F->a
*/