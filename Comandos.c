#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Comandos.h"
#include "Lista.h"
#include "Quadra.h"
#include "Torre.h"
#include "Semaforo.h"
#include "Hidrante.h"
#include "Retangulo.h"
#include "Circulo.h"
#include "CalculoCirculoRetangulo.h"
#include "Svg.h"
#include "Vector.h"

void funcFree(char **a){
	if (a == NULL){
		printf("ERRO\n");
	} else{
		free(*a);
		*a = NULL;
	}
}

char *colocaBarra(char *str){
	if (str == NULL)
		return NULL;
	char *ret;
	if (str[strlen(str)-1] != '/'){
		ret = (char*)malloc(sizeof(char)*(strlen(str) +2));
		sprintf(ret, "%s/", str);
	} else {
		ret = (char*)malloc(sizeof(char)*(strlen(str) + 1));
		strcpy(ret, str);
	}
	return ret;
}

char *concatena(char *str1, char *str2){
	char *aux;

	if (str1 == NULL){
		if (str2 == NULL){
			return NULL;
		} else{
			aux = (char*)malloc(sizeof(char)*(strlen(str2) + 1));
			strcpy(aux, str2);
			return aux;
		}
	} else{
		if (str2 == NULL){
			aux = (char*)malloc(sizeof(char)*(strlen(str1) + 1));
			strcpy(aux, str1);
			return aux;
		} else{
			aux = (char*)malloc(sizeof(char)*(strlen(str1) + strlen(str2) +1));
			strcpy(aux, str1);
			strcat(aux, str2);
			return aux;
		}
	}
}

char *pegaParametro(int argc, char *argv[], char *str){
	int i;
	for (i = 0; i<argc; i++){
		if (strcmp(str, argv[i]) == 0){
			return argv[i+1];
		}
	}
	return NULL;
}

void printSvgVector(Vector vetor, FILE *svg){
	int n, i;
	Circulo c1 = NULL;
	Retangulo r1 = NULL;
	for (i = 0; i < (getSizeVector(vetor)); i++){
		n = getTypeObj(vetor, i);
		if (n == 0){
			c1 = getObjVector(vetor, i);
			printSvgCirculo(&svg, c1);
		} else if (n == 1){
			r1 = getObjVector(vetor, i);
			printSvgRetangulo(&svg, r1);
		}
	}
}

int countQry(char *str){
	int a, ret = 0;
	for (a=strlen(str)-1; a>=0; a--){
		if (str[a] != '/')
			ret++;
		else
			break;
	}
	return ret;
}

char *pegaNomeBase(char *str){
	int i, j, count;
	char *name;
	count = countQry(str);
	name = (char*)malloc(sizeof(char)*(count -3));
	for(i = strlen(str) - count, j = 0; i<(strlen(str)-4); i++, j++){
		name[j] = str[i];
	}
	name[j] = '\0';
	return name;
}


char *funcTxt(int argc, char **argv){
	int i;
	char *aux1 = NULL, *aux2 = NULL, *aux3 = NULL, *aux4 = NULL;
	aux2 = colocaBarra(pegaParametro(argc, argv, "-o"));
	aux1 = pegaNomeBase(pegaParametro(argc, argv, "-f"));
	aux4 = pegaNomeBase(pegaParametro(argc, argv, "-q"));
	aux3 = (char*)malloc(sizeof(char)*(strlen(aux2) + strlen(aux1) + strlen(aux4) + 6));
	strcpy(aux3, aux2);
	strcat(aux3, aux1);
	strcat(aux3, "-");
	strcat(aux3, aux4);
	strcat(aux3, ".txt");
	funcFree(&aux2);
	funcFree(&aux1);
	funcFree(&aux4);
	return aux3;
}

char *funcSvgMain(int argc, char *argv[], char *str){
	char *ret = NULL, *dir = NULL, *uu;
	dir = colocaBarra(pegaParametro(argc, argv, "-o"));
	uu = pegaNomeBase(pegaParametro(argc, argv, "-f"));
	ret = concatena(dir, uu);
	funcFree(&uu);
	uu = concatena(ret, ".svg");
	funcFree(&ret);
	funcFree(&dir);
	return uu;
}

