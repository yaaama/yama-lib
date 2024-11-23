#include <assert.h>
#include <stdlib.h>

#include "common.h"
#include "linkedlist.h"

/* Create a new list object. */
list *list_create(void) {
  list *list = malloc(sizeof *list);
  /* If malloc fails just return NULL */
  if (list == NULL) {
    return NULL;
  }

  list->head = NULL;
  list->size = 0;
  return list;
}

u32 list_size(list *list) {

  if (list == NULL) {
    return 0;
  }

  return list->size;
}

list_node *list_create_node(void *data) {
  assert(data != NULL && "data is NULL");

  list_node *node_ptr = malloc(sizeof(list_node));

  node_ptr->data = data;
  node_ptr->next = NULL;

  return node_ptr;
}

void list_destroy_node(list_node *node) {
  assert(node != NULL);

  free(node->data);
  node->next = NULL;
  free(node);
}

void list_insert(list *list, void *data) {
  assert(list != NULL && "list is NULL!");
  assert(data != NULL && "data is NULL!");

  list_node *node = list_create_node(data);
  if (node == NULL) {
    /* node is NULL so something bad happened... */
    return;
  }

  list->size += 1;
  list_node *curr_head = list->head;

  /* If list is empty, just assign list head to new node and return */
  if (curr_head == NULL) {
    curr_head = node;
    return;
  }

  /* If the list is not empty */
  curr_head->next = node;
}

/* Deallocates and destroys the list */
void list_destroy(list *list) {
  assert(list);

  list_node *curr = list->head;
  list_node *next = curr->next;

  while (curr != NULL) {
    free(curr->data);
    free(curr);
    curr = next;
    next = curr->next;
  }

  free(list);
}

/* Returns the list node at the head */
list_node *list_head(list *list) { return list->head->data; }

/* Removes the head of a list object */
void list_remove_head(list *list) {
  assert(list && "List is NULL.");

  if (list->size <= 0) {
    /* That means we have an empty list... */
    return;
  }

  list_node *node = list->head;
  list_node *next = node->next;
  list->head = next;

  if (node) {
    free(node->data);
    free(node);
  }

  list->size -= 1;
}

/* Function to run an operation on each of the list elements */
void list_foreach(list *list, void (*operation)(void *func)) {

  /* u32 count = 0; */
  list_node *curr = list->head;

  while (curr) {
    /* count++; */
    operation(curr->data);
    curr = curr->next;
  }
}
