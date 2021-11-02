#ifndef __LISTA__
#define __LISTA__

#include <stdlib.h>

// Declaracion del tipo lista
typedef struct _lista_
{
  void *data;
  struct _lista_ *next;
}list;

// Retorna el ultimo elemento
list *last(list *lista)
{
  list *temp = lista;

  if(temp)
    while(temp->next)
      temp = temp->next;

  return temp;
}

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

// Obtener lista en la posicion "posicion"
list *_get(list *lista, size_t posicion)
{
  for(size_t i = 0; lista; i++, lista = lista->next)
    if(i == posicion)
      return lista;

  return NULL;
}

// Obtener dato de un elemento
void *get(list *lista, size_t posicion)
{
  list *ptr = _get(lista, posicion);
  
  if(ptr)
    return ptr->data;

  return NULL;
}

// Inserta un nuevo elemento en la lista
list *insert(list *lista, void *data, size_t posicion)
{
  size_t i = 0;
  list *anterior = NULL;
  list *actual = lista;

  while(i != posicion && actual)
  {
    anterior = actual;
    actual = actual->next;
    i++;
  }

  // Memoria necesaria para el nuevo elemento
  list *nueva = malloc(sizeof(list *));

  if(!nueva)
    return lista;
  
  // Asigna los valores al nuevo elemento
  nueva->data = data;
  nueva->next = actual;

  if(anterior)
    anterior->next = nueva;
  else
    lista = nueva;

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

//funcion de intercambio
void _swap(list *lista, int i, int j)
{
  void *temp;

  temp = get(lista, i);
  _get(lista, i)->data = get(lista, j);
  _get(lista, j)->data = temp;
  
}

// Ordena una lista con el metodo quickssort
void sort(list *lista, int izq, int der, int (*cmp)(void *, void *))
{
  int i, last;

  if(izq >= der)
    return;
  _swap(lista, izq, (izq + der) / 2);
  last = izq;

  for(i = izq + 1; i <= der; i++)
    if(cmp(get(lista, i), get(lista, izq)) < 0)
      _swap(lista, ++last, i);
  
  _swap(lista, izq, last);
  sort(lista, izq, last - 1, cmp);
  sort(lista, last + 1, der, cmp);
}

// Limpia la memoria asignada
void clear(list *lista, void (*freedata)(void *))
{
  list *temp;
  
  while(lista)
  {
    temp = lista->next;
    
    if(freedata)
      freedata(lista->data);
    free(lista);

    lista = temp;
  }
}
#endif
