//~/pset1/mario/less/
//mario.c
//pset1 cs50
//onelmv
//9.12.2018
//Print a half-pyramid from 0 to 23 steps.

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

    //print half-pyramid
    for (int i = 0 ; i < h ; i++)     // print each line.
    {
        for (int j = 0 ; j < h - i - 1; j++) //print spaces.
        {
            printf(" ");
        }

        for (int k = 0 ; k < i + 2 ; k++) //print hashes.
        {
            printf("#");
        }
        printf("\n");   //new line
    }
}
