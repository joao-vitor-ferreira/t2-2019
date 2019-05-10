#ifndef LISTA_H
#define LISTA_H

	typedef void *Lista;
	typedef void *Posic;
	typedef void *Item;
	typedef void (*RemoveLeak)(Item);

	Lista createList();
	int length(Lista L);
	Posic insert(Lista L, Item info);
	void remover(Lista L, Posic p);
	void deleteListComplete(Lista L, RemoveLeak equipament);
	Posic insertBefore(Lista L, Posic p, Item info);
	Posic insertAfter(Lista L, Posic p, Item info);
	Posic getFirst(Lista L);
	Posic getNext(Posic p);
	Posic getLast(Lista L);
	Posic getPrevious(Posic p);
	Item getObjt(Posic p);

	/*RETORNA O CONTEÚDO DO NÓ DA LISTA E POSIÇÃO P*/
#endif

