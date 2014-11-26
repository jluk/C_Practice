#include "list.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * This function will create a new list and return a pointer to that list.
 */
LIST* create_list()
{
	return NULL;
}

/**
 * This function will add the given data to the linked list (llist)
 */
void list_add(LIST* llist, int data)
{
	return;
}

/**
 * This function will return the data located at the given index in the list (llist)
 * i.e. for a list of 12,9,8,4,1    list_get(llist, 2) would give me the value 8
 */
int list_get(LIST* llist, int index)
{
	return 0;
}
/**
 * This function will remove the data located at the given index in the list (llist)
 * just like the above function, but removes the node instead
 * remember to free the node and re-arrange your pointers as needed!
 */
void list_del(LIST* llist, int index)
{
	return;
}

/**
 * This function will create a node from the given data and return a pointer to that node.
 */
NODE* create_node(int data)
{
	return NULL;
}

/** 
 * This function will print a node out in a nicely formatted way. Do whatever you want, just try to make it easy to read.
 * Note you will be using this to traverse over the list and print the nodes.
 */
void print_node(NODE* node)
{
	return;
}
