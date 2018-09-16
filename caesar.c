//~/pset2/caesar
//caesar.c
//pset2 cs50
//onelmv
//9.16.2018
//Caesar cypher

#include<stdio.h>
#include<cs50.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char Encrypting(char c, int key);

int main(int argc, string argv[])
{
    int key = 0;

    if (argc <= 2 && argc > 1) // Run if there are only two parameter.
    {
        key = atoi(argv[1]);

        if (key > 0) 
        {
            string plain_text = get_string("plaintext: "); 
            int len_text = strlen(plain_text);  

            printf("ciphertext: ");
            for (int i = 0 ; i < len_text; i++)
            {
                printf("%c", Encrypting(plain_text[i], key));
            }
            printf("\n");
        }
    }
    else
    {
        printf("Usage: ./caesar k\n");
        return 1;
    }
}//end

char Encrypting(char c, int key)
{
    if (isalpha(c))
    {
        if (isupper(c))
        {
            return (c - 65 + key) % 26 + 65;

        }
        else
        {   
            //islower()
            return (c - 97 + key) % 26 + 97;
        }
    }
    //no change
    return c;
}