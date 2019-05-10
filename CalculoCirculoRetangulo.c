#include <stdio.h>
#include <math.h>
#include "CalculoCirculoRetangulo.h"
#include "Retangulo.h"
#include "Circulo.h"

double distanciaEntrePontos(double xa, double ya, double xb, double yb){
	double d = sqrt(pow(xa - xb, 2) + pow(ya - yb, 2));
	return d;
}

int pontoInternoRetangulo(Retangulo r, double x, double y){
	short p1 = 0, p2 = 0, p3 = 0 , p4 = 0;
	double xr, yr;
	xr = getRetanguloX(r);
	yr = getRetanguloY(r);
	if (x >= xr && y >= yr)
		p1 = 1;
	xr = xr + getRetanguloWidth(r);
	if (x <= xr && y >= yr)
		p2 = 1;
	yr = yr + getRetanguloHeight(r);
	if (x <= xr && y <= yr)
		p3 = 1;
	xr = getRetanguloX(r);
	if (x >= xr && y <= yr)
		p4 = 1;

	if (p1 == 1 && p2 == 1 && p3 == 1 && p4 == 1)
		return 1;
	else
		return 0;	
}

int pontoInternoCirculo(Circulo c, double x, double y){
	double xc, yc, d;
	xc = getCirculoX(c);
	yc = getCirculoY(c);
	d = distanciaEntrePontos(xc, yc, x, y);
	if (d <= getCirculoRaio(c))
		return 1;
	else
		return 0;
}

int sobreposicaoCirculoRetangulo(Circulo c, Retangulo r){
	
	double d, xa, xb, ya, yb;
	short caso = 0;
	int test;

	while(caso < 4){
		xa = getCirculoX(c);
		ya = getCirculoY(c);
		xb = getRetanguloX(r);
		yb = getRetanguloY(r);
		if (caso == 1){
			xb = xb + getRetanguloWidth(r);
		} else if (caso == 2){
			yb = yb + getRetanguloHeight(r);
		} else if (caso == 3){
			xb = xb + getRetanguloWidth(r);
			yb = yb + getRetanguloHeight(r);
		}
		d = distanciaEntrePontos(xa, ya, xb, yb);
		if (d <= getCirculoRaio(c)){
			return 1;
		} else{
			test = pontoInternoRetangulo(r, getCirculoX(c),getCirculoY(c));
			if (test == 1)
				return 1;
		}
		caso++;
	}
	return 0;
}

int sobreposicaoCirculoCirculo(Circulo c1, Circulo c2){
	double d, xa, xb, ya, yb;
	xa = getCirculoX(c1);
	xb = getCirculoX(c2);
	ya = getCirculoY(c1);
	yb = getCirculoY(c2);
	d = distanciaEntrePontos(xa, ya, xb, yb);
	if (d<=(getCirculoRaio(c1) + getCirculoRaio(c2)))
		return 1;
	return 0;
}

int sobreposicaoRetanguloRetangulo(Retangulo r1, Retangulo r2){
	double d, x, y;
	int c, retorno = 0;
	x = getRetanguloX(r1);
	y = getRetanguloY(r1);
	c = pontoInternoRetangulo(r2, x, y);
	if (c == 1 )
		retorno = 1;
	x = x + getRetanguloWidth(r1);
	c = pontoInternoRetangulo(r2, x, y);
	if (c == 1)
		retorno = 1;
	y = y + getRetanguloHeight(r1);
	c = pontoInternoRetangulo(r2, x, y);
	if (c == 1)
		retorno = 1;
	x = getRetanguloX(r1);
	c = pontoInternoRetangulo(r2, x, y);
	if (c ==1)
		retorno = 1;	
	if (retorno == 0 ){
		x = getRetanguloX(r2);
		y = getRetanguloY(r2);
		c = pontoInternoRetangulo(r1, x, y);
		if (c == 1 )
			retorno = 1;
		x = x + getRetanguloWidth(r2);
		c = pontoInternoRetangulo(r1, x, y);
		if (c == 1)
			retorno = 1;
		y = y + getRetanguloHeight(r2);
		c = pontoInternoRetangulo(r1, x, y);
		if (c == 1)
			retorno = 1;
		x = getRetanguloX(r2);
		c = pontoInternoRetangulo(r1, x, y);
		if (c ==1)
			retorno = 1;	
	} else
		return 1;
	if (retorno == 0)
		return 0;
	else
		return 1;
}

double dcmRetanguloRetangulo(Retangulo r1, Retangulo r2){
	double x1, x2, y1, y2;
	x1 = getRetanguloX(r1) + getRetanguloWidth(r1)/2;
	x2 = getRetanguloX(r2) + getRetanguloWidth(r2)/2;
	y1 = getRetanguloY(r1) - getRetanguloHeight(r1)/2;
	y2 = getRetanguloY(r2) - getRetanguloHeight(r2)/2;
	return distanciaEntrePontos(x1, y1, x2, y2);
}

double dcmCirculoRetangulo(Circulo c1, Retangulo r1){
	double xc, xr, yc, yr;
	xc = getCirculoX(c1);
	xr = getRetanguloX(r1) + getRetanguloWidth(r1)/2;
	yc = getCirculoX(c1);
	yr = getRetanguloY(r1) - getRetanguloHeight(r1)/2;
	return distanciaEntrePontos(xc, yc, xr, yr);
}

double dcmCirculoCirculo(Circulo r1, Circulo r2){
	double x1, x2, y1, y2;
	x1 = getCirculoX(r1);
	x2 = getCirculoX(r2);
	y1 = getCirculoY(r1);
	y2 = getCirculoY(r2);
	return distanciaEntrePontos(x1, y1, x2, y2);
}