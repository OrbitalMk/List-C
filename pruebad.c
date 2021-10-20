#include <stdio.h>
#include <string.h>
#include "listadl.h"

int main()
{
  dlist *p = NULL;

  p = insert(p, "d", 0);
  p = insert(p, "b", 2);
  p = insert(p, "a", 1);
  p = insert(p, "x", 1);
  p = insert(p, "p", 2);
  p = insert(p, "q", 0);

  p = delete(p, len(p) - 2, NULL);
  sort(first(p), 0, len(p) - 1, (int (*)(void *, void *))strcmp);

  for(dlist *temp = p; temp; temp = temp->next)
    printf("%s", temp->data);
  printf("\n");

  clear(p, NULL);
  
  return 0;
}
