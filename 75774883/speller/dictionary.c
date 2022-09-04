// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>


#include "dictionary.h"

//define counter
unsigned int word_count = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int pos = hash(word);
    node *tmp = table[pos];

    while (tmp != NULL)
    {
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
        tmp = tmp->next;
    }
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function

    int total = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        total += tolower(word[i]) + 27;
    }
    return total % N;


}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r"); //open dictionary file

    if (file == NULL) //check if file exist
    {
        return false;
    }

    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        //inital new node
        node *new = malloc(sizeof(node));
        if (new == NULL)
        {
            unload();
            return false;
        }
        strcpy(new->word, word); //set word to the word we get
        //get index of bucket
        unsigned int pos = hash(word);
        //point to where that bucket points
        new->next = table[pos];
        //that bucket point to new
        table[pos] = new;

        //up the counter
        word_count++;
    }
    fclose(file);
    return true;

}
// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (word_count > 0)
    {
        return word_count;
    }
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{

    for (int i = 0; i < N; i++)
    {
        node *tmp = table[i];
        while (tmp != NULL)
        {
            node *current = tmp;
            tmp = tmp->next;
            free(current);
        }
    }

    // TODO
    return true;
}
