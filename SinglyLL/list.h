#ifndef LIST_H
#define LIST_H

typedef struct lnode {
	struct lnode* next;
	int data;
} NODE;

typedef struct llist {
	NODE* head;
	NODE* tail;
	int size;
} LIST;

LIST* create_list();
void list_add(LIST* llist, int data);
int list_get(LIST* llist, int index);
void list_del(LIST* llist, int index);
NODE* create_node(int data);
void print_node(NODE* node);

#endif
