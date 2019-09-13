#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "Cidade.h"
#include "Lista.h"
#include "Quadra.h"
#include "Semaforo.h"
#include "Torre.h"
#include "Hidrante.h"
#include "Retangulo.h"
#include "Circulo.h"
#include "Svg.h"


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
    city = (cidade*)malloc(sizeof(cidade));
    city->lQua = createList(nq);
    city->lSem = createList(ns);
    city->lTor = createList(nt);
    city->lHid = createList(nh);
    city->lFor = createList(i);
    return city;
}

Lista getList(Cidade city, char t){
    cidade *newCity = (cidade*)city;
    if (t == 'q'){
        return newCity->lQua;
    } else if (t == 't'){
        return newCity->lTor;
    } else if (t == 'h'){
        return newCity->lHid;
    } else if (t == 's'){
        return newCity->lSem;
    } else if (t == 'f'){
        return newCity->lFor;
    }
    printf("Paramento \"t\" incorreto\n");
    return NULL;
}

void addForma(Cidade city, Item info, int type){
    cidade *newCity = (cidade*)city;
    forms *forma = (forms*)malloc(sizeof(forms));
    forma->thing = info;
    forma->type = type;
    insertList(newCity->lFor, forma);
}

void addQuadra(Cidade city, Quadra q){
    Posic p;
    cidade *newCity = (cidade*)city;
    p = insertList(newCity->lQua, q);
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
;
Item getObjQuadra(Cidade city, Posic p){
    cidade *newCity = (cidade*)city;
    return getObjList(newCity->lQua, p);
}

Item getObjHidrante(Cidade city, Posic p){
    cidade *newCity = (cidade*)city;
    return getObjList(newCity->lHid, p);
}

Item getObjSemaforo(Cidade city, Posic p){
    cidade *newCity = (cidade*)city;
    return getObjList(newCity->lSem, p);
}

Item getObjTorre(Cidade city, Posic p){
    cidade *newCity = (cidade*)city;
    return getObjList(newCity->lTor, p);
}

Posic searchForma(Cidade city, int id, int *type){
    cidade *newCity = (cidade*)city;
    Circulo c1;
    Retangulo r1;
    forms *forma;
    Posic p1;
    for (p1 = getFirst(newCity->lFor); p1 >= 0; p1 = getNext(newCity->lFor, p1)){
        forma = getObjList(newCity->lFor, p1);
        if (forma->type == 0){
            c1 = forma->thing;
            if (getCirculoId(c1) == id){
                *type = forma->type;
                return p1;
            } 
        } else{
            r1 = forma->thing;
            if (getRetanguloId(r1) == id){
                *type = forma->type;
                return p1;
            }
        }
    }
    *type = -1;
    return -1;
}

Posic searchQuadra(Cidade city, char *cep){
    cidade *newCity = (cidade*)city;
    Quadra q1;
    Posic p1;
    for (p1 = getFirst(newCity->lQua); p1 >= 0; p1 = getNext(newCity->lQua, p1)){
        q1 = getObjList(newCity->lQua, p1);
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
    for (p1 = getFirst(newCity->lSem); p1 >= 0; p1 = getNext(newCity->lSem, p1)){
        s1 = getObjList(newCity->lSem, p1);
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
    for (p1 = getFirst(newCity->lTor); p1 >= 0; p1 = getNext(newCity->lTor, p1)){
        t1 = getObjList(newCity->lTor, p1);
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
    for (p1 = getFirst(newCity->lHid); p1 >= 0; p1 = getNext(newCity->lHid, p1)){
        h1 = getObjList(newCity->lHid, p1);
        if (strcmp(getHidranteId(h1), id) == 0){
            return p1;
        }
    }
    return -1;
}

Posic searchEquipUrban(Cidade city, char *id, char *type){
    Posic p1;
    p1 = searchHidrante(city, id);
    if(p1<0){
        p1 = searchSemaforo(city, id);
        if(p1<0){
            p1 = searchTorre(city, id);
            if (p1<0){
                *type = 'z';
                return -1;
            }
            else {
                *type = 't';
                return p1;
            }
        } else{
            *type = 's';
            return p1;
        }
    } else{
        *type = 'h';
        return p1;
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

void printSvgCidade(Cidade city, FILE *svg){
    cidade *newCity = (cidade*)city;
    forms *forma;
    Posic p1, type;
    printSvgList(newCity->lHid, svg, printSvgHidrante);
    printSvgList(newCity->lQua, svg, printSvgQuadra);
    printSvgList(newCity->lSem, svg, printSvgSemaforo);
    printSvgList(newCity->lTor, svg, printSvgTorre);
    for(p1 = getFirst(newCity->lFor); p1 >= 0; p1 = getNext(newCity->lFor, p1)){
        forma = getObjList(newCity->lFor, p1);
        if (forma->type == 0)
            printSvgCirculo(&svg, forma->thing);
        else
            printSvgRetangulo(&svg, forma->thing);
    }
}

void a(Lista list, Function f, int forma, va_list *ap){
    int position = getFirst(list), paux;
    forms *cor; // circulo ou retangulo
    for (;position >= 0;){
        paux = position;
        printf("paux %d\n", paux);
        position = getNext(list, position);
        printf("pos %d\n", position);
        if (forma){
            cor = (forms*)getObjList(list, paux);
            if(cor->type == 1){
                f(cor->thing, 1, ap);
            }else{
                f(cor->thing, 0, ap);
            }
        } else{
            f(getObjList(list, paux),ap);
        }
    }
}

void throughCity (Cidade city, Function f, ...){
    char t;
    va_list ap;
    va_start(ap, f);
    t = va_arg(ap, int);
    cidade *newCity = (cidade*)city;
    if (t == 'q'){
        a(newCity->lQua, f, 0, &ap);
    } else if (t == 't'){
        a(newCity->lTor, f, 0, &ap);
    } else if (t == 'h'){
        a(newCity->lHid, f, 0, &ap);
    } else if (t == 's'){
        a(newCity->lSem, f, 0, &ap);
    } else if (t == 'f'){
        a(newCity->lFor, f, 1, &ap);
    } 
    va_end(ap);
}
