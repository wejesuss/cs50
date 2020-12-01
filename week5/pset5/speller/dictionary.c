// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

// Number of buckets in hash table
const unsigned int N = LENGTH * 90;

// Hash table
node *table[N];

// word for dictionary
char dic_word[LENGTH + 1];

// size of the dictionary
int dic_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int code = hash(word);
    node *cursor = table[code];

    return find(cursor, word);
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int code = tolower(word[0]);

    for (int i = 1; word[i] != '\0'; i++)
    {
        code = code * 31 + tolower(word[i]);
    }

    return code % N;
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

    char c;
    int index = 0;

    while (fread(&c, sizeof(char), 1, file))
    {
        if (c == '\n')
        {
            // Terminate current word
            dic_word[index] = '\0';
            int code = hash(dic_word);

            bool inserted = insert_node(code, index, dic_word);
            if (!inserted)
            {
                fclose(file);
                printf("Error inserting %s.\n", dic_word);
                unload();
                return false;
            }

            // Reset index
            index = 0;
            // Update counter
            dic_size++;
        }
        else
        {
            dic_word[index] = c;
            index++;
        }
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
    for (int i = 0; i < N; i++)
    {
        // Recursively free memory
        free_list(table[i]);
    }

    return true;
}

// Add node in hash table
bool insert_node(unsigned int code, int length, char *word)
{
    node *n = malloc(sizeof(node));

    do
    {
        n->word[length] = word[length];
        length--;
    }
    while (length >= 0);

    if (table[code] == NULL)
    {
        n->next = NULL;
        table[code] = n;
    }
    else
    {
        n->next = table[code];
        table[code] = n;
    }

    return true;
}

// Find an element in hash table
bool find(node *cursor, const char *word)
{
    if (cursor == NULL)
    {
        return false;
    }

    if (strcasecmp(cursor->word, word) == 0)
    {
        return true;
    }

    return find(cursor->next, word);
}

// Free memory used by a linked list
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
