siguel: siguel.o Vector.o Retangulo.o Circulo.o CalculoCirculoRetangulo.o Comandos.o Svg.o
	gcc -o siguel siguel.o Vector.o Circulo.o Retangulo.o CalculoCirculoRetangulo.o Comandos.o Svg.o -lm -std=c99 -fstack-protector-all
siguel.o: siguel.c
	gcc -o siguel.o -c siguel.c -g -std=c99 -fstack-protector-all
Comandos.o: Comandos.c Comandos.h
	gcc -o Comandos.o -c Comandos.c -g -std=c99 -fstack-protector-all
Vector.o: Vector.c Vector.h
	gcc -o Vector.o -c Vector.c -g -std=c99 -fstack-protector-all
Retangulo.o: Retangulo.c Retangulo.h
	gcc -o Retangulo.o -c Retangulo.c -g -std=c99 -fstack-protector-all
Circulo.o: Circulo.c Circulo.h
	gcc -o Circulo.o -c Circulo.c -g -std=c99 -fstack-protector-all
CalculoCirculoRetangulo.o: CalculoCirculoRetangulo.c CalculoCirculoRetangulo.h
	gcc -o CalculoCirculoRetangulo.o -c CalculoCirculoRetangulo.c -g -std=c99 -fstack-protector-all
Svg.o: Svg.c Svg.h
	gcc -o Svg.o -c Svg.c -g -std=c99 -fstack-protector-all -lm
clear:
	rm -rf *.o vgcore*