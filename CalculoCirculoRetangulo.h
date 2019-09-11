#ifndef CALCULOCIRCULORETANGULO_H
#define CALCULOCIRCULORETANGULO_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>	
#include <math.h>
#include "Circulo.h"
#include "Retangulo.h"
	
double distanciaEntrePontos(double xa, double ya, double xb, double yb);
/*CALCULA A DISTÂNCIA ENTRE DOIS PONTOS NO PLANO CARTESIANO*/
int pontoInternoRetangulo(Retangulo r, double x, double y);
/* RETORNA 1 SE O PONTO DE COORDENADAS (X, Y) FOR INTERNO AO RETANGULO*/
int pontoInternoCirculo(Circulo c, double x, double y);
/* RETORNA 1 SE O PONTO DE COORDENADAS (X,Y) FOR INTERNO AO CIRCULO*/
int sobreposicaoCirculoRetangulo(Circulo c, Retangulo r);
/*	A FUNÇÃO RETORNA 1 CASO A SOBREPOSIÇÃO OCORRA E A FUNÇÃO RETORNA 0 CASO CONTRÁRIO*/
int sobreposicaoCirculoCirculo(Circulo c1, Circulo c2);
/*	A FUNÇÃO RETORNA 1 CASO A SOBREPOSIÇÃO OCORRA E A FUNÇÃO RETORNA 0 CASO CONTRÁRIO*/
int sobreposicaoRetanguloRetangulo(Retangulo r1, Retangulo r2);
/*	A FUNÇÃO RETORNA 1 CASO A SOBREPOSIÇÃO OCORRA E A FUNÇÃO RETORNA 0 CASO CONTRÁRIO*/
double dcmRetanguloRetangulo(Retangulo r1, Retangulo r2);
/* A FUNÇÃO RETORNA A DISTÂNCIA DO CENTRO DE MASSA DE DOIS RETANGULOS*/
double dcmCirculoRetangulo(Circulo c1, Retangulo r1);
/* A FUNÇÃO RETORNA A DISTÂNCIA DO CENTRO DE UM CIRCULO E DE UM RETANGULOS*/
double dcmCirculoCirculo(Circulo c1, Circulo c2);
/* A FUNÇÃO RETORNA A DISTÂNCIA DO CENTRO DE MASSA DE DOIS CIRCULO*/
double distPointsL1(double x1, double y1, double x2, double y2);
/*A FUNÇÃO RETORNA A DISTANCIA ENTRE DOIS PONTOS DE ACORDO COM A METRICA L1*/
#endif