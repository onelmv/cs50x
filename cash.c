//~/pset1/cash
//cash.c
//pset1 cs50
//onelmv
//9.13.2018
//calculates the minimum number of coins required to give a user change.

#include<stdio.h>
#include<cs50.h>
#include<math.h>

int main(void)
{

    float c;    // c is the cash.
    int count = 0;  // count is the amount of coins.

    //pront to evaluate input.
    //input a float.
    do
    {
        c = get_float("Change owed: ");
    }
    while (c <= 0);

    //convert to cents
    int n = round(c * 100);

    //Calculating...
    while (n >= 25)
    {
        n = n - 25;
        count++;
    }
    while (n >= 10)
    {
        n = n - 10;
        count++;
    }
    while (n >= 5)
    {
        n = n - 5;
        count++;
    }
    while (n >= 1)
    {
        n = n - 1;
        count++;
    }

    printf("%i\n", count);
}