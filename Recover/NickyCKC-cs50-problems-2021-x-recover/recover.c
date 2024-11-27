#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //Check no. of command-line-arguments
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    //Open card.raw
    FILE *file = fopen(argv[1], "r");

    //Check if file pointing to free memory
    if (file == NULL)
    {
        printf("Unable to read %s\n", argv[1]);
        return 2;
    }

    //Initialize
    int counter = 0;
    FILE *img = NULL;
    char filename[8];
    BYTE buffer[512];

    //Check whether there is still memory in file
    while (fread(&buffer, 512, 1, file) == 1)
    {
        //Check for JPEG signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //Close file
            if (counter != 0)
            {
                fclose(img);
            }

            //Create new file
            sprintf(filename, "%03i.jpg", counter);
            img = fopen(filename, "w");
            counter++;
        }

        //Write data in file until new JPEG signature is picked up
        if (counter != 0)
        {
            fwrite(&buffer, 512, 1, img);
        }
    }

    //Close files
    fclose(file);
    fclose(img);
    return 0;
}