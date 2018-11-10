


#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    //argument
    char *card = argv[1];

    //opening files
    FILE *pCard = fopen(card, "r");
    FILE *img = NULL; // to create the jpeg files.

    if (pCard == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", card);
        return 2;
    }

    uint8_t block [512]; //size of each block on the card
    //printf("%li\n",ftell(pCard)); //print position (byte)
    char file_name[8]; //for store each jpg file name.
    int i = 0; // ccounter for each jpeg found.

    //Reading until the end of memory, (each block is 512, except the last one is <512)
    while ((fread(block, 1, 512, pCard)) == 512)
    {
        if (block[0] == 0xff &&
            block[1] == 0xd8 &&
            block[2] == 0xff &&
            (block[3] & 0xf0) == 0xe0)
        {
            if (img == NULL)
            {
                sprintf(file_name, "%03i.jpg", i);  //creating file name...
                img = fopen(file_name, "w"); //creating jpg file...
                fwrite(&block, 512, 1, img);
                i++;
            }
            else
            {
                fclose(img); // closing the previous jpg file to create a new one
                sprintf(file_name, "%03i.jpg", i);
                img = fopen(file_name, "w");
                fwrite(&block, 512, 1, img);
                i++;
            }
        }
        else
        {
            if (img != NULL) //continue writing jpg file
            {
                fwrite(&block, 512, 1, img);
            }
        }
        //printf("encontrados%i\n", i);
    }

    fclose(pCard);
    fclose(img);
    return 0;
}