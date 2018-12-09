// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

//My hash table
node *hash_table[26] = {NULL}; // 26 letters lowcase
// Amount of words into the dictionary
int word_counter = 0;


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Opening dictionary
    FILE *dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        printf("Error opening the dictionary file\n");
        fclose(dic);
        return false;
    }
    else
    {
        //for store each word in the dictionary
        char dic_word[LENGTH + 1] = {0};

        // Get word by word
        while (fscanf(dic, "%s", dic_word) != EOF)
        {
            if (!insert(dic_word))
            {
                printf("Error inserting word into the hash table\n");
                unload();
                return false;
            }
            else
            {
                word_counter++;
            }
        }
        fclose(dic);
        return true;
    }
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // head of a list in the exact block of the array
    node *head = hash_table[hash(word)]; //WORD FROM TEXT
    // if is NULL , it isn't in the dic
    if (!head)
    {
        return false;
    }
    else
    {
        //traversing the list
        while (head != NULL)
        {
            if (strcasecmp(head->word, word) == 0) // strcascmp convert 2 strings lower case before compare theys.
            {
                return true;
            }
            // moving to next pointer
            head = head->next;
        }
        // out of the while , them not finds coincidences
        return false;
    }
}



// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return word_counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < 26; i++)
    {
        node *head = hash_table[i];
        while (head != NULL)
        {
            node *temp = head;
            head = head->next;
            free(temp);
        }
        //free (head);
    }


    return true;
}


////////////////
//My Functions//
////////////////

int hash(const char *word)
{
    if (word != NULL)
    {
        int index = tolower(word[0]) - 97; // 97 is 'a' in ASCII;
        return index; // return tolower(word[0]) - 97;
    }
    else
    {
        printf("Error in hash function\n");
        return -1;
    }
}

bool insert(char *word)
{
    // New node for a new word
    node *new_node = malloc(sizeof(node));
    //cheking if new node was successfully created
    if (!new_node)
    {
        return false;
    }
    else
    {
        // Index value from hash function
        int index = hash(word);
        strcpy(new_node->word, word);

        // For empty list
        if (hash_table[index] == NULL)
        {
            new_node->next = NULL;
            hash_table[index] = new_node;
            return true;
        }
        else
        {
            new_node->next = hash_table[index];
            hash_table[index] = new_node;
            return true;
        }
    }
}
