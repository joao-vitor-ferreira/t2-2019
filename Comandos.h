#ifndef COMANDOS_H
#define COMANDOS_H
#include "Vector.h"
#include "Cidade.h"
#include <stdio.h>

	typedef char *((*Object)(Item));
	typedef double (*Dist)(double x1, double y1, double x2, double y2);

char *funcIn(int argc, char **argv, char *str);
char *concatena(char *str1, char *str2);
void leituraGeo(int argc, char **argv, double *svgH, double *svgW, FILE *svgMain, Cidade *city);
void leituraQry(int argc, char **argv, double *svgH, double *svgW, FILE *svgMain, Cidade *city, Vector vetor);
void funcFree(char **a);
char *colocaBarra(char *str);
char *pegaParametro(int argc, char *argv[], char *str);
char *funcSvgQry(int argc, char **argv);
char *funcSvgMain(int argc, char *argv[], char *str);
char *pegaNomeBase(char *str);
void printSvgVector(Vector vetor, FILE *svg);
char *funcSvg(int argc, char **argv);

#endif