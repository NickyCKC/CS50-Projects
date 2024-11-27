#include <stdio.h>
#include <cs50.h>

int main(void)
{
    
    //Prompt user for pyramid height
    
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    
    //Build pyramid structure
    
    int i;
    for (i = 1; i < n + 1; i++)
    {
        int j;
        for (j = n; j > i; j--)
        {
            printf(" ");
        }
        int k;
        for (k = 0; k < i; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}

//Replace "." with " "