/*

NOTE: These are the contents of the dictionary.c file in the pset itself.
Here it's called speller.c as the pset itself is called "Speller" but the
dictionary.c is the only file you need to edit.

*/

// Implements a dictionary's functionality
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <strings.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
// Will guess large enough number as my hashing will be sum of letter asci values
const unsigned int N = 30000;

// Hash table
node *table[N];

// Dictionary size (to be used later by the check_size function)
int dictionary_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    /*
        Get the index number by checking the hash value.
        Then try getting the list in the hash table at that index.
        Loop over linked list and compare words to see if it's there.
    */

    // Get index number
    int index = hash(word);

    // Get linked list at that index
    node *n = table[index];

    // While current iteration is not NULL, compare words and exit if match is found
    while (n != NULL)
    {
        if (strcasecmp(n->word, word) == 0)
        {
            return true;
        }

        // If match not found, set n to next node
        n = n->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // This one will sum numerical values of all characters in the string

    // To keep track of sum
    int sum = 0;
    // To get the lenght of the current word
    int len = strlen(word);

    // For each letter check asci value and add to the sum variable
    for (int i = 0; i < len; i++)
    {
        int value = tolower(word[i]);
        sum += value;
    }

    // printf("%d\n", sum % N);
    // Make sure returned value is not bigger than N
    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open the file with fopen
    FILE *dictionary_file = fopen(dictionary, "r");

    // If null on opening, exit
    if (dictionary == NULL)
    {
        printf("Not able to read %s\n", dictionary);
        return false;
    }

    /*
        Read words from file until fscan returns != 1 (each string returns 1, then when no string we are at the end)
        Then allocate memory to node n for each word but check for memmory issues here
        Then copy current word to the node
        Then get index number by running the node in the hash function
        Then append node to the hash table at appropriate index
        Then close opened file
    */

    // Array for new word
    char new_word[LENGTH + 1];

    while (fscanf(dictionary_file, "%s", new_word) == 1)
    {
        // Make node for current word and allocate memory
        node *n = malloc(sizeof(node));

        // If null, exit
        if (n == NULL)
        {
            printf("Something with allocating memory failed");
            return false;
        }

        // Copy current word to the node
        strcpy(n->word, new_word);

        // Get intended index using hash function
        int index = hash(new_word);

        // Add node to the hash table but first, set the next pointer to the current list's top item,
        // then update top item the be the current node. That way we do not lose the current top item
        n->next = table[index];
        table[index] = n;

        // Increment the dictionary size counter
        dictionary_size += 1;
    }

    // Close the file
    fclose(dictionary_file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    // Here we are returning the dictionary size counter
    return dictionary_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // For each bucket in the hash table go over each node and free it

    for (int i = 0; i < N; i++)
    {
        // Current node
        node *n = table[i];

        while (table[i] != NULL)
        {
            // Create temporary node to store the next node's address so it's preserved after the freeing procedure
            node *temp = table[i]->next;

            // Free current node
            free(table[i]);

            // Set table[i] to the preserved next node address from the temp variable
            table[i] = temp;
        }
    }
    return true;
}
