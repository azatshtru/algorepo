#include "miniqutils.h"

#ifndef LINKED_LIST
#define LINKED_LIST

typedef struct linked_list_node {
  struct linked_list_node* prev;
  struct linked_list_node* next;
} llnode;

/* based on linux kernel implementation of linked list */

#define llnode_container(type, ptr, member_name) ((type*)(ptr - (unsigned long)(&(((type*)0)->member_name))))

void llnode_new(llnode* head);
void ll_insert(llnode* a, llnode* x, llnode* b);
void ll_insert_before(llnode* head, llnode* x);
void ll_insert_after(llnode* head, llnode* x);
void llnode_free(llnode* node);

#endif
