// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Global variable to count words for size function
unsigned int num_words = 0;

// Create 26 x 26 x 26 buckets in hash table
const unsigned int N = (17576);

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Convert word to lowercase
    int len = strlen(word);
    char word_lowerc[len];

    for (int i = 0; i < len; i++)
    {
        word_lowerc[i] = tolower(word[i]);
    }
    word_lowerc[len] = '\0';

    // Create temporary node and initialise it to the hash key
    node *ptr = table[hash(word_lowerc)];
    while (ptr != NULL)
    {
        if (strcmp(ptr->word, word_lowerc) == 0)
        {
            return true;
        }
        else
        {
            ptr = ptr->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // djb2 hash function found online, by Daniel J. Bernstein.
    unsigned long hash = 5381;
    int c;
    while ((c = *word++) != 0)
    {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open dictionary file
    FILE *f = fopen(dictionary, "r");
    if (f == NULL)
    {
        return false;
    }

    // Read each word in the file
    char *word = malloc(LENGTH + 1);
    if (word == NULL)
    {
        return false;
    }
    while ((fscanf(f, "%s", word) != EOF))
    {
        // Create temporary pointer
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        // Insert new word to beginning of the list
        strcpy(n->word, word);
        n->next = table[hash(word)];
        table[hash(word)] = n;

        // Incrememt word counter
        num_words++;
    }

    fclose(f);
    free(word);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Return the global variable calculated in the load function
    return num_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *ptr;
    for (int i = 0; i < N; i++)
    {
        ptr = table[i];
        while (ptr != NULL)
        {
            node *next = ptr->next;
            free(ptr);
            ptr = next;
        }
        table[i] = NULL;
    }
    return true;
}
