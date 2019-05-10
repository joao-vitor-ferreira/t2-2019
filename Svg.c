#include <stdio.h>
#include "Svg.h"
#include <math.h>
#include "CalculoCirculoRetangulo.h"

void printSvgCirculo(FILE **svg, Circulo c){
	fprintf(*svg, "<circle cx = \"%f\" cy = \"%f\" r = \"%f\" fill = \"%s\" stroke=\"%s\" stroke-width=\"1\" fill-opacity = \"0.65\"/>\n",
	getCirculoX(c), getCirculoY(c), getCirculoRaio(c), getCirculoCorPreenchimento(c), getCirculoCorContorno(c));
}

void printSvgRetangulo(FILE **svg, Retangulo r){
	fprintf(*svg, "<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"%s\" stroke=\"%s\" stroke-width=\"1\" fill-opacity = \"0.65\"/>\n",
	getRetanguloX(r), getRetanguloY(r), getRetanguloWidth(r), getRetanguloHeight(r), getRetanguloCorPreenchimento(r), getRetanguloCorContorno(r));
}

void printSvgLine(FILE **svg, double x1, double y1, double x2, double y2){
	double xm, ym, d;
	fprintf(*svg, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke-width=\"1\" stroke=\"black\" />\n",
	x1, y1, x2, y2);
	xm = (x1 + x2)/2;
	ym = (y1 + y2)/2;
	d = distanciaEntrePontos(x1, y1, x2, y2);
	fprintf(*svg, "<text x=\"%f\" y=\"%f\" font-family= \"Verdana\"  font-size=\"5\">%f</text>\n",
	xm, ym, d);
}