#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Here we are going to write some functions to support a linked list that stores
 * Person data (name, age)
 * Justin Luk
 */
typedef struct person_t
{
    char* name;
    int age;
} Person;

/* Example functions given to you. If you want to truly grasp these concepts, try
 * writing your own structs and functions as well!
 */

// Create a new Person
Person* create_person(const char* name, int age)
{
    Person* p = (Person*) malloc(sizeof(Person));
    p->name = strdup(name);
    p->age = age;
    return p;
}

// Make a deep copy of a Person
void* copy_person(const void* data)
{
    Person *p = (Person*) data;
    return create_person(p->name, p->age);
}

// Print a Person
void print_person(void* data)
{
    Person *p = (Person*) data;
    printf("%s, %d\n", p->name, p->age);
}

// Free a Person
void free_person(void* data)
{
    Person *p = (Person*) data;
    // free any malloc'd pointers contained in the Person struct
    free(p->name);
    free(p);
}

// Return 1 if the person's name is 8+ characters long
int long_name(const void *data)
{
	Person *p = (Person*) data;
	return strlen(p->name) > 7;
}

/* This main function does a little testing
   Like all good CS Majors you should test
   your code here. There is no substitute for testing
   and you should be sure to test for all edge cases
   e.g., calling remove_front on an empty list.
*/
int main(void)
{
	/* Now to make use of all of this stuff */
	list* llist = create_list();

  	/* What does an empty list contain?  Lets use our handy traversal function */
  	printf("TEST CASE 1\nAn Empty list should print nothing here:\n");
  	traverse(llist, print_person);
	printf("\n");

 	/* Lets add a person and then print */
 	push_front(llist, create_person("Andrew", 24));
 	printf("TEST CASE 2\nA List with one person should print that person:\n");
 	traverse(llist, print_person);
 	printf("\n");

 	/* Lets remove that person and then print */
 	remove_front(llist, free_person);
 	printf("TEST CASE 3\nAnother Empty list should print nothing here:\n");
 	traverse(llist, print_person);
 	printf("\n");

 	/* Lets add two people and then print */
 	push_front(llist, create_person("Nick", 22));
 	push_front(llist, create_person("Randal", 21));
 	printf("TEST CASE 4\nA List with two people should print those two people:\n");
 	traverse(llist, print_person);
 	printf("\n");

	/* Lets copy this list */
	list* llist2 = copy_list(llist, copy_person);
	printf("TEST CASE 5\nA copied list should print out the same two people:\n");
 	traverse(llist2, print_person);
 	printf("\n");

  	/* Lets kill the list */
  	empty_list(llist, free_person);
 	printf("TEST CASE 6\nAfter freeing all nodes the list should be empty:\n");
 	traverse(llist, print_person);
	printf("\n");

	/* Let's make a list of people, and remove certain ones! */
	/* Should remove anyone whose name is 8+ characters long */
	push_front(llist, create_person("Josephine", 27));
	push_front(llist, create_person("Dave", 34));
	push_front(llist, create_person("Benjamin", 23));
	push_front(llist, create_person("Lisa", 41));
	push_front(llist, create_person("Maximilian", 24));
	remove_if(llist, long_name, free_person);
	printf("TEST CASE 7\nShould only print 2 people with short names:\n");
	traverse(llist, print_person);
  printf("\n");

 	/* YOU ARE REQUIRED TO MAKE MORE TEST CASES THAN THE ONES PROVIDED HERE */
 	/* You will get points off if you do not you should at least test each function here */

//  /* Creating */
// list* create_list(void); USED IN LIST.C
// list* copy_list(list* llist, list_cpy copy_func); USED IN LIST.C

// /* Adding */
// void push_front(list* llist, void* data); TESTED
// void push_back(list* llist, void* data); TESTED

// /* Removing */
// int remove_front(list* llist, list_op free_func); TESTED
// int remove_back(list* llist, list_op free_func); TESTED
// int remove_if(list* llist, list_pred pred_func, list_op free_func); TESTED

// /* Querying List */
// void* front(list* llist); TESTED
// void* back(list* llist); TESTED
// int is_empty(list* llist); TESTED
// int size(list* llist); TESTED

// /* Freeing */
// void empty_list(list* llist, list_op free_func); TESTED

// /* Traversal */
// void traverse(list* llist, list_op do_func); TESTED


  empty_list(llist,free_person);

  /* Let's test if push_back works correctly */
  push_back(llist, create_person("Dan", 20));
  push_back(llist, create_person("Stan", 20));
  push_back(llist, create_person("Plan", 20));
  push_back(llist, create_person("Crayon", 20));
  printf("TEST CASE 8 (push_back)\nShould print Dan, Stan, Plan, Crayon:\n");
  traverse(llist,print_person);
  printf("\n");

  /* Let's test remove_front */
  remove_front(llist,free_person);
  printf("TEST CASE 9 (remove_front)\nBye Bye Dan:\n");
  traverse(llist,print_person);
  printf("\n");

  /* Now remove back */
  remove_back(llist,free_person);
  printf("TEST CASE 10 (remove_back)\nBye Bye Crayon:\n");
  traverse(llist,print_person);
  printf("\n");

  /* Double check copy_list */
  list* dup = copy_list(llist, copy_person);
  printf("TEST CASE 11 (copy_list)\nShould reprint Stan, Plan, Size is: 2:\n");
  traverse(dup,print_person);
  printf("Size is: %d\n", size(dup));
  printf("\n");

  /* Double check is_empty and empty_list (even though we used it already) and size */
  if (!is_empty(dup)){
    printf("TEST CASE 12 (is_empty)\nYou want to see this!\n");
    empty_list(dup,free_person);
  }
  printf("\n");

  printf("TEST CASE 13 (empty_list)\nYou want a size of 0!\n");
  printf("Size is: %d\n", size(dup));
  printf("\n");

  /* Test certain cases of remove_if as well as front, back */
  empty_list(llist,free_person);
  push_front(llist, create_person("Dave", 34));
  push_front(llist, create_person("Lisa", 41));
  push_front(llist, create_person("Maximilian", 24));
  push_front(llist, create_person("Benjamin", 23));
  push_front(llist, create_person("Josephine", 27));
  push_back(llist, create_person("Becky", 19));
  remove_back(llist, free_person);
  push_back(llist, create_person("Jessie", 20));

  /* Print out the sample list */
  printf("This is the sample list printed out \n");
  traverse(llist,print_person);
  printf("\n");

  /* Test front and back methods */
  Person* f = front(llist);
  Person* b = back(llist);
  printf("TEST CASE 14 (front)\nShould only print Josephine: %s\n", f->name);
  printf("TEST CASE 15 (back)\nShould only print Jessie: %s\n", b->name);
  printf("\n");

  /* Check remove_if still works if head is repeatedly removed */
  remove_if(llist, long_name, free_person);
  printf("TEST CASE 16 (repeated head node)\nShould only print 3 people with short names:\n");
  traverse(llist, print_person);  
  printf("\n");

  /* Check remove_if to remove head, tail, regular case*/
  empty_list(llist,free_person);
  push_front(llist, create_person("Abbadabba", 34));
  push_front(llist, create_person("Lisa", 41));
  push_front(llist, create_person("Maximilian", 24));
  push_back(llist, create_person("Benjamin", 23));
  push_front(llist, create_person("Josephine", 27));
  push_back(llist, create_person("Becky", 19));
  remove_back(llist, free_person);
  push_back(llist, create_person("Jessieventura", 20));
  remove_if(llist, long_name, free_person);
  printf("TEST CASE 17 \nShould only print 1 short names: \n");
  traverse(llist,print_person);
  printf("\n");

  /* check remove_if when only one node left */
  push_front(llist, create_person("Longnamemisterman", 100));
  remove_back(llist, free_person);
  remove_if(llist, long_name, free_person);
  printf("TEST CASE 18 \nShould print no names removing last node: \n");
  traverse(llist,print_person);
  printf("\n");

  /* Test head and tail still intact after remove_if */
  push_back(llist, create_person("Benjamin", 23));
  push_front(llist, create_person("Maximilian", 24));
  printf("TEST CASE 19 \nShould print two names, Maximilian and Benjamin: \n");
  traverse(llist,print_person);
  printf("\n");

 	/* Testing over clean up*/
	empty_list(llist, free_person);
 	free(llist);
	empty_list(llist2, free_person);
	free(llist2);
  empty_list(dup, free_person);
  free(dup);

  	return 0;
}