char *funcSvg(int argc, char **argv){
	int i;
	char *aux = NULL, *strdir = NULL, *aux2 = NULL, *aux3 = NULL, *aux4 = NULL;
	strdir = colocaBarra(pegaParametro(argc, argv, "-o"));
	aux = pegaNomeBase(pegaParametro(argc, argv, "-f"));
	aux2 = pegaNomeBase(pegaParametro(argc, argv, "-q"));
	aux3 = (char*)malloc(sizeof(char)*(strlen(strdir) + strlen(aux) + strlen(aux2) + 6));
	strcpy(aux3, strdir);
	funcFree(&strdir);
	strcat(aux3, aux);
	strcat(aux3, "-");
	strcat(aux3, aux2);
	strcat(aux3, ".svg");
	funcFree(&aux);
	funcFree(&aux2);
	return aux3;
}

int barraQry(char *str){
	int a, ret= -1;
	for (a=strlen(str)-1; a>=0; a--){
		if (str[a] == '/'){
			ret = a;
			break;
		}
	}
	return ret;
}

double modulo(double value){
	if (value<0)
		value *= -1;
	return value;
}

void cmpRet(Retangulo r1, double *xma, double *xme, double *yma, double *yme){
	if (*xme < 0)
		*xme = getRetanguloX(r1);
	if (*yme < 0)
		*yme = getRetanguloY(r1);
	if (getRetanguloX(r1) < *xme)
		*xme = getRetanguloX(r1);
	if (getRetanguloY(r1) < *yme)
		*yme = getRetanguloY(r1);
	if ((getRetanguloX(r1) + getRetanguloWidth(r1)) > *xma)
		*xma = getRetanguloX(r1) + getRetanguloWidth(r1);
	if ((getRetanguloY(r1) + getRetanguloHeight(r1)) > *yma)
		*yma = getRetanguloY(r1) + getRetanguloHeight(r1);
}

void cmpCir(Circulo c1, double *xma, double *xme, double *yma, double *yme){
	if (*xme < 0)
		*xme = getCirculoX(c1) - getCirculoRaio(c1);
	if (*yme < 0)
		*yme = getCirculoY(c1) - getCirculoRaio(c1);
	if ((getCirculoX(c1) - getCirculoRaio(c1)) < *xme)
		*xme = (getCirculoX(c1) - getCirculoRaio(c1));
	if ((getCirculoY(c1) - getCirculoRaio(c1)) < *yme)
		*yme = getCirculoY(c1) - getCirculoRaio(c1);
	if ((getCirculoX(c1) + getCirculoRaio(c1)) > *xma)
		*xma = getCirculoX(c1) + getCirculoRaio(c1);
	if ((getCirculoY(c1) + getCirculoRaio(c1)) > *yma)
		*yma = getCirculoY(c1) + getCirculoRaio(c1);
}

void svgCmpCirculo(double *svgH, double *svgW, double x, double y, double raio){
	if ((x+raio) > (*svgW))
		*svgW = x+raio;
	if ((y+raio) > (*svgH))
		*svgH = y+raio;
}

void svgCmpRetangulo(double *svgH, double *svgW, double x, double y, double height, double width){
	if ((x + width) > (*svgW))
		*svgW = x + width;
	if ((y+height) > (*svgH))
		*svgH = y + height;
}

