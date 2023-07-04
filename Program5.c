/*
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

char productions[100][100];
int productionLength[100];
int noProductions;

char first(char var)
{
    for (int i = 0; i < noProductions; i++)
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
    for(int i=0;i<noProductions;i++){
        if(var == productions[0][0]){
            return '$';
        }

        else{

            for(int j = 3;j<productionLength[0];j++){
                if(var == productions[0][j]){
                    return first(productions[0][j+1]);
                }

                else if(var == productions[0][productionLength[0]-1]){
                    return follow(productions[0][0]);
                }
            }
        }
    }
}
int main()
{
    printf("Enter the number of productions\n");
    scanf("%d", &noProductions);
    for (int i = 0; i < noProductions; i++)
    {
        printf("Enter the length of production %d\n", i);
        scanf("%d", &productionLength[i]);
        printf("Enter the production\n");
        for (int j = 0; j < productionLength[i]; j++)
        {
            scanf(" %c", &productions[i][j]);
        }
    }

    int count = 0;
    printf("Variable        First       Follow\n");
    while (count < noProductions)
    {
        printf("%c              %c              %c\n", productions[count][0], first(productions[count][0]),follow(productions[count][0]));
        count++;
    }
    return 0;
}