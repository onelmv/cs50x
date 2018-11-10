//~/pset2/crack
//crack.c
//pset2 cs50
//onelmv
//9.20.2018
//cracking password

#define _XOPEN_SOURCE
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<cs50.h>




int main(int argc, string argv[])
{
    if (argc <= 2 && argc > 1) // Run if there are only two parameter.
    {
        char dic[52] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
                        'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                        'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
                        'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                        'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
                       };

        string word  = NULL; // string for build each word
        string hash = argv[1]; //original hash
        char salt[2] = {argv[1][0], argv[1][1]};
        string myHash;  //my hash for compare

        for (int i = 0; i < 52; i++)
        {
            word = &dic[i];
            myHash = crypt(word, salt); //creating my hash

            if (strcmp(myHash, hash) == 0)
            {
                printf("%s\n", word);
                return 0;
            }
        }
        for (int i = 0; i < 52; i++)
        {
            for (int j = 0; j < 52; j++)
            {
                word[0] = dic[i];
                word[1] = dic[j];
                myHash = crypt(word, salt);


                if (strcmp(myHash, hash) == 0)
                {
                    printf("%s\n", word);
                    return 0;
                }

            }
        }
        for (int i = 0; i < 52; i++)
        {
            for (int j = 0; j < 52; j++)
            {
                for (int k = 0; k < 52; k++)
                {
                    word[0] = dic[i];
                    word[1] = dic[j];
                    word[2] = dic[k];
                    myHash = crypt(word, salt);
                    if (strcmp(myHash, hash) == 0)
                    {
                        printf("%s\n", word);
                        return 0;
                    }

                }
            }
        }
        for (int i = 0; i < 52; i++)
        {
            for (int j = 0; j < 52; j++)
            {
                for (int k = 0; k < 52; k++)
                {
                    for (int l = 0; l < 52; l++)
                    {
                        word[0] = dic[i];
                        word[1] = dic[j];
                        word[2] = dic[k];
                        word[3] = dic[l];
                        myHash = crypt(word, salt);
                        if (strcmp(myHash, hash) == 0)
                        {
                            printf("%s\n", word);
                            return 0;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < 52; i++)
        {
            for (int j = 0; j < 52; j++)
            {
                for (int k = 0; k < 52; k++)
                {
                    for (int l = 0; l < 52; l++)
                    {
                        for (int m = 0; m < 52; m++)
                        {
                            word[0] = dic[i];
                            word[1] = dic[j];
                            word[2] = dic[k];
                            word[3] = dic[l];
                            word[4] = dic[m];
                            myHash = crypt(word, salt);
                            if (strcmp(myHash, hash) == 0)
                            {
                                printf("%s\n", word);
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {
        printf("Usage: ./crack hash\n"); // the arg have more than 1 parameter
        return 1;
    }
}//end