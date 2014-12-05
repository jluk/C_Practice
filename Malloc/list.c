#include <stdlib.h>
#include "./list.h"
#include "my_malloc.h"

//Justin Luk

static NODE* create_node(int data);

static NODE* create_node(int data)
{
    NODE* newNode = my_malloc(sizeof(NODE));
    if (!newNode){
      return NULL;
    }
    newNode->prev = NULL;
    newNode->next = NULL;
    newNode->data = data;
    return newNode;
}

LIST* create_list(void)
{
    LIST* newList = my_malloc(sizeof(LIST));
    if (!newList){
      return NULL;
    }
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;
    return newList;
}

/**
 * pushFront
 * Takes in ptr to a list and data to add
 * Should add new node containing the data to the head of the list, and increment size
 */
void pushFront(LIST *list, int data)
{
	NODE* llnode = create_node(data);
    llnode->data = data;
    llnode->next = list->head;
    list->head = llnode;
    if (list->tail == NULL) {
      list->tail = llnode;
    } else {
      llnode->next->prev = llnode;
    }
    list->size++;
}

/**
 * pushFront
 * Takes in ptr to a list and data to add
 * Should add new node containing the data to the tail of the list, and increment size
 */
void pushBack(LIST *list, int data)
{
    NODE* llnode = create_node(data);
    llnode->data = data;
    llnode->prev = list->tail;
    list->tail = llnode;
    if (list->head == NULL){
      list->head = llnode;
    } else {
      llnode->prev->next = list->tail;
    }
    list->size++;
}

/**
 * popFront
 * Takes in ptr to a list
 * Remove and free node at the front of the list, and decrement size
 * Return the value of that node
 * Return 0 if the size of the list is 0
 */
int popFront(LIST *list)
{
    if (list->head == NULL){ //size is 0
      return 0;
    } else if (list->head == list->tail){ //edge case for one node left
      NODE* llnode = list->head;
      int temp = llnode->data;
      my_free(llnode);
      list->head = NULL;
      list->tail = NULL;
      list->size = 0;
      return temp;
    } else { //normal case where you remove head and reassign head's next as new head
      NODE* llnode = list->head;
      int temp = llnode->data;
      //move head, unlink old head
      list->head = llnode->next;
      llnode->next->prev = NULL;
      //free node, update size, return removed node data
      my_free(llnode);
      list->size--;
      return temp;
    }
}

/**
 * popBack
 * Takes in ptr to a list
 * Remove and free node at the back of the list, and decrement size
 * Return the value of that node
 * Return 0 if the size of the list is 0
 */
int popBack(LIST *list)
{
    if (list->head == NULL){ //size is 0
      return 0;
    } else if (list->head == list->tail){ //edge case for one node left
      NODE* llnode = list->head;
      int temp = llnode->data;
      my_free(llnode);
      list->head = NULL;
      list->tail = NULL;
      list->size = 0;
      return temp;
    } else { //normal case where you remove head and reassign head's next as new head
      NODE* llnode = list->tail;
      int temp = llnode->data;
      //move tail ptr, delink node
      list->tail = llnode->prev;
      llnode->prev->next = NULL;
      my_free(llnode);
      list->size--;
      return temp;
    }
}


