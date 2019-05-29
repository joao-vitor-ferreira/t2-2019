#include "Cidade.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    Lista lQua;
    Lista lSem;
    Lista lHid;
    Lista lTor;
    Lista lFor;
}cidade;

typedef struct {
    void *thing;
    int type; /* 0 para Circulo e 1 para retangulo*/
}forms;



Cidade createCidade(int i, int nq, int nh, int ns, int nt){
    cidade *city;
    city->lQua = createList(nq);
    city->lSem = createList(ns);
    city->lTor = createList(nt);
    city->lHid = createList(nh);
    city->lFor = createList(i);
    return city;
}

void addForma(Cidade city, Item info, int type){
    cidade *newCity = (cidade*)city;
    forms *forma = (forms*)malloc(sizeof(forms));
    forma->thing = info;
    forma->type = type;
    insertList(newCity->lFor, forma);
}

void addQuadra(Cidade city, Quadra q){
    cidade *newCity = (cidade*)city;
    insertList(newCity->lQua, q);
}

void addSemaforo(Cidade city, Semaforo s){
    cidade *newCity = (cidade*)city;
    insertList(newCity->lSem, s);
}

void addTorre(Cidade city, Torre t){
    cidade *newCity = (cidade*)city;
    insertList(newCity->lTor, t);
}

void addHidrante(Cidade city, Hidrante h){
    cidade *newCity = (cidade*)city;
    insertList(newCity->lHid, h);
}

Item getObjForma(Cidade city, Posic p){
    cidade *newCity = (cidade*)city;
    forms *forma = getObjList(newCity->lFor, p);
    return forma->thing;
}

Posic searchForma(Cidade city, int id, int *type){
    cidade *newCity = (cidade*)city;
    Circulo c1;
    Retangulo r1;
    forms *forma;
    Posic p1;
    for (p1 = getFirst(newCity->lFor); p1 > 0; p1 = getNext(newCity->lFor, p1)){
        forma = getObjList(newCity->lFor, p1);
        if (forma->type == 0){
            c1 = forma->thing;
            if (getCirculoId(c1) == 0){
                *type = forma->type;
                return p1;
            } 
        } else{
            r1 = forma->thing;
            if (getRetanguloId(r1) == 0){
                *type = forma->type;
                return p1;
            }
        }
    }
    return -1;
}

Posic searchQuadra(Cidade city, char *cep){
    cidade *newCity = (cidade*)city;
    Quadra q1;
    Posic p1;
    for (p1 = getFirst(newCity->lQua); p1 > 0; p1 = getNext(newCity->lQua, p1)){
        if (strcmp(getQuadraCep(q1), cep) == 0){
            return p1;
        }
    }
    return -1;
}

Posic searchSemaforo(Cidade city, char *id){
    cidade *newCity = (cidade*)city;
    Semaforo s1;
    Posic p1;
    for (p1 = getFirst(newCity->lSem); p1 > 0; p1 = getNext(newCity->lSem, p1)){
        if (strcmp(getSemaforoId(s1), id) == 0){
            return p1;
        }
    }
    return -1;
}

Posic searchTorre(Cidade city, char *id){
    cidade *newCity = (cidade*)city;
    Torre t1;
    Posic p1;
    for (p1 = getFirst(newCity->lTor); p1 > 0; p1 = getNext(newCity->lTor, p1)){
        if (strcmp(getTorreId(t1), id) == 0){
            return p1;
        }
    }
    return -1;
}

Posic searchHidrante(Cidade city, char *id){
    cidade *newCity = (cidade*)city;
    Hidrante h1;
    Posic p1;
    for (p1 = getFirst(newCity->lHid); p1 > 0; p1 = getNext(newCity->lHid, p1)){
        if (strcmp(getHidranteId(h1), id) == 0){
            return p1;
        }
    }
    return -1;
}

void removeForma(Cidade city, Posic p){
    cidade *newCity = (cidade*)city;
    forms *forma = getObjList(newCity->lFor, p);
    Circulo c1;
    Retangulo r1;
    if (forma->type == 0){
        c1 = forma->thing;
        if (getCirculoCorContorno(c1) != NULL)
            free(getCirculoCorContorno(c1));
        if (getCirculoCorPreenchimento(c1) != NULL)
            free(getCirculoCorPreenchimento(c1));
        free(c1);
    } else{
        r1 = forma->thing;
        if (getRetanguloCorContorno(r1) != NULL)
            free(getRetanguloCorContorno(r1));
        if (getRetanguloCorPreenchimento(r1) != NULL)
            free(getRetanguloCorPreenchimento(r1));
        free(r1);
    }
    free(forma);
    removeList(newCity->lFor, p);
}

void removeQuadra(Cidade city, Posic p){
    cidade *newCity = (cidade*)city;
    Quadra q1 = getObjList(newCity->lQua, p);
    if (getQuadraCep(q1) != NULL)
        free(getQuadraCep(q1));
    if (getQuadraCorContorno(q1) != NULL)
        free(getQuadraCorContorno(q1));
    if (getQuadraCorPreenchimento(q1) != NULL)
        free(getQuadraCorPreenchimento(q1));
    free(q1);
    removeList(newCity->lQua, p);
}

void removeTorre(Cidade city, Posic p){
    cidade *newCity = (cidade*)city;
    Torre t1 = getObjList(newCity->lTor, p);
    if (getTorreCorContorno(t1) != NULL)
        free(getTorreCorContorno(t1));
    if (getTorreCorPreenchimento(t1) != NULL)
        free(getTorreCorPreenchimento(t1));
    if (getTorreId(t1) != NULL)
        free(getTorreId(t1));
        free(t1);
    removeList(newCity->lTor, p);
}

void removeSemaforo(Cidade city, Posic p){
    cidade *newCity = (cidade*)city;
    Semaforo s1 = getObjList(newCity->lSem, p);
    if (getSemaforoCorContorno(s1) != NULL)
        free(getSemaforoCorContorno(s1));
    if (getSemaforoCorPreenchimento(s1) != NULL)
        free(getSemaforoCorPreenchimento(s1));
    if (getSemaforoId(s1) != NULL)
        free(getSemaforoId(s1));
    free(s1);
    removeList(newCity->lSem, p);
}

void removeHidrante(Cidade city, Posic p){
    cidade *newCity = (cidade*)city;
    Hidrante h1 = getObjList(newCity->lHid, p);
    if (getHidranteCorContorno(h1) != NULL)
        free(getHidranteCorContorno(h1));
    if (getHidranteCorPreenchimento(h1) != NULL)
        free(getHidranteCorPreenchimento(h1));
    if (getHidranteId(h1) != NULL)
        free(getHidranteId(h1));
    free(h1);
    removeList(newCity->lHid, p);
}