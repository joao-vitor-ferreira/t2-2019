#ifndef CIDADE_H
#define CIDADE_H
#include "Lista.h"
#include "Quadra.h"
#include "Semaforo.h"
#include "Torre.h"
#include "Hidrante.h"
#include "Retangulo.h"
#include "Circulo.h"
#include <stdio.h>

    typedef void *Cidade;

/* Uma cidade é uma estrutura na qual armazena todas as informações, tal como quadras, hidantes, semaforos, radio-bases e outras formas*/

Cidade createCidade(int i, int nq, int nh, int ns, int nt);
void addQuadra(Cidade city, Item info);
void addSemaforo(Cidade city, Item info);
void addTorre(Cidade city, Item info);
void addHidrante(Cidade city, Item info);
void addForma(Cidade city, Item info, int type);
void removeForma(Cidade city, Posic p);
void removeQuadra(Cidade city, Posic p);
void removeTorre(Cidade city, Posic p);
void removeSemaforo(Cidade city, Posic p);
void removeHidrante(Cidade city, Posic p);
Posic searchQuadra(Cidade city, char *cep);
Posic searchSemaforo(Cidade city, char *id);
Posic searchHidrante(Cidade city, char *id);
Posic searchTorre(Cidade city, char *id);
Posic searchForma(Cidade city, int id, int *type);

#endif