void leituraGeo(int argc, char **argv, double *svgH, double *svgW, FILE *svgMain, Cidade *city, Vector *vetor){
	int NQ = 1000, NS = 1000, NH = 1000, NR = 1000, NF = 1000, i, *type;
	FILE *entrada = NULL;
	Circulo c1 = NULL;
	Posic p1;
	Retangulo r1 = NULL;
	Quadra q1;
	Semaforo s1;
	Torre t1;
	Hidrante h1;
	char *line = NULL, *word = NULL, *cor1 = NULL, *cor2 = NULL, 
	*aux = NULL, *aux2 = NULL, *aux3 = NULL, *text = NULL, *cep;
	double raio, x, y, height, width;
	line = (char*)malloc(sizeof(char)*200);
	word =(char*)malloc(sizeof(char)*30);
	cor1 = (char*)malloc(sizeof(char)*20);
	cep = (char*)malloc(sizeof(char)*20);
	cor2 = (char*)malloc(sizeof(char)*20);
	text = (char*)malloc(sizeof(char)*200);
	aux = colocaBarra(pegaParametro(argc, argv, "-e"));
	aux2 = concatena(aux, pegaParametro(argc, argv, "-f"));
	entrada = fopen(aux2, "r");
	funcFree(&aux);
	funcFree(&aux2);

	//DEFININDO NX

	fscanf(entrada, "%[^\n]\n", line);
	sscanf(line, "%s", word);
	if (strcmp(word, "nx") == 0){
		sscanf("%s %d %d %d %d %d", word, NF, NQ, NH, NS, NR);
	}
	*city = createCidade(NF, NQ, NH, NS, NR);
	rewind (entrada);

	while(!feof(entrada)){
		fscanf(entrada, "%[^\n]\n", line);
		sscanf(line, "%s", word);
		if (strcmp(word, "c") == 0){
			sscanf(line, "%s %d %lf %lf %lf %s %s", word, &i, &raio, &x, &y, cor1, cor2);
			aux = (char*)malloc(sizeof(char)*(strlen(cor1) + 1));
			aux2 = (char*)malloc(sizeof(char)*(strlen(cor2) + 1));
			strcpy(aux, cor1);
			strcpy(aux2, cor2);
			c1 = creatCirculo(i, raio, x, y, aux2, aux);
			addForma(*city, c1, 0);
			p1 = searchForma(*city, i, type);
			svgCmpCirculo(svgH, svgW, x, y, raio);
		}else if (strcmp(word, "r") == 0){
			sscanf(line, "%s %d %lf %lf %lf %lf %s %s", word, &i, &width, &height, &x, &y, cor1, cor2);
			aux = (char*)malloc(sizeof(char)*(strlen(cor1) + 1));
			aux2 = (char*)malloc(sizeof(char)*(strlen(cor2) + 1));
			strcpy(aux, cor1);
			strcpy(aux2, cor2);
			r1 = creatRetangulo(i, width, height, x, y, aux2, aux);
			addForma(*city, r1, 1);
			p1 = searchForma(*city, i, type);
			svgCmpRetangulo(svgH, svgW, x, y, height, width);
		} else if (strcmp(word, "t") == 0){
			sscanf(line, "%s %lf %lf %[^\n]", word, &x, &y, text);
			fprintf(svgMain, "<text x=\"%f\" y=\"%f\" font-family=\"Verdana\" font-size=\"5\">%s</text>\n", x, y, text);
			svgCmpCirculo(svgH, svgW, x, y, 0.0);
		} else if (strcmp(word, "q") == 0){
			sscanf(line, "%s %s %lf %lf %lf %lf", word, cep, &x, &y, &width, &height);
			aux = (char*)malloc(sizeof(char)*(strlen(cor1) + 1));
			aux2 = (char*)malloc(sizeof(char)*(strlen(cor2) + 1));
			aux3 = (char*)malloc(sizeof(char)*(strlen(cep) + 1));
			strcpy(aux, cor1);
			strcpy(aux2, cor2);
			strcpy(aux3, cep);
			q1 = createQuadra(x, y, width, height, cep);
			setQuadraCorContorno(q1, cor1);
			setQuadraCorPreenchimento(q1, cor2);
			addQuadra(*city, q1);
			svgCmpRetangulo(svgH, svgW, x, y, height, width);
		}
		
	}
	funcFree(&line);
	funcFree(&word);
	funcFree(&cor1);
	funcFree(&cor2);
	funcFree(&text);
	fclose(entrada);
}

