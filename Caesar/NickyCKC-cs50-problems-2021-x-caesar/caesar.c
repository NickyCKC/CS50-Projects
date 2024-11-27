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

    else
    {

        //Check k is non-negative integer
        if (argv[1] < 0)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }

        //Prompt user for input
        else
        {
            in = get_string("plaintext: ");

            //Output cipher
            printf("ciphertext: ");

            //Convert string to int
            int k = atoi(argv[1]);

            //Create loop
            while (k >= 26)
            {
                k = k - 26;
            }


            int n = strlen(in);

            int i;

            for (i = 0; i < n; i++)
            {
                int t = (in[i] + k);
                int f = (t - 26);

                //For lower case
                if (islower(in[i]))
                {
                    //Loop
                    if (t  > 122)
                    {
                        printf("%c", f);
                    }

                    else
                    {
                        printf("%c", t);
                    }
                }

                //For upper case
                else if (isupper(in[i]))
                {
                    //Loop
                    if (t > 90)
                    {
                        printf("%c", f);
                    }

                    else
                    {
                        printf("%c", t);
                    }
                }

                //Print out punctuations etc.
                else
                {
                    printf("%c", in[i]);
                }
            }
        }
    }
    //End program
    printf("\n");
    return 0;
}