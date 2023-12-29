/* TP3 - A diferenca desta implementação com relacao ao TP2
 * eh que os racionais devem alocados dinamicamente */

/* acrescente aqui os demais includes que voce queira ou precise */
#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"

/* 
 * Implemente aqui as funcoes definidas no racionais.h.
 * Caso queira, voce pode definir neste arquivo funcoes
 * adicionais que serao internas a este arquivo.
 *
 * Por exemplo, as funções mdc e mmc devem ser
 * implementadas neste arquivo.
*/

/* Maximo Divisor Comum entre a e b      */
/* calcula o mdc pelo metodo de Euclides */
int mdc (int a, int b){
	if (b == 0)
		return a;
	return mdc (b, a % b);
}

/* Minimo Multiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
int mmc (int a, int b){
	return (a * b) / mdc (a , b);
}

struct racional *cria_r (long int numerador, long int denominador) {
	struct racional *r;
	r = malloc (sizeof (struct racional));
	if (!r)
		return NULL;
	r->num = numerador;
	r->den = denominador;
	simplifica_r (r);
	return r;
}

void destroi_r (struct racional *r) {
	if (!r)
		return;
	free (r);
}

int numerador_r (struct racional *r, long int *num) {
	if (!r || r->den == 0)
		return 0;	
	*num = r->num;
	return 1;
}

int denominador_r (struct racional *r, long int *den) {
	if (!r || r->den == 0)
		return 0;
	*den = r->den;
	return 1;
}

int valido_r (struct racional *r) {
	if (!r || r->den == 0)
		return 0;
	return 1;
}

void imprime_r (struct racional *r) {
	if (!r)
		printf (" NULO ");
	else if (!valido_r(r)) {
		printf (" Invalido ");
	}
	else if (r->num == 0)
		printf (" %ld ", r->num);
	else if (r->den == 1)
		printf (" %ld ", r->num);
	else if (r->num == r->den)
		printf (" 1 ");
	else
		printf (" %ld/%ld ", r->num, r->den);
}

int compara_r (struct racional *r1, struct racional *r2) {
	if ((!r1 || !r2) || (r1->den == 0 || r2->den == 0))
		return -2;
	
	int divisor, valor1, valor2;
	divisor = mmc (r1->den, r2->den);
	valor1 = (divisor / r1->den) * r1->num;
	valor2 = (divisor / r2->den) * r2->num;
	
	if (valor1 < valor2)
		return -1;
	if (valor1 > valor2)
		return 1;
	else
		return 0;
}

int simplifica_r (struct racional *r) {
	if (!r || !valido_r(r))
		return 0;
	int divisor;
	divisor = mdc (r->num, r->den);
	r->num /= divisor;
	r->den /= divisor;

	if ((r->num < 0 && r->den < 0) || r->den < 0) {
		r->num *= -1;
		r->den *= -1;
	}
	return 1;
}

int soma_r (struct racional *r1, struct racional *r2, struct racional *r3) {
	if (!r1 || !r2 || !r3)
		return 0;
	if (!valido_r (r1) || !valido_r (r2) || !valido_r (r3))
		return 0;
	
	int divisor, valor1, valor2;
	divisor = mmc (r1->den, r2->den);
	valor1 = (divisor / r1->den) * r1->num;
	valor2 = (divisor / r2->den) * r2->num;
	r3->num = valor1 + valor2;
	r3->den = divisor;
	simplifica_r (r3);
	return 1;
}

int subtrai_r (struct racional *r1, struct racional *r2, struct racional *r3) {
	if (!r1 || !r2 || !r3)
		return 0;
	if (!valido_r (r1) || !valido_r (r2) || !valido_r (r3))
		return 0;
	
	int divisor, valor1, valor2;
	divisor = mmc (r1->den, r2->den);
	valor1 = (divisor / r1->den) * r1->num;
	valor2 = (divisor / r2->den) * r2->num;
	r3->num = valor1 - valor2;
	r3->den = divisor;
	simplifica_r (r3);
	return 1;
}
int multiplica_r (struct racional *r1, struct racional *r2, struct racional *r3) {
	if (!r1 || !r2 || !r3)
		return 0;	

	r3->num = r1->num * r2->num;
	r3->den = r1->den * r2->den;
	simplifica_r (r3);
	
	return 1;
}

int divide_r (struct racional *r1, struct racional *r2, struct racional *r3) {
	if (!r1 || !r2 || !r3)
		return 0;	
	
	if (!valido_r (r1) || !valido_r (r2) || !valido_r (r3))
		return 0;
	r3->num = r1->num * r2->den;
	r3->den = r1->den * r2->num;
	simplifica_r (r3);
	
	return 1;
}
