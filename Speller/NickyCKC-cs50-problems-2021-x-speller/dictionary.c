// Implements a dictionary's functionality

#include <stdbool.h>
#include "dictionary.h"
#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Required for int returned after using hash function
unsigned int hash_value;

// To keep track of words each time one is updated into load function
unsigned int word_count;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Get int value from hash function
    hash_value = hash(word);

    // Create a cursor node to check through linked list of nodes
    node *cursor = table[hash_value];

    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }
    // Return false if word not found in dictionary
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    // Source from djb2 Dan Bernstein, http://www.cse.yorku.ca/~oz/hash.html
    unsigned long hash = 5381;
    int c;
    while ((c = toupper(*word++)))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{

    // TODO
    //Open dictionary file
    FILE *dict = fopen(dictionary, "r");
    // If file cannot open, return false
    if (dict == NULL)
    {
        return false;
    }


    // Initialise word
    char word[LENGTH + 1];

    // Read till end of file
    while (fscanf(dict, "%s", word) != EOF)
    {
        // Allocate memory for new node
        node *n = malloc(sizeof(node));
        // If NULL returned, return false
        if (n == NULL)
        {
            return false;
        }

        // Copy word into word field of new node
        strcpy(n->word, word);

        // Create an int that has hash value of word
        hash_value = hash(word);

        // Point next field of new node to table with hash value
        n->next = table[hash_value];

        // Point tbale with hash value to new node
        table[hash_value] = n;

        // Increase word count
        word_count++;
    }

    // Close file
    fclose(dict);

    // Return true if data loaded
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Check if word count is updated after running load function
    if (word_count > 0)
    {
        return word_count;
    }

    // If word count not updated due to failed load function
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate though all the tables
    for (int i = 0; i < N; i++)
    {
        // Set cursor equal to the table[i]
        node *cursor = table[i];

        // Iterate though linked list until all memory is freed
        while (cursor != NULL)
        {
            node *tmp = cursor;

            cursor = cursor->next;

            free(tmp);
        }

        // Check if all memory is freed
        if (i == N - 1 && cursor == NULL)
        {
            return true;
        }
    }
    return false;
}
