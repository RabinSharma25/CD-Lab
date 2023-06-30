// operator precedence parser
#include <stdio.h>

void displayProductions(char prod[100][100], int pLen[], int noProd)
{
    for (int i = 1; i <= noProd; i++)
    {
        for (int j = 1; j <=pLen[i]; j++)
        {
            printf("%c", prod[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int noOfProductions;
    int productionLength[100];
    char productions[50][100];
    
    printf("Enter the number of productions\n");
    scanf("%d", &noOfProductions);
    for (int i = 1; i <= noOfProductions; i++)
    {

        printf("Enter the length of production no %d\n", i);
        scanf("%d", &productionLength[i]);
        printf("Enter production%d\n", i);
        for (int j = 1; j <= productionLength[i]; j++)
        {
            scanf(" %c", &productions[i][j]);
        }
    }

    printf("The set of productions are as follows:\n");
    displayProductions(productions, productionLength, noOfProductions);

    return 0;
}

// 5
// 5
// E>E+E
// 5
// E>E*E
// 5
// E>E/E
// 5
// E>E-E
// 3
// E>a