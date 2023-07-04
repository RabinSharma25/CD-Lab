/*
This code works for the input similar to the one given below

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
*/

#include <stdio.h>
#include <ctype.h>
int noOfProductions;
int productionLength[100];
char productions[50][100];

char first(char var)
{
    for (int i = 0; i < noOfProductions; i++)
    {
        if (var == productions[i][0])
        {
            if (islower(productions[i][3]))
            {
                return productions[i][3];
            }

            else
            {
                return first(productions[i][3]);
            }
        }
    }
}

char follow(char var)
{
    for (int i = 0; i < noOfProductions; i++)
    {
        // for starting variable
        if (var == productions[0][0])
        {
            return '$';
        }

        // for rest of the variables
        else
        {
            for (int j = 3; j < productionLength[0]; j++)
            {
                // for the last variable
                if (j == productionLength[0] - 1)
                {
                    return follow(productions[0][0]);
                }

                else if (var == productions[0][j])
                {
                    return first(productions[0][j + 1]);
                }
            }
        }
    }
}

void displayProductions(char prod[100][100], int pLen[], int noProd)
{
    for (int i = 0; i < noProd; i++)
    {
        for (int j = 0; j < pLen[i]; j++)
        {
            printf("%c", prod[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    printf("Enter the number of productions\n");
    scanf("%d", &noOfProductions);
    for (int i = 0; i < noOfProductions; i++)
    {

        printf("Enter the length of production no %d\n", i);
        scanf("%d", &productionLength[i]);
        printf("Enter production%d\n", i);
        for (int j = 0; j < productionLength[i]; j++)
        {
            scanf(" %c", &productions[i][j]);
        }
    }

    // displayProductions(productions,productionLength,noOfProductions);
    int count = 0;
    printf("Variable        First       Follow\n");
    while (count < noOfProductions)
    {
        printf("%c                %c             %c\n", productions[count][0], first(productions[count][0]), follow(productions[count][0]));
        count++;
    }

    return 0;
}