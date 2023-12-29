#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "racionais.h"

#define MINIMO 0
struct racional simplifica_por_div (struct racional r) {
	int i;
	for (i = 2; i <= r.den; i++)			//Simplifica por meio da divisão
		if (r.num % i == 0 && r.den % i == 0) {
			r.num = r.num / i;
			r. den = r.den / i;
		}
	return r;
}

struct racional verifica_sinal (struct racional r) {
	if (r.num < 0 && r.den < 0) {			//Verifica se os dois valores são negativos
		r.num = r.num * -1;
		r.den = r.den * -1;
	}	
	else if (r.den < 0 )				//Se o valor é negativo, mantem o sinal apenas para no num.
		r.den = r.den * - 1;
	return r;
}


//Função que fornece valores aleatorios entre MIN e MAX.
int aleat (int min, int max) {
	int numeroSorteado = min + rand() % (max - min + 1);
	return numeroSorteado;
}

//Funcao responsavel por fornecer o valor do MDC para resolver as operações matemáticas.
int mdc (int a, int b) {
	if (b == 0)
		return a;
	return mdc(b, a % b );
}

//Função responsavel por fornecer o valor do MMC para resolver as operações matematicas.
int mmc (int a, int b) {
	return (a * b) / mdc(a,b);
}

//Função responsavel por simplificar os valores obtidos da função 'Aleat', além de ajustar sinais e valores.
struct racional simplifica_r (struct racional r) {
/*	int div;
	div = mdc(r.num,r.den);
	r.num = r.num / div;
	r.den = r.den / div;
*/	r = simplifica_por_div (r);
	r = verifica_sinal (r);
	return r;
}

//Funcao responsavel por receber os valores de numerador e denominador para formar o número racional.
struct racional cria_r (int numerador, int denominador) {
	struct racional novoRacional;
	novoRacional.num = numerador;
	novoRacional.den = denominador;//verificar valido_r
	novoRacional.valido = valido_r(novoRacional);
	if (novoRacional.valido == 0)
		return novoRacional;
	novoRacional = simplifica_r (novoRacional);
	return novoRacional;
}

//Função responsavel dar inicio no processo de criacao do novo numero racional.
struct racional sorteia_r (int n) {
 	struct racional novoRacional;
	int num, den;
	num = aleat (MINIMO, n);
	den = aleat (MINIMO, n);
	novoRacional = cria_r (num, den);
	return novoRacional;
}

//Funcao responsavel por imprimir os valores conforme as regras da matematica.
void imprime_r (struct racional r) {
	if (!valido_r(r))
		printf ("INVALIDO ");
	else if (r.num == 0)
		printf (" %d", r.num);
	else if (r.den == 1)
		printf (" %d", r.num);
	else if (r.num == r.den)
		printf (" %d ", r.num/r.den);
	else if (r.num < 0 )
		printf (" %d/%d ", r.num, r.den);
	else
		printf (" %d/%d ", r.num, r.den);
}

//Verifica se o numero racional nao esta sendo dividido por zero.
int valido_r (struct racional r) {
	if (r.den == 0)
		return 0;
	return 1;
}

//Funcao responsavel por realizar a funcao da soma entre numeros racionais, além de retornar o valor.
struct racional soma_r (struct racional r1, struct racional r2) {
	struct racional soma;
	soma.den = mmc (r1.den, r2.den);
	soma.num = ((soma.den / r1.den) * r1.num) + ((soma.den / r2.den) * r2.num);
	soma.valido = valido_r (soma);
	soma = simplifica_r (soma);
	return soma;
}

//Funcao responsavel por realizar a operação de subtração entre numeros racionais
struct racional subtrai_r (struct racional r1, struct racional r2) {
	struct racional sub;
	sub.den = mmc (r1.den, r2.den);
	sub.num = ((sub.den / r1.den) * r1.num ) - ((sub.den / r2.den) * r2.num);
	sub.valido = valido_r (sub);
	sub = simplifica_r (sub);
	return sub;
}

//Funcao responsavel por realizar a operação de mutiplicação entre numeros racionais
struct racional multiplica_r (struct racional r1, struct racional r2) {
	struct racional mult;
	mult.num = r1.num * r2.num;
	mult.den = r1.den * r2.den;
	mult.valido = valido_r (mult);
	simplifica_r (mult);
	return mult;
}


//Funcao responsavel por realizar a operação de divisao entre numeros racionais
struct racional divide_r (struct racional r1, struct racional r2) {
	struct racional resp;
	resp.num = r1.num * r2.den;
	resp.den = r1.den * r2.num;
	resp.valido = valido_r (resp);
	if (valido_r (resp))
		resp = simplifica_r (resp);
	return resp;
}
/* acrescente demais includes que voce queira ou precise */

/* 
 * Implemente aqui as funcoes definidas no racionais.h 
 * caso queira, você pode definir neste arquivo funcoes
 * adicionais que serao internas e so podem ser usadas
 * aqui.
*/
