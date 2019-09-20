#ifndef CALCULOCIRCULORETANGULO_H
#define CALCULOCIRCULORETANGULO_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>	
#include <math.h>
#include "Circulo.h"
#include "Retangulo.h"
	
/*CALCULA A DISTÂNCIA ENTRE DOIS PONTOS NO PLANO CARTESIANO*/
double distanciaEntrePontos(double xa, double ya, double xb, double yb);
/* RETORNA 1 SE O PONTO DE COORDENADAS (X, Y) FOR INTERNO AO RETANGULO*/
int pontoInternoRetangulo(Retangulo r, double x, double y);
/* RETORNA 1 SE O PONTO DE COORDENADAS (X,Y) FOR INTERNO AO CIRCULO*/
int pontoInternoCirculo(Circulo c, double x, double y);
/*	A FUNÇÃO RETORNA 1 CASO A SOBREPOSIÇÃO OCORRA E A FUNÇÃO RETORNA 0 CASO CONTRÁRIO*/
int sobreposicaoCirculoRetangulo(Circulo c, Retangulo r);
/*	A FUNÇÃO RETORNA 1 CASO A SOBREPOSIÇÃO OCORRA E A FUNÇÃO RETORNA 0 CASO CONTRÁRIO*/
int sobreposicaoCirculoCirculo(Circulo c1, Circulo c2);
/*	A FUNÇÃO RETORNA 1 CASO A SOBREPOSIÇÃO OCORRA E A FUNÇÃO RETORNA 0 CASO CONTRÁRIO*/
int sobreposicaoRetanguloRetangulo(Retangulo r1, Retangulo r2);
/* A FUNÇÃO RETORNA A DISTÂNCIA DO CENTRO DE MASSA DE DOIS RETANGULOS*/
double dcmRetanguloRetangulo(Retangulo r1, Retangulo r2);
/* A FUNÇÃO RETORNA A DISTÂNCIA DO CENTRO DE UM CIRCULO E DE UM RETANGULOS*/
double dcmCirculoRetangulo(Circulo c1, Retangulo r1);
/* A FUNÇÃO RETORNA A DISTÂNCIA DO CENTRO DE MASSA DE DOIS CIRCULO*/
double dcmCirculoCirculo(Circulo c1, Circulo c2);
/*A FUNÇÃO RETORNA A DISTANCIA ENTRE DOIS PONTOS DE ACORDO COM A METRICA L1*/
double distPointsL1(double x1, double y1, double x2, double y2);
/*A FUNÇÃO VERIFICA SE OS PONTOS REFERENTES AO RETANGULO NO SVG (XR, YR, WIDTH, HEIGHT) ESTÃO INTEIRAMENTE DENTRO DO CIRCULO (XC, YC, RAIO)*/
int retanguloInternoCirculo(double xr, double yr, double width, double height, double xc, double yc, double raio);
/*A FUNÇÃO VERIFICA SE O RETANGULO(RI) ESTÁ TOTALMENTE INSERIDO DENTRO DE OUTRO RETANGULO(RE)*/
int retanguloInternoRetangulo(double xi, double yi, double wi, double hi, double xe, double ye, double we, double he);
/*A FUNÇÃO VERIFICA SE O CIRCULO(C) ESTÁ TOTALMENTE INSERIDO DENTRO DE OUTRO RETANGULO(R)*/
int circuloInternoRetangulo(double raio, double xc, double yc, double xr, double yr, double wr, double hr);
#endif