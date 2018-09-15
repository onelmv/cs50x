//~/pset1/credit
//credit.c
//pset1 cs50
//onelmv
//9.15.2018
//verification if a credit card number is valid according to Luhn’s algorithm.

#include<stdio.h>
#include<cs50.h>
#include<math.h>

int n_length(long long cardNumb);
int luhn(long long cardNumb);
int card_name(long long cardNumb, int length);

int main(void)
{
    long long card_n;

    //prompt
    do
    {
        card_n = get_long_long("Number: ");
    }
    while (card_n <= 0);

    //Check if it is a correct number or not. If it is ,we use it.
    int l = n_length(card_n); //store number length.
    if (l >= 13 && l <= 16)
    {
        if (l == 14)
        {
            printf("INVALID\n");
        }

        //Luhn’s algorithm.
        if (luhn(card_n) == 1)
        {
            //Card type.
            int c = card_name(card_n, l);
            if (c == 1)
            {
                printf("VISA\n");
            }
            else if (c == 2)
            {
                printf("MASTERCARD\n");
            }
            else if (c == 3)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n"); // Invalid checksum.
        }
    }
    else
    {
        printf("INVALID\n");  //Invalid number length.
    }

}//end

//length number function.
int n_length(long long cardNumb)
{
    int count = 0;
    //This while go to check each digit (From the end to the beginning)
    while (cardNumb >= 1)
    {
        cardNumb = cardNumb / 10 ;
        count++;
    }
    return count;
}

//Luhn function
int luhn(long long cardNumb)
{
    int sum = 0;
    int temp = 0;

    while (cardNumb > 0)
    {
        sum = sum + cardNumb % 10;  //Store the last digit.
        cardNumb = cardNumb / 10;   //go to another digit.
        temp = (cardNumb % 10) * 2; //Multiply by two and store temporarily

        if (temp >= 10) //If the result is greater than 10, sum each digit.
        {
            temp = (temp % 10) + (temp / 10);
        }
        sum = sum + temp;
        cardNumb = cardNumb / 10;
    }
    if (sum % 10 == 0)  //If checksum is correct return 1.
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//CArd type function
int card_name(long long cardNumb, int length)
{
    if (length == 16)  //Check if is MASTERCARD or VISA.
    {
        int temp = cardNumb / pow(10, 15); //take the first digit .. pow(10,15) = 10^15
        int temp2 = cardNumb / pow(10, 14); //take two first digit
        if (temp == 4)
        {
            return 1;  //VISA
        }
        else if (temp2 == 51 || temp2 == 52 || temp2 == 53 || temp2 == 54 || temp2 == 55)
        {
            return 2; // MASTERCARD
        }
    }
    else if (length == 13)
    {
        int temp3 = cardNumb / pow(10, 12);
        if (temp3 == 4)
        {
            return 1; //visa
        }

    }
    else if (length == 15)
    {
        int temp4 = cardNumb / pow(10, 13);
        if (temp4 == 34 || temp4 == 37)
        {
            return 3; //AMEX
        }
    }

    return 0; //INVALID
}
