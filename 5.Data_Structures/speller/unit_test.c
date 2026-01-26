#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global variable to count words for size function
unsigned int num_words = 0;
const int LENGTH = 45;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = (17576);

// Hash table
node *table[N];

// Prototypes
bool check(const char *word);
unsigned int hash(const char *word);
bool load(const char *dictionary);

int main(int argc, char *argv[])
{
    load(argv[1]);
    const char *word = get_string("Enter word: ");
    if (check(word) == true)
    {
        printf("Word found in dictionary\n");
    }
    else
    {
        printf("Word not found in dictionary\n");
    }
    printf("No. Words: %i\n", num_words);
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int key = hash(word);
    node *ptr = table[key];
    while (ptr != NULL)
    {
        if (strcmp(ptr->word, word) == 0)
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
    printf("hash %lu\n", hash % N);
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
        printf("Error loading dictionary file\n");
        return false;
    }

    // Read each word in the file
    char *word = malloc(LENGTH + 1);
    if (word == NULL)
    {
        printf("Error: Not enough memory\n");
        return false;
    }
    while ((fscanf(f, "%s", word) != EOF))
    {
        // Create temporary pointer
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Error: Not enough memory\n");
            return false;
        }

        // Insert new word to beginning of the list
        unsigned int key = hash(word);

        strcpy(n->word, word);
        n->next = table[key];
        table[key] = n;

        // Incrememt word counter
        num_words++;
    }

    fclose(f);
    free(word);

    return true;
}
