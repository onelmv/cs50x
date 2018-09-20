//~/pset2/vinegere
//vinegere.c
//pset2 cs50
//onelmv
//9.19.2018
//Vinegere cypher.

#include<stdio.h>
#include<cs50.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

void Encrypting(string text, char key[], int len_key, int len_text);
bool isALphaStr(string k, int length);

int main(int argc, string argv[])
{
    if (argc <= 2 && argc > 1) // Run if there are only two parameter.
    {

        int len_key = strlen(argv[1]);

        if (isALphaStr(argv[1], len_key)) //Check if the key have only alpha char.
        {
            string plain_text = get_string("plaintext: ");
            int len_text = strlen(plain_text);  //plain tex length.

            printf("ciphertext: ");
            Encrypting(plain_text, argv[1], len_key, len_text);
            printf("\n");
        }
        else
        {
            printf("Usage: ./caesar k\n"); //the key don't have only alpha char.
            return 1;
        }
    }
    else
    {
        printf("Usage: ./caesar k\n"); // the arg have more than 1 parameter
        return 1;
    }
}//end

void Encrypting(string text, char key[], int len_key, int len_text)
{
    int j = 0; //key count

    for (int i = 0; i < len_text ; i++)
    {
        if (isalpha(text[i]))
        {
            if (isupper(text[i]))
            {
                // What kind of monster I have created 0_0 ....
                //I use toupper() to convert to uper or lower case , the key may be in either of the two.
                printf("%c", ((((text[i] - 65) + (toupper(key[j % len_key]) - 65)) % 26) + 65)) ;
            }
            else //islower()
            {
                printf("%c", ((((text[i]  - 97) + (tolower(key[j % len_key]) - 97)) % 26) + 97));
            }
            j++;
        }
        else
        {
            //Does not change if it is a symbol or space.
            printf("%c", text[i]);
        }
    }
}

bool isALphaStr(string key,  int len_k)
{
    //I have to improve this .... later
    int count = 0;
    for (int i = 0 ; i < len_k; i++)
    {
        if (isalpha(key[i]))
        {
            count++;
        }
        else
        {
            count--;
        }
    }
    if (count == len_k)
    {
        return true;
    }
    else
    {
        return false;
    }
}
