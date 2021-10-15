#ifndef __LISTA__
#define __LISTA__

#include <stdlib.h>
#include <stdbool.h>

// Declaracion del tipo lista
typedef struct _lista_
{
  void *data;
  struct _lista_ *next;
}list;

// Retorna el tamaño de lista
size_t len(list *lista)
{
  size_t vlen = 0;
  
  while(lista)
  {
    vlen++;
    lista = lista->next;
  }

  return vlen;
}

// Inserta un nuevo elemento en la lista
list *insert(list *lista, void *data, size_t posicion)
{
  list *anterior = NULL;
  list *actual = lista;

  for(size_t i = 0; ; i++)
  {
    if(i == posicion || !actual)
    {
      // Memoria necesaria para el nuevo elemento
      list *nueva = malloc(sizeof(list));

      // Asigna los valores al nuevo elemento
      nueva->data = data;
      nueva->next = actual;

      if(anterior)
	anterior->next = nueva;
      else
	lista = nueva;

      break;
    }

    anterior = actual;
    actual = actual->next;
  }

  return lista;
}

// Elimina un elemento en la lista
list *delete(list *lista, size_t posicion,  void (*freedata)(void *))
{
  list *anterior = NULL;
  list *actual = lista;

  for(size_t i = 0; actual; i++)
  {
    if(i == posicion)
    {
      if(anterior)
	anterior->next = actual->next;
      else
	lista = actual->next;
      
      if(freedata)
	freedata(actual->data);
      free(actual);

      break;
    }

    anterior = actual;
    actual = actual->next;
  }

  return lista;
}

// Limpia la memoria dinamica asignada
void clear(list *lista, void (*freedata)(void *))
{
  list *temp;
  
  for(; lista; lista = temp)
  {
    temp = lista->next;
    
    if(freedata)
      freedata(lista->data);
    free(lista);
  }
}
#endif
