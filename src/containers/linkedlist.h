#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "common.h"
#include <stddef.h>

typedef struct list_node list_node;

struct list_node {
  void *data;
  list_node *next;
};

typedef struct {
  list_node *head;
  u32 size;
} list;

list *list_create(void);

u32 list_size(list *list);

void list_destroy(list *list);
void list_insert(list *list, void *data);

list_node *list_head(list *list);
list_node *list_tail(list *list);


void list_foreach(list *list, void (*operation)(void *func));

#endif // LINKEDLIST_H_
