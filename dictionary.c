/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dictionary.h"

 //initialize the size
 int volume = 0;

 //define the node struct
 typedef struct node
 {
 	char word[LENGTH +1];
 	struct node* next;
 } node;

 node* hashtable[27] = {NULL};


/**
 *Returns hash
 */
 int hash ( char* word)
 {
 	char fletter = toupper(word[0]);
 	if (fletter >= 'A' && fletter <= 'Z')
 	{
 		return fletter - 'A';
 	}
 	else 
 	{
 		return 26;
 	}
 }	 

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
	int len = strlen(word);

	//copy the lowercased version of the wrd
	char ref_word[len];
    for (int i = 0; i < len; i++)
    {
    	ref_word[i] = tolower(word[i]);
    }
    ref_word[len] = '\0';

    //calculate the hash and check the bucket
    int index = hash(ref_word);
    if (hashtable[index] == NULL)
    {
    	return false;
    }
    else
    {
    	node* crawler = hashtable[index];
    	if (strcmp(hashtable[index]->word,ref_word)==0)
    	{
    		return true;
    	}
    	while (crawler -> next != NULL)
    	{
    		if (strcmp(crawler->word,ref_word)==0)
    		{
    			return true;
    		}
    		crawler = crawler -> next;
    	}
    	
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    //initialize new node
    node* new_node = NULL;
    
    //open file
    FILE* file = fopen(dictionary,"r");
    if (file == NULL)
    {
    	return false;
    }

    //until end of the file
    while(feof(file) == 0)
    {
    	//make a new node for each new word
    	new_node = malloc(sizeof(node));

    	//read from file
    	fscanf(file, "%s" , new_node -> word);
    	new_node -> next = NULL;

    	//find the hash index using the hash function
    	int index = hash(new_node -> word);

    	//assign the new node to the linked list
    	if (hashtable[index] == NULL)
    	{
    		hashtable[index] = new_node;
    		volume++;
    	}
    	else
    	{
    		node* crawler = hashtable[index];
    		while (crawler -> next != NULL)
    		{
    			crawler = crawler->next;
    		}
    		crawler -> next = new_node;
    		volume++;
    	}

    	
    }
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return volume-1;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    for (int i = 0; i<27;i++)
    {
    	node* cursor = hashtable[i];
    	while (cursor!=NULL)
    	{
    		node* temp = cursor;
    		cursor = cursor->next;
    		free(temp);
    	}
    }
    return true;
}
