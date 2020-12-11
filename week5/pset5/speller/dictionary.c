// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Number of buckets in hash table
const unsigned int N = 150000;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Prototypes
bool insert_node(unsigned int code, char *word);
bool find(node *cursor, const char *word);
void free_list(node *list);

// Hash table
node *table[N];

// word for dictionary and check function
char dic_word[LENGTH + 1];

// size of the dictionary
int dic_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int i;
    for (i = 0; word[i] != '\0'; i++)
    {
        dic_word[i] = tolower(word[i]);
    }

    dic_word[i] = '\0';

    int code = hash(dic_word);
    node *cursor = table[code];

    return find(cursor, dic_word);
}

// Hashes word to a number
// hash function from http://www.cse.yorku.ca/~oz/hash.html
unsigned int hash(const char *word)
{
    unsigned int hash_code = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        int c = word[i];
        hash_code = c + (hash_code << 6) + (hash_code << 16) - hash_code;
    }

    return hash_code % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }

    while (fscanf(file, "%s", dic_word) != EOF)
    {
        int code = hash(dic_word);
        bool inserted = insert_node(code, dic_word);
        if (!inserted)
        {
            fclose(file);
            printf("Error inserting %s.\n", dic_word);
            unload();
            return false;
        }

        // Update counter
        dic_size++;
    }

    if (ferror(file))
    {
        fclose(file);
        printf("Error reading %s.\n", dictionary);
        unload();
        return false;
    }

    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dic_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Free memory used by a linked list
    for (int i = 0; i < N; i++)
    {
        free_list(table[i]);
    }

    return true;
}

// Add node in hash table
bool insert_node(unsigned int code, char *word)
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return false;
    }

    strcpy(n->word, word);
    n->next = table[code];
    table[code] = n;

    return true;
}

// Find an element in hash table
bool find(node *cursor, const char *word)
{
    if (cursor == NULL)
    {
        return false;
    }

    if (strcmp(cursor->word, word) == 0)
    {
        return true;
    }

    return find(cursor->next, word);
}

// Recursively free memory
void free_list(node *n)
{
    if (n == NULL)
    {
        return;
    }

    free_list(n->next);
    free(n);
    return;
}
