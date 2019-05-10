#ifndef RETANGULO_H
#define RETANGULO_H

	typedef void *Retangulo;

Retangulo creatRetangulo(int id, double width, double height, double x, double y, char *corPreenchimento, char *corContorno);
int getRetanguloId(Retangulo r);
double getRetanguloWidth(Retangulo r);
double getRetanguloHeight(Retangulo r);
double getRetanguloX(Retangulo r);
double getRetanguloY(Retangulo r);
char *getRetanguloCorPreenchimento(Retangulo r);
char *getRetanguloCorContorno(Retangulo r);
void freeCor(Retangulo r);
void freeRetangulo(Retangulo r);

#endif