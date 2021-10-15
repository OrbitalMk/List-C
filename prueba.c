#include <stdio.h>
#include "lista.h"

int main()
{
  list *p = NULL;

  p = insert(p, "!", 0);
  p = insert(p, "world", 0);
  p = insert(p, " ", 0);
  p = insert(p, "Hello", 0);

  p = delete(p, len(p) - 1, NULL);

  for(list *temp = p; temp; temp = temp->next)
    printf("%s", temp->data);
  printf("\n");

  clear(p, NULL);
  
  return 0;
}
