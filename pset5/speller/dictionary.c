// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"
#include <ctype.h>

#define SIZE 26

typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// hashtable with 26 buckets -> one bucket for each letter in ASCII
node *hashtable[SIZE];

//global var to track dictionary size
int dictionarySize = 0;

// hash function
int hashFunction (const char* word) {
    int hash = tolower(word[0]) - 97;
    return hash;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    // open dictionary file
    FILE *file = fopen(dictionary, "r");

    // declare empty variable for word
    char word[LENGTH + 1];

    // scan dictionary word by word
    while (fscanf(file, "%s", word) != EOF) {

        // increment dictionary size
        dictionarySize++;

        // malloc a node for each new word
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            unload();
            return false;
        }

        // copy word into node
        strcpy(new_node->word, word);

        // find index to insert into hashtable
        int index = hashFunction(word);

        // add word into hashtable at index
        if(hashtable[index] == NULL){
            hashtable[index] = new_node;
            new_node->next = NULL;
        } else {
            new_node->next = hashtable[index];
            hashtable[index] = new_node;
        }
    }

    // close file after creating dictionary
    fclose(file);
    return true;
}

// Returns true if word is in dictionary else false
bool check(const char* word)
{
    // TODO
    //temp variable for word
    char temp[LENGTH + 1];

    //convert word to lowercase
    for(int i = 0; i < strlen(word); i++){
        temp[i] = tolower(word[i]);
    }
    // add NULL to the end of word
    temp[strlen(word)] = '\0';

    //where is head? -> head is at word's hash index
    int index = hashFunction(word);

    // if hastable does not have anything at index return false
    if(hashtable[index] == NULL){
        return false;
    }

    // cursor to compare words
    node *cursor = hashtable[index];

    // if hashtable has something at index
    // iterate through words and compare them
    while(cursor != NULL){
        if (strcmp(temp, cursor->word) == 0) {
            return true;
        }
        cursor = cursor->next;
    }
    // no more words at index? -> word not found
    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if(dictionarySize > 0){
        return dictionarySize;
    } else {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    // loop through hashtable
    for (int i = 0; i < SIZE; i++){
        node *cursor = hashtable[i];

        // if there is something at index -> free it
        while (cursor != NULL){
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }

    return true;
}
