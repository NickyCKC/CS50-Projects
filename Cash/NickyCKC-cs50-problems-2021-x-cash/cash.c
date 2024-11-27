#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    
    //Prompt user for any amount of money greater than 0
    
    float n;
    do
    {
        n = get_float("Change owed: ");
    }
    
    //Reprompt if amount is <= 0
    
    while (n <= 0);

    //Convert dollars into cents to avoid mistakes
    
    int m = round(n * 100);

    
    //Calculate coins needed for change
    
    int a;
    for (a = 0; m >= 25; a++)
    {
        m = (m - 25);
    }

    int b;
    for (b = 0; m >= 10; b++)
    {
        m = (m - 10);
    }
    
    int c;
    for (c = 0; m >= 5; c++)
    {
        m = (m - 5);
    }
    
    int d;
    for (d = 0; m >= 1; d++)
    {
        m = (m - 1);
    }
    
    //Print the no. of coins returned
    
    printf("%i\n", a + b + c + d);

}
