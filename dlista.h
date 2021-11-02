/* Double linked */
#ifndef __DLISTA__
#define __DLISTA__

#include <stdlib.h>

// Declaracion del tipo lista
typedef struct _lista_
{
  void *data;
  struct _lista_ *next;
  struct _lista_ *prev;
}dlist;

// Retorna el primer elemento
dlist *first(dlist *lista)
{
  dlist *temp = lista;

  if(temp)
    while(temp->prev)
      temp = temp->prev;

  return temp;
}

// Retorna el ultimo elemento
dlist *last(dlist *lista)
{
  dlist *temp = lista;

  if(temp)
    while(temp->next)
      temp = temp->next;

  return temp;
}

// Retorna el tamaño de lista
size_t len(dlist *lista)
{
  dlist *temp = first(lista);
  size_t vlen = 0;
  
  while(temp)
  {
    vlen++;
    temp = temp->next;
  }

  return vlen;
}

// Obtener lista en la posicion "posicion"
dlist *_get(dlist *lista, size_t posicion)
{
  dlist *temp = first(lista);
  
  for(size_t i = 0; temp; i++, temp = temp->next)
    if(i == posicion)
      return temp;

  return NULL;
}

// Obtener dato de un elemento
void *get(dlist *lista, size_t posicion)
{
  dlist *ptr = _get(lista, posicion);
  
  if(ptr)
    return ptr->data;

  return NULL;
}

// Inserta un nuevo elemento en la lista
dlist *insert(dlist *lista, void *data, size_t posicion)
{
  size_t i = 0;
  dlist *actual = first(lista);
  dlist *anterior = NULL;

  while(i != posicion && actual)
  {
    anterior = actual;
    actual = actual->next;
    i++;
  }

  // Memoria necesaria para el nuevo elemento
  dlist *nueva = malloc(sizeof(dlist *));

  if(!nueva)
    return lista;
  
  // Asigna los valores al nuevo elemento
  nueva->data = data;
  nueva->next = actual;
  nueva->prev = anterior;

  if(actual)
    actual->prev = nueva;

  if(anterior)
    anterior->next = nueva;
  else
    lista = nueva;

  return lista;
}

// Elimina un elemento en la lista
dlist *delete(dlist *lista, size_t posicion,  void (*freedata)(void *))
{
  dlist *actual = first(lista);
  dlist *anterior = NULL;
  

  for(size_t i = 0; actual; i++)
  {
    if(i == posicion)
    {
      if(anterior)
	anterior->next = actual->next;
      else
	lista = actual->next;

      if(actual->next)
	actual->next->prev = anterior;
      
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
void _swap(dlist *lista, int i, int j)
{
  void *temp;

  temp = get(lista, i);
  _get(lista, i)->data = get(lista, j);
  _get(lista, j)->data = temp;
  
}

// Ordena una lista con el metodo quickssort
void sort(dlist *lista, int izq, int der, int (*cmp)(void *, void *))
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
void clear(dlist *lista, void (*freedata)(void *))
{
  dlist *temp;
  lista = first(lista);
  
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
