#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "racionais.h"


#define MINIMO 0

/* 
 * Implemente neste arquivo as funções definidas no racionais.h.
 * Caso queira, você pode definir neste arquivo funções adicionais
 * que serão internas a este arquivo.
 *
 * Por exemplo, as funções aleat, mdc e mmc devem ser
 * implementadas neste arquivo.
*/

/* retorna um numero aleatorio entre min e max, inclusive. */
int aleat (int min, int max){
	return min + rand() % (max - min + 1);
}

/* Maximo Divisor Comum entre a e b - calcula o mdc pelo metodo de Euclides */
int mdc (int a, int b){
	if (b == 0)
		return a;
	return mdc(b, a % b);
}

/* Minimo Multiplo Comum entre a e b -  mmc = (a * b) / mdc (a, b)*/
int mmc (int a, int b){
	return (a * b) / mdc (a, b);
}

//Cria um numero racional com base nas informações dos parametros.
struct racional cria_r (int numerador, int denominador) {
	struct racional racionalNovo;
	racionalNovo.num = numerador;
	racionalNovo.den = denominador;
	racionalNovo.valido = valido_r (racionalNovo);
	return racionalNovo;
}

//Retorna um numero racional aleatorio na forma simplificada
struct racional sorteia_r (int max) {
	struct racional racionalNovo;
	int numerador, denominador;
	numerador = aleat (MINIMO,max);
	denominador = aleat (MINIMO,max);
	racionalNovo = cria_r (numerador, denominador);
	simplifica_r (&racionalNovo);
	return racionalNovo;
}

//Retorna o numerador de um racional
int numerador_r (struct racional r) {
	return r.num;
}

//Retorna um denominador de um racional
int denominador_r (struct racional r) {
	return r.den;
}

//Verifica se um racional eh valido (denominador != 0)
int valido_r (struct racional r) {
	if (denominador_r (r) == 0)
		return 0;
	return 1;
}

//Imprima os numeros racionais com formatação
void imprime_r (struct racional r) {
	if (!valido_r (r))
		printf (" INVALIDO ");
	else if (numerador_r (r) == 0)
		printf ("0");
	else if (denominador_r (r) == 1)
		printf (" %d ", numerador_r (r));
	else if (numerador_r (r)  == denominador_r (r))
		printf (" %d ", numerador_r (r) / denominador_r (r));
/*	else if (numerador_r (r) < 0 && denominador_r (r) < 0 ) {
		r.num *= -1;
		r.den *= -1;
		printf (" %d/%d ", numerador_r (r), denominador_r (r));
	}
	else if (denominador_r (r) < 0){
		r.den *= -1;
		printf (" %d/%d ", numerador_r (r), denominador_r (r));
	}
*/	else
		printf (" %d/%d ", numerador_r (r), denominador_r (r));	
}

//Compara dois racionais e retorna um valor referente a comparacao
int compara_r (struct racional r1, struct racional r2) {
	int valor1, valor2;
	int divisor;
	divisor = mmc (denominador_r (r1), denominador_r (r2));
	valor1 = (divisor / denominador_r (r1)) * numerador_r (r1);
	valor2 = (divisor / denominador_r (r2)) * numerador_r (r2);
	if (valor1 > valor2)
		return 1;
	else if (valor1 < valor2)
		return -1;
	else
		return 0;
}

int simplifica_r (struct racional *r) {
	if (!valido_r (*r))
		return 0;
	int divisor = mdc (numerador_r (*r), denominador_r (*r));
	r->num /= divisor;
	r->den /= divisor;

	if (numerador_r (*r) < 0 && denominador_r (*r) < 0) {
		r->num *= -1;
		r->den *= -1;
	}
	else if (denominador_r (*r) < 0)
		r->den *= - 1;
	return 1;
}

int soma_r (struct racional r1, struct racional r2, struct racional *r3) {
	if (!r3)
		return 0;
	if (!valido_r (r1)) {
		*r3 = r2;
		return 0;
	}
	if (!valido_r (r2)) {
		*r3 = r1;
		return 0;
	}
	int divisor, num, den;
        divisor= mmc (denominador_r (r1), denominador_r(r2));
	den= divisor;
	num = ((divisor / denominador_r(r1)) * numerador_r (r1)) + ((divisor / denominador_r (r2)) * numerador_r(r2));
	*r3 = cria_r (num,den);
	return 1;
}

int subtrai_r (struct racional r1, struct racional r2, struct racional *r3) {
	if (!r3)
		return 0;
	if (!valido_r (r1)) {
		*r3 = r2;
		return 0;
	}
	if (!valido_r (r2)) {
		*r3 = r1;
		return 0;
	}
	int divisor, num, den;
	divisor =  mmc (denominador_r (r1), denominador_r(r2));
	den = divisor;
	num = ((divisor / denominador_r(r1)) * numerador_r (r1)) + ((divisor / denominador_r (r2)) * numerador_r(r2));
	*r3 = cria_r (num, den);
	return 1;
}

int multiplica_r (struct racional r1, struct racional r2, struct racional *r3) {	
	if (!r3)
		return 0;
	if (!valido_r (r1)) {
		*r3 = r2;
		return 0;
	}
	if (!valido_r (r2)) {
		*r3 = r1;
		return 0;
	}
	if (!r3)
		return 0;
	int num, den;
	num = numerador_r (r1) * numerador_r (r2);
	den = denominador_r (r1) * denominador_r (r2);
	*r3 = cria_r (num, den);
	return 1;
}

int divide_r (struct racional r1, struct racional r2, struct racional *r3) {
	if (!r3)
		return 0;
	if (!valido_r (r1)) {
		*r3 = r2;
		return 0;
	}
	if (!valido_r (r2)) {
		*r3 = r1;
		return 0;
	}
	if (!r3)
		return 0;
	int num, den;
	num = numerador_r (r1) * denominador_r (r2);
	den = denominador_r (r1) * numerador_r (r2);
	*r3 = cria_r (num,den);
	return 1;
}
