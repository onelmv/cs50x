//~/pset1/mario/more/
//mario.c
//pset1 cs50
//onelmv
//9.13.2018
//Print two half-pyramids from 0 to 23 steps.

#include<stdio.h>
#include<cs50.h>

int main(void)
{
    // h is the height.
    int h;

    //pront to evaluate input.
    do
    {
        h = get_int("Height : ");

    }
    while (h < 0 || h > 23);

    //print pyramid
    for (int i = 0 ; i < h ; i++)     // print each line.
    {
        for (int j = 0 ; j < h - i - 1; j++) //print spaces.
        {
            printf(" ");
        }

        for (int k = 0 ; k < i + 1 ; k++) //print left hashes.
        {
            printf("#");
        }

        printf("  ");   //print 2 spaces

        for (int l = 0 ; l < i + 1 ; l++) // print right hashes.
        {
            printf("#");
        }

        printf("\n");   //new line
    }
}
