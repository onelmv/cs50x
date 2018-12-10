// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45
//#define ARRAY_SIZE 26 // 26 letters lowcase

// Prototypes
bool load(const char *dictionary);
bool check(const char *word);
unsigned int size(void);
bool unload(void);

#endif // DICTIONARY_H

//////////////////////////////

// Node struct for my list
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Hash function . Return an index for the hash table
int hash(const char *word);
// Insert a word into the hash table
bool insert(char *word);
