#include "header.h"

int add_item(List *list, void *data, size_t size) {
  Node *new;

  MALLOC(new, Node, sizeof(Node));
  MALLOC(new->data, void, size);
  new->next = NULL;

  memcpy(new->data, data, size);
  if (list->head == NULL)
    list->head = list->tail = new;
  else {
    list->tail->next = new;
    list->tail = new;
  }

  return OK;
}

void free_list(List *list) {
  Node *i;

  for (i = list->head; i != NULL; i = list->head) {
    list->head = list->head->next;
    free(i->data);
    free(i);
  }
  return;
}

void print_list(List *list) {
  Node *i;
  int count = 0;
  for (i = list->head; i != NULL; i = i->next, count++) {
    printf("%.2f count: %d\n", *(double *)i->data, count);
  }
  return;
}
