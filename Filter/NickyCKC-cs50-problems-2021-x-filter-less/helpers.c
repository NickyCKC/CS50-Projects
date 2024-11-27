#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;
            int red = image[i][j].rgbtRed;

            float avg = (blue + green + red) / 3.0;
            avg = round(avg);

            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;
            int red = image[i][j].rgbtRed;

            float sepiaRed = .393 * red + .769 * green + .189 * blue;
            float sepiaGreen = .349 * red + .686 * green + .168 * blue;
            float sepiaBlue = .272 * red + .534 * green + .131 * blue;

            sepiaRed = round(sepiaRed);
            sepiaGreen = round(sepiaGreen);
            sepiaBlue = round(sepiaBlue);

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            if (j < j + 1 && j + 1 != width)
            {
                int tmp[3];
                tmp[0] = image[i][j].rgbtBlue;
                tmp[1] = image[i][j].rgbtGreen;
                tmp[2] = image[i][j].rgbtRed;
                
                
                image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
                image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
                image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
                
                image[i][width - j - 1].rgbtBlue = tmp[0];
                image[i][width - j - 1].rgbtGreen = tmp[1];
                image[i][width - j - 1].rgbtRed = tmp[2];
            }
        }
    }

    return;
}

int blurvalue(int i, int j, int height, int width, RGBTRIPLE image[height][width], int colour)
{
    int sum = 0;
    float counter = 0;
    
    for (int y = i - 1; y < i + 2; y++)
    {
        for (int x = j - 1; x < j + 2; x++)
        {
            if (y < 0 || x < 0 || y >= height || x >= width)
            {
                continue;
            }
            
            if (colour == 0)
            {
                sum += image[y][x].rgbtBlue;
            }
            
            else if (colour == 1)
            {
                sum += image[y][x].rgbtGreen;
            }
            
            else
            {
                sum += image[y][x].rgbtRed;
            }
            
            counter++;
        }
    }
    return round(sum / counter);
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = blurvalue(i, j, height, width, copy, 0);
            image[i][j].rgbtGreen = blurvalue(i, j, height, width, copy, 1);
            image[i][j].rgbtRed = blurvalue(i, j, height, width, copy, 2);
        }
    }

    return;
}