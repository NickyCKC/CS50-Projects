#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(void)
{
    //Prompt user for string
    string text;
    text = get_string("Text: ");
    
    //Count letters, words & sentences
    int s;
    int w;
    int i;
    int l;
    char x = '!';
    char y = '?';
    char z = '.';
    int n = strlen(text);
    
    for (i = 0, w = 1, s = 0, l = 0; i < n; i++)
    {
        //Count letters
        if (islower(text[i]))
        {
            l += 1;
        }
        else if (isupper(text[i]))
        {
            l += 1;
        }
        
        //Count words
        else if (text[i] == ' ')
        {
            w += 1;
        }
        
        //Count sentences
        else if (text[i] == '!')
        {
            s += 1;
        }
        
        else if (text[i] == '?')
        {
            s += 1;
        }
        
        else if (text[i] == '.')
        {
            s += 1;
        }
    }

    //Calculate the Coleman-Liau index
    float L;
    float S;
    
    //Calculate average number of letters/sentences per 100 words
    L = (float) l / w * 100;
    S = (float) s / w * 100;
    
    //Apply formula
    float I;
    I = 0.0588 * L - 0.296 * S - 15.8;
    
    //Round index to nearest whole number
    int g = round(I);
    
    //Calculate grade
    if (g >= 16)
    {
        printf("Grade 16+\n");
    }
    
    else if (g < 1)
    {
        printf("Before Grade 1\n");
    }
    
    else
    {
        printf("Grade %i\n", g);
    }
}