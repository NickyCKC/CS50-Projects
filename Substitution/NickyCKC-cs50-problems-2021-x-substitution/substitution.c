#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    string in;
    string out;

    //Check no. of command-line-arguments
    if (argc != 2)
    {
        printf("ERROR\n");
        return 1;
    }

    //Calculate strlen of command-line-argument
    int n = strlen(argv[1]);

    //Check length of command-line-argument
    if (n != 26)
    {
        printf("ERROR\n");
        return 1;
    }

    int j;
    int i;

    for (i = 0; i < n; i++)
    {
        //Check if %c is non-alphabet
        if (isalpha(argv[1][i]))
        {
            for (j = 0; j < i; j++)
            {
                //Check if alphabets repeat
                if (argv[1][j] == argv[1][i])
                {
                    printf("ERROR\n");
                    return 1;
                }
                if (argv[1][j] == argv[1][25])
                {
                    printf("ERROR\n");
                    return 1;
                }
            }
        }
        else
        {
            printf("ERROR\n");
            return 1;
        }
    }

    //Prompt user for text
    in = get_string("plaintext: ");

    //Calculate strlen of in
    int l;
    l = strlen(in);
    
    //Print cipher
    printf("ciphertext: ");

    int t;
    for (t = 0; t < l; t++)
    {
        //Check for lower case
        if (islower(in[t]))
        {
            printf("%c", tolower(argv[1][(in[t] - 97)]));
        }
        //Check for upper case
        else if (isupper(in[t]))
        {
            printf("%c", toupper(argv[1][(in[t] - 65)]));
        }
        //Print non-alphabets
        else
        {
            printf("%c", in[t]);
        }
    }
    printf("\n");
    return 0;
}