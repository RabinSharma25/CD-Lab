/*
This program works for all first and most follow calculation except for a situation where the epsilon need to be
brought above in previous production and the follows needs to be special here.
In first and follow functions Stacks are used to store the return address of j or k which might change by doing recursion
and as Stack follows Last In First Out methods hence its easier to implement in resursion as it return address has
similar concept and the functions first and follow returns an array cotaining the calculated first and follow.
*/

#include <stdio.h>
#include <ctype.h>

int i, j, k, l, p, state;

char productions[50][50]; // Array to store productions
int noOfProductions, productionLength[50];

char vari[100]; // array containing unique variables
int noOfVari;

int STACK1[100]; // array to track recursion
int top = 1;
int top1 = 0;

char firFol[100]; // array for raw calculated first and follow

char fil[100]; // array storing filtered first and follow
int noOfItems;

char stack[100];
int col, ctop = 0;
int cstack[100];

char *arr1;
int x, xtop[100], xt = 0;

int xtop1 = 0;
char *func(char var, char oVar);
int pcount,flag;
char *first(char var, char oVar)
{
    pcount = 0;
    flag = 0;
    col = 3;
    for (j = 0; j < noOfProductions; j++)
    {
        if (var == productions[j][0])
        {
            pcount++;
            if (isupper(productions[j][col]))
            {
                flag = 1;
                top1++;
                STACK1[top1] = j; // Storing the return address as the variable j changes when going inside first function
                top1++;
                STACK1[top1] = flag;
                ctop++;
                cstack[ctop] = col;
                xt++;
                xtop[xt] = top;
                top1++;
                STACK1[top1] = pcount;
                arr1 = first(productions[j][col], oVar);
                pcount = STACK1[top1];
                top1--;
                col = cstack[ctop];
                ctop--;
                flag = STACK1[top1];
                top1--;
                j = STACK1[top1];
                top1--;
                xt--;

                if (arr1[(arr1[0] - 48) - 1] == '&' && col == productionLength[j] - 1 && var == oVar)
                {
                    firFol[top] = '#';
                    top++;
                    firFol[0] = top + '0';
                }
                else if (arr1[(arr1[0] - 48) - 1] == '&')
                {
                    ctop++;
                    cstack[ctop] = col;
                    func(var, oVar);
                    col = cstack[ctop];
                    ctop--;
                }
            }
            else if (productions[j][col] == '#' && col == productionLength[j] - 1 && var != oVar)
            {
                firFol[top] = '&';
                top++;
                firFol[0] = top + '0';
            }
            else
            {
                firFol[top] = productions[j][col];
                top++;
                firFol[0] = top + '0'; // storing the first element as digit
            }
        }
    }

    for (x = xtop[xt]; x < top; x++)
    {
        if ((flag == 1 && firFol[top - 1] == '&' && pcount == 1) || (flag == 0 && firFol[x] == '&') || (flag == 1 && firFol[x] == '&' && pcount != 1))
        {
            firFol[top] = '&';
            top++;
            firFol[0] = top + '0';
            break;
        }
    }
    return firFol;
}

char *func(char var, char oVar)
{
    col++;
    if (isupper(productions[j][col]))
    {
        top1++;
        STACK1[top1] = j; // Storing the return address as the variable j changes when going inside first function
        ctop++;
        cstack[ctop] = col;
        xt++;
        xtop[xt] = top;
        arr1 = first(productions[j][col], oVar);

        col = cstack[ctop];
        ctop--;
        j = STACK1[top1];
        top1--;
        xt--;
        if (arr1[(arr1[0] - 48) - 1] == '&' && col == productionLength[j] - 1 && var == oVar)
        {
            firFol[top] = '#';
            top++;
            firFol[0] = top + '0';
        }
        else if (arr1[(arr1[0] - 48) - 1] == '&' && col == productionLength[j] - 1)
        {
            return 0;
        }
        else if (arr1[(arr1[0] - 48) - 1] == '&')
        {
            func(var, oVar);
        }
    }
    else
    {
        firFol[top] = productions[j][col];
        top++;
        firFol[0] = top + '0';
    }
}

char *follow(char var, char oVar)
{
    if (var == productions[0][0])
    {
        firFol[top] = '$';
        top++;

        firFol[0] = top + '0';
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
                follow(productions[j][0], oVar);
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
                    first(productions[j][k + 1], oVar);
                    j = STACK1[top1];
                    top1--;
                }
                else
                {
                    firFol[top] = productions[j][k + 1];
                    top++;
                    firFol[0] = top + '0';
                }
            }
        }
    }
    return firFol;
}

void filter(char *arr) // function for removing duplicacies
{
    k = -1;
    for (j = 1; j < (arr[0] - 48); j++)
    {
        state = 0;
        for (l = 0; l <= k; l++)
        {
            if (fil[l] == arr[j])
            {
                state = 1;
                break;
            }
        }
        if (state == 0 && arr[j] != '&')
        {
            k++;
            fil[k] = arr[j];
        }
    }
    noOfItems = k + 1;
}

void display(char var)
{
    char *arr;
    printf("First(%c)  - ", var);
    arr = first(var, var);
    filter(arr);
    for (int i = 0; i < noOfItems; i++)
    {
        printf("%c,", fil[i]);
    }
    printf("\b \b\n");
    top = 1;
    top1 = 0;
    printf("Follow(%c) - ", var);
    arr = follow(var, var);
    filter(arr);
    for (int i = 0; i < noOfItems; i++)
    {
        printf("%c,", fil[i]);
    }
    printf("\b \b \n\n");
    top = 1;
    top1 = 0;
}

void populateVari() // This function populates the vari array with the unique variables in the productions.
{
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
}

void input()
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
}

int main()
{
    input();
    populateVari();
    // displaying first and follow

    for (i = 0; i < noOfVari; i++)
    {
        display(vari[i]);
    }

    return 0;
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

Set of Production 7:
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

Set of Production 8:
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
4
F->#
4
F->a

Set of Production 9:
6
5
S->AC
4
A->#
4
A->B
4
B->c
4
C->d
4
C->#

Set of Production 10:
9
7
S->aBDh
5
B->cC
5
C->bC
4
C->#
5
D->EF
4
E->g
4
E->#
4
F->f
4
F->#

Set of Production 11:
5
6
S->(L)
4
S->a
5
L->SK
6
K->,SK
4
K->#

Set of Production 12:
4
7
S->AaAb
7
S->BbBa
4
A->#
4
B->#

Set of Production 13:
9
6
S->ACB
6
S->CbB
5
S->Ba
5
A->da
5
A->BC
4
B->g
4
B->#
4
C->h
4
C->#
*/