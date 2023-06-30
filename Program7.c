// operator precedence parser
#include <stdio.h>

char precedenceTab[100][100];
char terminal[50];
int terminalNo = 1;

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

void createPTab()
{
    terminal[terminalNo] = '$';
    precedenceTab[0][0] = ' ';

    for (int i = 0; i <= terminalNo; i++)
    {
        for (int j =0; j <= terminalNo; j++)
        {
            if (i == j && i == 0)
            {
                continue;
            }
            else if (i == 0)
            {
                precedenceTab[i][j] = terminal[j];
            }
            else if (j == 0)
            {
                precedenceTab[i][j] = terminal[i];
            }
            else if ((terminal[i] == 'a' || terminal[i] == '$') && i == j)
            {
                precedenceTab[i][j] = '_';
            }
            else if (i == j && terminal[i] != 'a' && terminal[i] != '$')
            {
                precedenceTab[i][j] = '>';
            }
            else if (terminal[i] == '$' || terminal[j] == 'a')
            {
                precedenceTab[i][j] = '<';
            }
            else if (terminal[i] == 'a' || terminal[j] == '$')
            {
                precedenceTab[i][j] = '>';
            }
            else if ((terminal[i] == '*' || terminal[i] == '/') && (terminal[j] == '-' || terminal[j] == '+'))
            {
                precedenceTab[i][j] = '>';
            }
            else if ((terminal[i] == '+' || terminal[i] == '-') && (terminal[j] == '*' || terminal[j] == '/'))
            {
                precedenceTab[i][j] = '<';
            }
            else if ((terminal[i] == '+' && terminal[j] == '-') || (terminal[i] == '-' && terminal[j] == '+') || (terminal[i] == '*' && terminal[j] == '/') || (terminal[i] == '/' && terminal[j] == '*'))
            {
                precedenceTab[i][j] = '>';
            }
        }
    }
    
    printf("The precedence Table is as follows:\n");
    for (int i = 0; i <= terminalNo; i++)
    {
        for (int j = 0; j <= terminalNo; j++)
        {
            printf(" %c\t", precedenceTab[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int noOfProductions,flag;
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

    // Terminal Determining part
    for (int i = 1; i <= noOfProductions; i++)
    {
        for (int j = 1; j <= productionLength[i]; j++)
        {
            flag = 0;
            /*If the char in the production are than capital letters or > char
            then they will be considered as terminal. */
            if (isupper(productions[i][j]) || productions[i][j] == '>')
            {
                continue;
            }
            else
            {
                if (productions[i][j] == 'a')
                {
                    terminal[terminalNo] = terminal[1];
                    terminal[1] = productions[i][j];
                    terminalNo++;
                }
                else
                {
                    terminal[terminalNo] = productions[i][j];
                    terminalNo++;
                }
            }
        }
    }

    printf("The set of productions are as follows:\n");
    displayProductions(productions, productionLength, noOfProductions);
    createPTab();
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