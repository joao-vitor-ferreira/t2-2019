#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

typedef struct reg{
	int id;
	void *obj;
	struct reg *next;
	struct reg *prev;
}celula;

typedef struct abc{
	int length;
	struct reg *first;
	struct reg *last;
}list;

Lista createList(){
	list *L = (list*)malloc(sizeof(list));
	L->first = NULL;
	L->last = NULL;
	L->length = 0;
	return(L);
}

int length(Lista L){
	list *newlist;
	newlist = (list*)L;
	return newlist->length;
}

Posic insert(Lista L, Item info){
	list *newlist;
	celula *newreg, *aux;
	newlist = (list*) L;
	newreg = (celula*)malloc(sizeof(celula));
	newreg->next = NULL;
	newreg->prev = NULL;
	newreg->obj = info;

	if (newlist->length == 0){
		newlist->first = newreg;
		newlist->last = newreg;
		newreg->id = 0;
	} else {
		aux = newlist->last;
		aux->next = newreg;
		newreg->prev = aux;
		newreg->next = NULL;
		newreg->id += 1;
		newlist->last = newreg;
	}
	newlist->length++;

	return (Posic) newreg;
}

void remover(Lista L, Posic p){
	list *newlist = (list*)L;
	celula *newreg = (celula*)p;
	celula *prev = newreg->prev;
	celula *next = newreg->next;
	
	if (prev!=NULL){
		prev->next = next;
	} else{
		newlist->first = next;	
		if (next == NULL)
			newlist->first = NULL;
	} if (next!=NULL){
		next->prev = prev;
	} else{
		newlist->last = prev;
		if (prev == NULL)
			newlist->last = NULL;
	}
	(newlist->length)--;
	if (newreg->obj != NULL)
		free(newreg->obj);
	if (newreg != NULL)
		free(newreg);	
}

Posic insertBefore(Lista L, Posic p, Item info){
	list *newlist = (list*)L;
	celula *newreg, *aux1, *aux2;
	aux1 = (celula*)p;
	aux2 = aux1->prev;
	newreg = (celula*)malloc(sizeof(celula));
	newreg->next = NULL;
	newreg->prev = NULL;
	if (aux2!=NULL){
		aux2->next = newreg;
		newreg->prev = aux2;
	} else{
		newlist->first = newreg;
	}
	newreg->next = aux1;
	aux1->prev = newreg;
	newreg->obj = info;
	newlist->length++;
	return (Posic)newreg;
}

Posic insertAfter(Lista L, Posic p, Item info){
	list *newlist = (list*)L;
	celula *newreg, *aux1, *aux2;
	aux1 = (celula*)p;
	aux2 = aux1->next;
	newreg = (celula*)malloc(sizeof(celula));
	newreg->next = NULL;
	newreg->prev = NULL;
	if (aux2!=NULL){
		aux2->prev = newreg;
		newreg->next = aux2;
	} 
	else newlist->last = newreg;
	newreg->prev = aux1;
	aux1->next = newreg;
	newreg->obj = info;
	newlist->length++;
	return (Posic) newreg;
}

Posic getFirst(Lista L){
	list *newlist = (list*)L;
	return (Posic) newlist->first;
}

Posic getLast(Lista L){
	list *newlist = (list*)L;
	return (Posic) newlist->last;
}

Posic getNext(Posic p){
	celula *newreg = (celula*)p;
	if (newreg != NULL){
		if (newreg->next != NULL)
			return(Posic)newreg->next;
	}
	return NULL;
}

Posic getPrevious(Posic p){
	celula *newreg = (celula*)p;
	if (newreg!=NULL)
		return (Posic) newreg->prev;
	else
		return NULL;	
}

Item getObjt(Posic p){
	if (p != NULL){
		celula *newreg = (celula*)p;
		return (Item)newreg->obj;
	}
	return NULL;
}

void deleteListComplete(Lista L, RemoveLeak equiment){
	Posic p1, p;
	int tam;
	list *newlist = (list*)L;
	celula *aux, *aux1;
	aux = newlist->first;
	tam = newlist->length;
	while(aux != NULL){
		aux1 = aux->next;
		equiment(getObjt((Posic)aux));
		remover(L, (Posic)aux);
		aux = aux1;
		tam--;
		if (tam <= 0)
			break;
	}
	if (newlist != NULL)
		free(newlist);
}