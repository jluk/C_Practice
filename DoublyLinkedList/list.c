/**
 * CS 2110 - Spring 2014 - Homework #12
 * Edited by: Brandon Whitehead, Andrew Wilder
 *
 * list.c: Complete the functions!
 * By: Justin Luk
 */

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

/* The node struct.  Has a prev pointer, next pointer, and data. */
/* DO NOT DEFINE ANYTHING OTHER THAN WHAT'S GIVEN OR YOU WILL GET A ZERO*/
/* Design consideration only this file should know about nodes */
/* Only this file should be manipulating nodes */
/* DO NOT TOUCH THIS DECLARATION DO NOT PUT IT IN OTHER FILES */
typedef struct lnode
{
  struct lnode* prev; /* Pointer to previous node */
  struct lnode* next; /* Pointer to next node */
  void* data; /* User data */
} node;


/* Do not create any global variables here. Your linked list library should obviously work for multiple linked lists */
// This function is declared as static since you should only be calling this inside this file.
static node* create_node(void* data);

/** create_node
  *
  * Helper function that creates a node by allocating memory for it on the heap.
  * Be sure to set its pointers to NULL.
  *
  * @param data a void pointer to data the user wants to store in the list
  * @return a node
  */
static node* create_node(void* data)
{
    /// @todo Implement changing the return value!
    node* newNode = malloc(sizeof(node));
    if (!newNode){
      return NULL;
    }
    newNode->prev = NULL;
    newNode->next = NULL;
    newNode->data = data;
    return newNode;
}

/** create_list
  *
  * Creates a list by allocating memory for it on the heap.
  * Be sure to initialize size to zero and head/tail to NULL.
  *
  * @return an empty linked list
  */
list* create_list(void)
{
    /// @todo Implement changing the return value!
    list* newList = malloc(sizeof(list));
    if (!newList){
      return NULL;
    }
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;
    return newList;
}

/** push_front
  *
  * Adds the data to the front of the linked list
  *
  * @param llist a pointer to the list.
  * @param data pointer to data the user wants to store in the list.
  */
void push_front(list* llist, void* data)
{
    /// @todo Implement
    node* llnode = create_node(data);
    llnode->data = data;
    llnode->next = llist->head;
    llist->head = llnode;
    if (llist->tail == NULL) {
      llist->tail = llnode;
    } else {
      llnode->next->prev = llnode;
    }
    llist->size++;
}

/** push_back
  *
  * Adds the data to the back/end of the linked list
  *
  * @param llist a pointer to the list.
  * @param data pointer to data the user wants to store in the list.
  */
void push_back(list* llist, void* data)
{
    /// @todo Implement
    node* llnode = create_node(data);
    llnode->data = data;
    llnode->prev = llist->tail;
    llist->tail = llnode;
    if (llist->head == NULL){
      llist->head = llnode;
    } else {
      llnode->prev->next = llist->tail;
    }
    llist->size++;
}

/** front
  *
  * Gets the data at the front of the linked list
  * If the list is empty return NULL.
  *
  * @param llist a pointer to the list
  * @return The data at the first node in the linked list or NULL.
  */
void* front(list* llist)
{
    /// @todo Implement changing the return value!
    /// @note you are returning the HEAD's DATA not the head node. Remember the user should never deal with the linked list nodes.
  if (llist->head == NULL) {
    return NULL;
  } else {
    node* llnode = llist->head;
    return llnode->data;
  }
}

/** back
  *
  * Gets the data at the "end" of the linked list
  * If the list is empty return NULL.
  *
  * @param llist a pointer to the list
  * @return The data at the last node in the linked list or NULL.
  */
void* back(list* llist)
{
    /// @todo Implement changing the return value!
  if (llist->head == NULL) {
    return NULL;
  } else {
    node* llnode = llist->tail;
    return llnode->data;
  }
}

/** remove_front
  *
  * Removes the node at the front of the linked list
  *
  * @warning Note the data the node is pointing to is also freed. 
  If you have any pointers to this node's data it will be freed!
  *
  * @param llist a pointer to the list.
  * @param free_func pointer to a function that is responsible 
  for freeing the node's data.
  * @return -1 if the remove failed (which is only there are no 
  elements) 0 if the remove succeeded.
  */
int remove_front(list* llist, list_op free_func)
{
    /// @todo Implement
    /// @note remember to also free the node itself
    /// @note free_func is a function that is responsible for freeing the node's data only.
    if (llist->head == NULL){
      return -1;
    } else if (llist->head == llist->tail){ //edge case for one node left
      node* llnode = llist->head;
      free_func(llnode->data);
      free(llnode);
      llist->head = NULL;
      llist->tail = NULL;
      llist->size = 0;
      return 0;
    } else { //normal case where you remove head and reassign head's next as new head
      node* llnode = llist->head;
      free_func(llnode->data);
      llist->head = llnode->next;
      llnode->next->prev = NULL;
      free(llnode);
      llist->size--;
      return 0;
    }
}

/** remove_back
  *
  * Removes the node at the back of the linked list
  *
  * @warning Note the data the node is pointing to is also freed. If you have any pointers to this node's data it will be freed!
  *
  * @param llist a pointer to the list.
  * @param free_func pointer to a function that is responsible for freeing the node's data.
  * @return -1 if the remove failed 0 if the remove succeeded.
  */
