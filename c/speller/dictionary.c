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

bool unload_node(node *n);

// TODO: Choose number of buckets in hash table
const unsigned int N = 400000;
unsigned int word_count = 0;
// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *tmp = table[hash(word)];
    while (tmp != NULL)
    {
        register int i = strlen(word);
        if (i == strlen(tmp->word))
        {
            while (i > 0 && tolower(word[i]) == tmp->word[i])
            {
                i--;
            }
            if (i == 0)
            {
                return true;
            }
        }
        tmp = tmp->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    register unsigned int hash = 0;
    register int i = 0;
    register long long mul = 1;
    while (word[i] != '\0' && i < 10)
    {
        hash += tolower(word[i]) * mul;
        i++;
        mul *= 52;
    }

    return hash % 400000;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    for (int i = 0; i < N; ++i)
    {
        table[i] = NULL;
    }
    FILE *infile = fopen(dictionary, "r");
    if (!infile)
    {
        printf("Error opening dictionary file!\n");
        return false;
    }
    char word[LENGTH + 1];
    size_t nodesize = sizeof(node);
    while (fscanf(infile, "%s", word) == 1)
    {
        register unsigned int word_hash = hash(word);
        node *n = (node *) malloc(nodesize);
        strcpy(n->word, word);
        n->next = table[word_hash];
        table[word_hash] = n;
        word_count++;
    }
    fclose(infile);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; ++i)
    {
        if (table[i] != NULL)
        {
            unload_node(table[i]);
        }
    }
    return true;
}

bool unload_node(node *n)
{
    if (n->next != NULL)
    {
        unload_node(n->next);
    }
    free(n);
    return true;
}
