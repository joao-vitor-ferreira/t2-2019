#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

typedef struct{
	int prev;
	int next;
	void *thing;
}array;

typedef struct{
	int size; // capacidade do vetor
	int fist; // primeira posição da lista
	int last; // último posição da lista
	int fep; // primeira posição vazia
	array *vet;
}head;

Lista createList(int size){
	head *cabeca;
	cabeca = (head*)malloc(sizeof(head));
	cabeca->size = size;
	cabeca->fep = 0;
	cabeca->fist = -1;
	cabeca->last = -1;
	cabeca->vet = (array*)malloc(sizeof(array)*size);
	int i, prev, next;
	prev = -1;
	next = 1;
	for (i = 0; i < size; i++, prev++, next++){
		cabeca->vet[i].prev = prev;
		cabeca->vet[i].next = next;
		cabeca->vet[i].thing = NULL;
	}
	cabeca->vet[size-1].next = -2;
	return cabeca;
}

int lengthList(Lista L){
	head *newHead = (head*)L;
	return newHead->size;
}

Posic insertList(Lista L, Item info){
	head *newHead = (head*)L;
	if (newHead->fep >= 0){
		newHead->vet[newHead->fep].thing = info;
		if (newHead->fist != -1)
			newHead->vet[newHead->vet[newHead->fep].prev].next = newHead->fep;
		newHead->vet[newHead->fep].next = -1;
		newHead->last = newHead->fep;
		newHead->fep = newHead->vet[newHead->fep].next;
	} else{
		printf("Lista cheia\n");
	}
	newHead->vet[newHead->size - 1].next = -2;
	return newHead->vet[newHead->fep].prev;
}

void removeList(Lista L, Posic p){
	head *newHead = (head*)L;
	if(newHead->fist == p){
		newHead->fist = newHead->vet[newHead->fist].next;
		newHead->vet[newHead->vet[newHead->fist].next].prev = -1;
		newHead->vet[newHead->vet[newHead->fep].prev].next = p;
		newHead->vet[p].next = newHead->fep;
		newHead->vet[p].prev = newHead->vet[newHead->fep].prev;
		newHead->vet[newHead->fep].prev = p;
		newHead->fep = p;
	} else if (newHead->last == p){
		newHead->vet[newHead->vet[p].prev].next = -1;
		newHead->vet[p].next = newHead->fep;
		newHead->fep = p;
		newHead->last = newHead->vet[newHead->fep].prev;
	} else {
		newHead->vet[newHead->vet[p].prev].next = newHead->vet[p].next;
		newHead->vet[newHead->vet[p].next].prev = newHead->vet[p].prev;
		newHead->vet[p].next = newHead->fep;
		newHead->vet[newHead->fep].prev = p;
		newHead->vet[p].prev = newHead->last;
		newHead->fep = p;
	}
}

Posic getFirst(Lista L){
	head *newHead = (head*)L;
	return newHead->fist;
}

Posic getLast(Lista L){
	head *newHead = (head*)L;
	return newHead->last;
}

Posic getNext(Lista L, Posic p){
	head *newHead = (head*)L;
	return newHead->vet[p].next;
}

Posic getPrevious(Lista L,Posic p){
	head *newHead = (head*)L;
	return newHead->vet[p].prev;
}

Item getObjList(Lista L, Posic p){
	head *newHead = (head*)L;
	return newHead->vet[p].thing;
}

void deleteList(Lista L){
	head *newHead = (head*)L;
	if (newHead->vet != NULL)
		free(newHead->vet);
	if (newHead != NULL)
		free(newHead);
}