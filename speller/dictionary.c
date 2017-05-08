
#include <stdbool.h>

#include <ctype.h>    

#include "dictionary.h"

#include <string.h>

#include <stdio.h>
#include <stdlib.h>



int count = 0;     // gloabal counter

typedef struct node {         // data structure 
    bool is_word;
    struct node *child[27];
    } node;

int index(char c);   // function prototype

void freeNode(node *cNode);

node root = {false,{NULL}};

bool check(const char *word)
{
    node *ptr = &root;
    for (int i=0;i<strlen(word);i++)
    {
        if (ptr->child[index(word[i])] == NULL)  
            return false;                             
        ptr = ptr->child[index(word[i])];       
    }
    if (ptr->is_word)  
        return true;
    else
        return false;
}




bool
load(const char *dictionary)
{
    FILE *file = fopen(dictionary,"r");
    if (file == NULL)
        return false;
    while (!feof(file))
    {
        char word[LENGTH+1] = {};
        fscanf(file,"%s\n",word); // have to use "%s\n" instead of "%s", or the count will be wrong, don't know why.
        count++;    
        node *ptr = &root;
        for (int i=0;i<strlen(word);i++)
        {
            if (ptr->child[index(word[i])] == NULL)  
            {
                node *new = malloc(sizeof(node));   
                *new = (node) {false,{NULL}};       
                ptr->child[index(word[i])] = new;
                ptr = new;
            }
            else
            {
                ptr = ptr->child[index(word[i])];  
            }
         }
         ptr->is_word = true
    }
fclose(file);      
return true;
}




int
index(char c)
{
    int num;
    if (c == '\'')
        return 26;
    else if(isalpha(c))
        c += 32;
    num = c - 'a';
    return num;
}



/*
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */

unsigned int
size(void)
{
    if (count)
        return count;
    else
        return 0;
}


/*
 * Unloads dictionary from memory.  Returns true if successful else false.
 */

bool
unload(void)
{
    for (int i=0;i<27;i++)            // can't just call freeNode(&root),this will cause free(&root),but
    {
        if (root.child[i] != NULL)  // root is not in heap(cause it's not allocated by malloc)
            freeNode(root.child[i]);
    }
    return true;         // can't figure out when to return false...
}

void freeNode(node *cNode)
{
    for (int i=0;i<27;i++)
    {
        if (cNode->child[i] != NULL)   // free node recursively, the method is elegant!
            freeNode(cNode->child[i]); // first free all the child,then free itself.
    }
    free(cNode);
 }