int remove_back(list* llist, list_op free_func)
{
    /// @todo Implement
    /// @note Remember to also free the node itself
    /// @note free_func is a function that is responsible for freeing the node's data only.
    if (llist->head == NULL){
      return -1;
    } else if (llist->head == llist->tail){ //edge case for one node left
      node* llnode = llist->head;
      free_func(llnode->data);
      free(llnode);
      llist->head = NULL;
      llist->tail = NULL;
      llist->size = 0;
      return 0;
    } else { //normal case where you remove head and reassign head's next as new head
      node* llnode = llist->tail;
      free_func(llnode->data);
      llist->tail = llnode->prev;
      llnode->prev->next = NULL;
      free(llnode);
      llist->size--;
      return 0;
    }}

/** copy_list
  *
  * Create a new list structure, new nodes, and new copies of the data by using
  * the copy function. Its implementation for any test structure must copy
  * EVERYTHING!
  *
  * @param llist A pointer to the linked list to make a copy of
  * @param copy_func A function pointer to a function that makes a copy of the
  *        data that's being used in this linked list, allocating space for
  *        every part of that data on the heap. This is some function you must
  *        write yourself for testing, tailored specifically to whatever context
  *        you're using the linked list for in your test.
  * @return The linked list created by copying the old one
  */
list* copy_list(list* llist, list_cpy copy_func)
{
	/// @todo implement
  list* copyList = create_list();
  node* llnode = llist->head;
  while (llnode != NULL)
  {
    push_back(copyList,  copy_func(llnode->data));
    llnode = llnode->next;
  }
  return copyList;
}

/** size
  *
  * Gets the size of the linked list
  *
  * @param llist a pointer to the list
  * @return The size of the linked list
  */
int size(list* llist)
{
    ///@note simply return the size of the linked list.  Its that easy!
    return llist->size;
}

/** remove_if
  *
  * Removes all nodes whose data when passed into the predicate function returns true
  *
  * @param llist a pointer to the list
  * @param pred_func a pointer to a function that when it returns true it will remove the element from the list and do nothing otherwise @see list_pred.
  * @param free_func a pointer to a function that is responsible for freeing the node's data
  * @return the number of nodes that were removed.
  */
int remove_if(list* llist, list_pred pred_func, list_op free_func)
{
    /// @todo Implement changing the return value!
    /// @note remember to also free all nodes you remove.
    /// @note be sure to call pred_func on the NODES DATA to check if the node needs to be removed.
    /// @note free_func is a function that is responsible for freeing the node's data only.
   
    //CASE 0: Empty List
    if (llist->head == NULL){
      return 0;

    } else if (llist->head == llist->tail){
      //CASE 1: one node in llist
      if (pred_func(llist->head->data)){
        free_func(llist->head->data);
        free(llist->head);
        llist->head = NULL;
        llist->tail = NULL;
        llist->size = 0;
        return 1;
      }
      return 0;

    } else {
      //CASE 2: Regular case
      int removed = 0;
      node* llnode = llist->head;
      while (llnode != NULL) {
        if (pred_func(llnode->data)){
          if (llnode->prev == NULL){
            llist->head = llnode->next;
            llist->head->prev = NULL;
            free_func(llnode->data);
            free(llnode);
            llnode = llist->head;
            llist->size--;
            removed++;
          } else if (llnode->next == NULL){
            llist->tail = llnode->prev;
            llist->tail->next = NULL;
            free_func(llnode->data);
            free(llnode);
            llnode = NULL; //NEED TO ERASE POINTER AFTER USING AVOID REACHABLE BLOCK
            llist->size--;
            removed++;
          } else {
            node* nodeNext = llnode->next;
            llnode->next->prev = llnode->prev;
            llnode->prev->next = llnode->next;
            free_func(llnode->data);
            free(llnode);
            llnode = nodeNext;
            llist->size--;
            removed++;
          }
        } else {
          llnode = llnode->next;
        }
      }
      return removed;
    }
    return 0;
} 

/** is_empty
  *
  * Checks to see if the list is empty.
  *
  * @param llist a pointer to the list
  * @return 1 if the list is indeed empty 0 otherwise.
  */
int is_empty(list* llist)
{
    ///@note an empty list by the way we want you to implement it has a size of zero and head points to NULL.
  if ((llist->size == 0) && (llist->head == NULL)) {
    return 1;
  } else {
    return 0;
  }
}

/** empty_list
  *
  * Empties the list after this is called the list should be empty.
  *
  * @param llist a pointer to a linked list.
  * @param free_func function used to free the node's data.
  */
void empty_list(list* llist, list_op free_func)
{
    /// @todo Implement
    /// @note Free all of the nodes not the linked list itself.
    /// @note do not free llist.
    if (llist == NULL) {
      return;
    }

    node* llnode = llist->head;
    node* temp;
    //traverse the list and free the data and memory allocated
    while (llnode != NULL)
    {
      temp = llnode;
      free_func(llnode->data);
      llnode = llnode->next;
      free(temp);
    }
    //reset head,tail,size
    llist->head = NULL;
    llist->tail = NULL;
    llist->size = 0;
    return;
}

/** traverse
  *
  * Traverses the linked list calling a function on each node's data.
  *
  * @param llist a pointer to a linked list.
  * @param do_func a function that does something to each node's data.
  */
void traverse(list* llist, list_op do_func)
{
    /// @todo Implement
    if (llist == NULL) {
      return;
    }
    //create pointer to traverse the llist from the head
    node* llnode = llist->head;
    //traverse the list and complete function on data
    while (llnode != NULL) {
      do_func(llnode->data);
      llnode = llnode->next;
    }
}
