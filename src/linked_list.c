#include "../headers/linked_list.h"

void llnode_new(llnode* head) {
  head->next = head;
  head->prev = head;
}

void ll_insert(llnode* a, llnode* x, llnode* b) {
  a->next = x;
  x->prev = a;
  x->next = b;
  b->prev = x;
}

void ll_insert_before(llnode* head, llnode* x) {
  ll_insert(head->prev, x, head);
}

void ll_insert_after(llnode* head, llnode* x) {
  ll_insert(head, x, head->next);
}

void llnode_free(llnode* node) {
  node->prev->next = node->next;
  node->next->prev = node->prev;
}