char *funcSvgBb(int argc, char **argv, char *suf){
	char *dir, *qry, *bb, *aux, *geo;
	dir  = colocaBarra(pegaParametro(argc, argv, "-o"));
	qry = pegaNomeBase(pegaParametro(argc, argv, "-q"));
	geo = pegaNomeBase(pegaParametro(argc, argv, "-f"));
	aux = concatena(dir, geo);
	funcFree(&dir);
	bb = concatena(aux, "-");
	funcFree(&aux);
	aux = concatena(bb, qry);
	funcFree(&bb);
	bb = concatena(aux, "-");
	funcFree(&aux);
	aux = concatena(bb, suf);
	funcFree(&bb);
	bb = concatena(aux, ".svg");
	funcFree(&aux);
	funcFree(&qry);
	funcFree(&geo);
	return bb;
}

void leituraQry(int argc, char **argv, double *svgH, double *svgW, FILE *svgQry, Cidade *city, Vector vetor){
	FILE *entrada = NULL, *txt = NULL, *svgBb;
	Item it;
	int i, j, var, tipo1, tipo2;
	Circulo c1 = NULL, c2 = NULL;
	Retangulo r1 = NULL, r2 = NULL;
	char *line = NULL, *word = NULL, *cor = NULL, *suf = NULL, 
	*aux = NULL, *aux2 = NULL, *aux3 = NULL, *text = NULL;
	double raio, x, y, height, width;
	line = (char*)malloc(sizeof(char)*200);
	word =(char*)malloc(sizeof(char)*30);
	cor = (char*)malloc(sizeof(char)*20);
	suf = (char*)malloc(sizeof(char)*20);
	aux = colocaBarra(pegaParametro(argc, argv, "-e"));
	aux2 = concatena(aux, pegaParametro(argc, argv, "-q"));
	entrada = fopen(aux2, "r");
	funcFree(&aux);
	funcFree(&aux2);
	while(!feof(entrada)){
		fscanf(entrada, "%[^\n]\n", line);
		if (feof(entrada) && strlen(line) == 0)
			break;
		sscanf(line, "%s", word);
		if (strcmp(word, "i?") == 0){
			sscanf(line, "%s %d %lf %lf", word, &j, &x, &y);
			i = getTypeObj(vetor, j);
			if (i == 1){
				r1 = (Retangulo)getObjVector(vetor, j);
				if (r1 != NULL)
					var = pontoInternoRetangulo(r1, x, y);
				else
					var = -1;
			} else{
				c1 = getObjVector(vetor, j);
				if (c1 != NULL)
					var = pontoInternoCirculo(c1, x, y);
				else
					var = -1;
			}
			if (txt == NULL){
				aux = funcTxt(argc, argv);
				txt = fopen(aux, "w");
				funcFree(&aux);
			}
			if(*svgW < x)
				*svgW = x;
			if (*svgH < y)
				*svgH = y;
			if (var == 0){
				fprintf(txt, "%s\nNÃO\n", line);
				fprintf(svgQry, "<circle cx = \"%f\" cy = \"%f\" r = \"3\" fill = \"red\" stroke=\"red\" stroke-width=\"1\" />\n", x, y);
			} else{
				fprintf(txt, "%s\nSIM\n", line);
				fprintf(svgQry, "<circle cx = \"%f\" cy = \"%f\" r = \"3\" fill = \"green\" stroke=\"green\" stroke-width=\"1\" />\n", x, y);
			}
		} else if (strcmp(word, "o?") == 0){
			double xma, yma, xme, yme;
			xma = 0.0;
			yma = 0.0;
			xme = -1.0;
			yme = -1.0;
			sscanf(line, "%s %d %d", word, &i, &j);
			it = getObjVector(vetor, i);
			if (it == NULL){
				printf("Não achei %d", i);
				break;
			}
			tipo1 = getTypeObj(vetor, i);
			it = getObjVector(vetor, j);
			if (it == NULL){
				printf("Não achei %d", j);
				break;
			}
			tipo2 = getTypeObj(vetor, j);
			if (tipo1 == 1){
				if (tipo2 == 1){
					r1 = getObjVector(vetor, i);
					r2 = getObjVector(vetor, j);
					var = sobreposicaoRetanguloRetangulo(r1, r2);
					cmpRet(r1, &xma, &xme, &yma, &yme);
					cmpRet(r2, &xma, &xme, &yma, &yme);
				} else{
					r1 = getObjVector(vetor, i);
					c1 = getObjVector(vetor, j);
					var = sobreposicaoCirculoRetangulo(c1, r1);
					cmpRet(r1, &xma, &xme, &yma, &yme);
					cmpCir(c1, &xma, &xme, &yma, &yme);
				}
			} else{
				if (tipo2 == 1){
					c1 = getObjVector(vetor, i);
					r1 = getObjVector(vetor, j);
					var = sobreposicaoCirculoRetangulo(c1, r1);
					cmpRet(r1, &xma, &xme, &yma, &yme);
					cmpCir(c1, &xma, &xme, &yma, &yme);
					
				} else{
					c1 = getObjVector(vetor, i);
					c2 = getObjVector(vetor, j);
					var  = sobreposicaoCirculoCirculo(c1, c2);
					cmpCir(c1, &xma, &xme, &yma, &yme);
					cmpCir(c2, &xma, &xme, &yma, &yme);
				}
			}
			if (txt == NULL){
				aux = funcTxt(argc, argv);
				txt = fopen(aux, "w");
				funcFree(&aux);
			}
			if (var == 0){
				fprintf(txt, "%s\nNÃO\n", line);
				fprintf(svgQry, "<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"white\" stroke=\"black\" stroke-width=\"4\" fill-opacity = \"0.000\"/>\n", xme, yme, (xma - xme), (yma - yme));
			} else{
				fprintf(txt, "%s\nSIM\n", line);
				fprintf(svgQry, "<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"white\" stroke=\"black\" stroke-width=\"4\" fill-opacity = \"0.000\" stroke-dasharray = \"5,5,5\"/>\n", xme, yme, (xma - xme), (yma - yme));
			}
			if ((xme + (xma -xme)) > *svgW)
				*svgH = xme + (xma -xme);
			if ((yme + (yma - yme)) > *svgH)
				*svgH = yme + (yma - yme);
		} else if (strcmp(word, "d?") == 0){
			sscanf(line, "%s %d %d", word, &i, &j);
			tipo1 = getTypeObj(vetor, i);
			tipo2 = getTypeObj(vetor, j);
			if (tipo1 == 0){
				if (tipo2 == 0){
					c1 = getObjVector(vetor, i);
					c2 = getObjVector(vetor, j);
					x = distanciaEntrePontos(getCirculoX(c1), getCirculoY(c1), getCirculoX(c2), getCirculoY(c2));
					fprintf(svgQry, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke-width=\"2\" stroke=\"brown\" />", getCirculoX(c1), getCirculoY(c1), getCirculoX(c2), getCirculoY(c2));
					fprintf(svgQry, "<text x=\"%f\" y=\"%f\" font-family=\"Verdana\" font-size=\"5\">%f</text>\n", (getCirculoX(c1) + getCirculoX(c2))/2, (getCirculoY(c1) + getCirculoY(c2))/2, x);
				}else{
					c1 = getObjVector(vetor, i);
					r1 = getObjVector(vetor, j);
					x = distanciaEntrePontos(getCirculoX(c1), getCirculoY(c1), getRetanguloX(r1) + getRetanguloWidth(r1)/2, getRetanguloY(r1) + getRetanguloHeight(r1)/2);
					fprintf(svgQry, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke-width=\"2\" stroke=\"brown\" />", getCirculoX(c1), getCirculoY(c1), getRetanguloX(r1) + getRetanguloWidth(r1)/2, getRetanguloY(r1) + getRetanguloHeight(r1)/2);
					fprintf(svgQry, "<text x=\"%f\" y=\"%f\" font-family=\"Verdana\" font-size=\"5\">%f</text>\n",(getCirculoX(c1) + (getRetanguloX(r1) + getRetanguloWidth(r1)/2))/2, (getCirculoY(c1) + (getRetanguloY(r1) + getRetanguloHeight(r1)/2))/2, x);

				}
			} else{
				if (tipo2==0){
					r1 = getObjVector(vetor, i);
					c1 = getObjVector(vetor, j);
					x = distanciaEntrePontos(getCirculoX(c1), getCirculoY(c1), getRetanguloX(r1) - getRetanguloWidth(r1)/2, getRetanguloY(r1) - getRetanguloHeight(r1)/2);
					fprintf(svgQry, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke-width=\"2\" stroke=\"brown\" />", getCirculoX(c1), getCirculoY(c1), getRetanguloX(r1) + getRetanguloWidth(r1)/2, getRetanguloY(r1) + getRetanguloHeight(r1)/2);
					fprintf(svgQry, "<text x=\"%f\" y=\"%f\" font-family=\"Verdana\" font-size=\"5\">%f</text>\n",(getCirculoX(c1) + (getRetanguloX(r1) + getRetanguloWidth(r1)/2))/2, (getCirculoY(c1) + (getRetanguloY(r1) + getRetanguloHeight(r1)/2))/2, x);
				}else{
					r1 = getObjVector(vetor, i);
					r2 = getObjVector(vetor, j);
					x = distanciaEntrePontos(getRetanguloX(r1) - getRetanguloWidth(r1)/2, getRetanguloY(r1) - getRetanguloHeight(r1)/2, getRetanguloX(r2) - getRetanguloWidth(r2)/2, getRetanguloY(r2) - getRetanguloHeight(r2)/2);
					fprintf(svgQry, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke-width=\"2\" stroke=\"brown\" />", getRetanguloX(r2) + getRetanguloWidth(r2)/2, getRetanguloY(r2) + getRetanguloHeight(r2)/2, getRetanguloX(r1) + getRetanguloWidth(r1)/2, getRetanguloY(r1) + getRetanguloHeight(r1)/2);
					fprintf(svgQry, "<text x=\"%f\" y=\"%f\" font-family=\"Verdana\" font-size=\"5\">%f</text>\n",((getRetanguloX(r2) + getRetanguloWidth(r2)/2) + (getRetanguloX(r1) + getRetanguloWidth(r1)/2))/2, ((getRetanguloY(r2) + getRetanguloHeight(r2)/2) + (getRetanguloY(r1) + getRetanguloHeight(r1)/2))/2, x);
				}
			}
			if (txt == NULL){
				aux = funcTxt(argc, argv);
				txt = fopen(aux, "w");
				funcFree(&aux);
			}
			fprintf(txt, "%s\n%.10f\n", line, x);
		}else if (strcmp(word, "bb") == 0){
			sscanf(line, "%s %s %s", word, suf, cor);
			aux = funcSvgBb(argc, argv, suf);
			svgBb = fopen(aux, "w");
			funcFree(&aux);
			fprintf(svgBb, "<svg width = \"%f\" height = \"%f\">", *svgW, *svgH);
			for (i = 0; i<getSizeVector(vetor); i++){
				j = getTypeObj(vetor, i);
				if (j == 0){
					c1 = getObjVector(vetor, i);
					fprintf(svgBb, "<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"%s\" stroke=\"%s\" stroke-width=\"1\" />\n", getCirculoX(c1) - getCirculoRaio(c1), getCirculoY(c1) - getCirculoRaio(c1),getCirculoRaio(c1)*2, getCirculoRaio(c1)*2, cor, cor);
					printSvgCirculo(&svgBb, c1);
				} else if (j == 1){
					r1 = getObjVector(vetor, i);
					fprintf(svgBb, "<ellipse cx=\"%f\" cy=\"%f\" rx=\"%f\" ry=\"%f\" style=\"fill:%s\" />", getRetanguloX(r1) + getRetanguloWidth(r1)/2, getRetanguloY(r1) + getRetanguloHeight(r1)/2, getRetanguloWidth(r1)/2, getRetanguloHeight(r1)/2, cor);
					printSvgRetangulo(&svgBb, r1);
				}
			}
			fprintf(svgBb, "</svg>");
			fclose(svgBb);
		}
	}
	if (txt!= NULL)
		fclose(txt);
	funcFree(&line);
	funcFree(&word);
	funcFree(&cor);
	funcFree(&suf);
	fclose(entrada);
}