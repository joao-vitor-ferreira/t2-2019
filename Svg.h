#ifndef SGV_H
#define SGV_H

#include "Circulo.h"
#include "Retangulo.h"

	typedef void (*Print)(FILE **svg, void *);

void printSvgCirculo(FILE **svg, Circulo c);
void printSvgRetangulo(FILE **svg, Retangulo r);
void printSvgLine(FILE **svg, double x1, double y1, double x2, double y2);

#endif