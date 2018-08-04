#include "header.h"


int add_item(List *list, void *data, size_t datasize) {
  /*
  Description: Add general item to a list.
  Input: List pointer, pointer to a data struct, size of data.
  Output: OK if mallocs succeeded and !OK else.
  */
  Node *new;

  MALLOC(new, Node, sizeof(Node));
  MALLOC(new->data, void, datasize);
  
  new->next = NULL;
  memcpy(new->data, data, datasize);
  
  if (list->head == NULL)
    list->head = list->tail = new;
  else {
    list->tail->next = new;
    list->tail = new;
  }

  return OK;
}

void free_list(List *list) {
  /*
  Description: Delete given list.
  Input: List pointer.
  Output: void.
  */
  Node *i;

  for (i = list->head; i != NULL; i = list->head) {
    list->head = list->head->next;
    free(i->data);
    free(i);
  }
  return;
}

boolean is_empty_list(List *list) {
  /*
  Description: Check if a given list is empty.
  Input: List pointer.
  Output: True or False.
  */
  return (list->head == NULL);
}

void print_list(List *list) {
  /* @temp
  Description: Print a given list.
  Input: List pointer.
  Output: void.
  */

  Node *i;
  int count = 0;
  for (i = list->head; i != NULL; i = i->next, count++) {
    printf("%.2f count: %d\n", *(double *)i->data, count);
  }
  return;
}

void walk_list(List *list, void (*action)(void *)) {
  Node *i;
  for (i = list->head; i != NULL ; i = i->next) {
    (*action)(i->data);
  }
  return;
}
