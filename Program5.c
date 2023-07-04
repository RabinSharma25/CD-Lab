/*
This code only works for the following production or the productions
containing the following characters which means you can interchange the location of variables but 
in this program the follow of a variable cannot be more than one character at the moment.
Dont put S in any other production than S>ABCD as this changes the follows significantly but u can try other productions.
S->ABCD
A->b
B->c
C->d
D->e
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

char LHS[6] = {'S', 'A', 'B', 'C', 'D'}; /*The LHS side of the productions*/
char RHS[10][10] = {"ABCD.", "b.", "c.", "d.", "e."};  /*The RHS side of the productions*/
char FIRST[5];  /*Stores the found First*/
char FOLLOW[5][5];/*Stores the found Follows*/

int i, j, k, req, fn, row, col;
char r;

void checkFollow()
{
    if (islower(RHS[i][req]))   /*if the charater found is a terminal(small letters) then it is placed in follow*/ 
    {
        FOLLOW[row][col] = RHS[i][req];
    }
    else            /*if nonterminal(capital letter) is found as a follow then we need to put the first of the found nonterminal
                    as the follow of the variable that is being calculated*/
    {
        switch (RHS[i][req])
        {
        case 'A':
            k = 1;
            FOLLOW[row][0] = FIRST[k];
            break;
        case 'B':
            k = 2;
            FOLLOW[row][0] = FIRST[k];
            break;
        case 'C':
            k = 3;
            FOLLOW[row][0] = FIRST[k];
            break;
        case 'D':
            k = 4;
            FOLLOW[row][0] = FIRST[k];
            break;
        case 'S':
            k=0;
            FOLLOW[row][0] = FIRST[k];
            break;
        case '.':               /*but if '.' is found in the follow then that means we need to give the follow
        of the LHS variable as the follow for the variable that is being calculated.*/
            FOLLOW[row][0] = FOLLOW[0][0];
            if(islower(FOLLOW[0][1]))
            {
                FOLLOW[row][1] = FOLLOW[0][1];
            }
        default:
            break;
        }
    }
}

int main()
{
    printf("Enter the LHS of the set of productions:\n");
    for (i = 0; i < 5; i++)
    {
        scanf(" %c", &LHS[i]);
    }
    printf("Enter the RHS of the set of productions:\n");
    for (i = 0; i < 5; i++)
    {
        printf("For productions of %c with \".\" at the end of RHS:\n",LHS[i]);
        for (j = 0; j < 10; j++)
        {
            scanf(" %c", &RHS[i][j]);
            if (RHS[i][j] == '.')
            {
                break;
            }
        }
    }

    for (i = 0; i <= 5; i++)
    {
        if (islower(RHS[i][0])) // Checks if the first element in RHS is lowercase or not
        {
            FIRST[i] = RHS[i][0];
        }
        else /* if the RHS is not lower case then k should be given that is the index where the found
        variables production is stored*/
        {
            if (RHS[i][0] == 'A')
            {
                k = 1; // since production of A is stored in index 1 of RHS
            }
            else if (RHS[i][0] == 'B')
            {
                k = 2;
            }
            else if (RHS[i][0] == 'C')
            {
                k = 3;
            }
            else if (RHS[i][0] == 'D')
            {
                k = 4;
            }
            FIRST[i] = RHS[k][0];
        }
    }
    printf("FIRST:\n");
    for (i = 0; i < 5; i++)
    {
        printf("%c FIRST -> %c\n", LHS[i], FIRST[i]);
    }

    // For follow from here

    FOLLOW[0][0] = '$';
    for (i = 0; i < 5; i++) //i should be less than 5 as there are only 5 productions
    {
        for (j = 0; j <= 10; j++) 
        {
            switch (RHS[i][j])
            {
            case '.':
                j == 11;
                break;

            case 'S':
                req = j + 1;
                row = 0;    //implies in which row of follow matrix we should store our follow
                col = 1;    //implies in which row of follow matrix we should store our follow
                checkFollow();  /*checks for the following character of found variable i.e here it is 
                checking what character is there in RHS after the Variable S*/  
                break;

            case 'A':
                req = j + 1;
                row = 1;
                col = 0;
                checkFollow();
                break;
            case 'B':
                req = j + 1;
                row = 2;
                col = 0;
                checkFollow();
                break;
            case 'C':
                req = j + 1;
                row = 3;
                col = 0;
                checkFollow();
                break;
            case 'D':
                req = j + 1;
                row = 4;
                col = 0;
                checkFollow();
                break;

            default:
                break;
            }
        }
    }

    printf("\nFOLLOW:\n");
    for (i = 0; i < 5; i++)
    {
        printf("%c FOLLOW -> %c %c\n", LHS[i], FOLLOW[i][0], FOLLOW[i][1]);
    }

    return 0;
}
