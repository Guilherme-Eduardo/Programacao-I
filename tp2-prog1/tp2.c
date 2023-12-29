#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "racionais.h"

#define MAX 100

//Realiza a troca de posicao de dois structs em um vetor
int troca (struct racional *r1, struct racional *r2) {
	struct racional aux;
	aux = *r1;
	*r1 = *r2;
	*r2 = aux;
	return 1;
}

//Realiza a ordenacao do vetor de struct por Selection Sort
int ordenaRacional (struct racional r[], int tam) {
	int menor;

	for (int i = 0; i < tam - 1; i++) {
	menor = i;
		for (int j = i + 1; j < tam; j++) {
			if (compara_r (r[menor],r[j]) == 1 )
				menor = j;
		}
		troca (&r[menor], &r[i]);	
	}
	return 1;
}

//Remove valores nulos do vetor 
int eliminaElementos (struct racional r[],  int *tam) {
	if (*tam < 0)
		return -1;
	for (int i = 0; i < *tam; i++) {
		if (!valido_r(r[i])){
			troca (&r[i], &r[*tam - 1]);	
			*tam = *tam - 1;
		}
	}
	return 1;
}

void imprimeVetor (struct racional r[], int tam) {
	int i;
	for (i = 0; i < tam; i++)
		imprime_r (r[i]);
	printf ("\n");
}

//Seta 0 no den e num no struct responsavel receber a soma
int inicializaSoma (struct racional *r) {
	r->num = 0;
	r->den = 0;
	r->valido = 1;
	return 1;
}

int somaVetor (struct racional r[], int tam, struct racional *soma) {
	int i;
	inicializaSoma (soma);
	for (i = 0; i < tam; i++) 
		soma_r (r[i], *soma, soma);
	simplifica_r (soma);
	return 1;
}

int main () {

	srand(0);
	int i, n;
	struct racional r[MAX];
	struct racional soma;
	do {
		printf ("Informe um valor para n:");
		scanf("%d", &n);
	} while (n <= 0 || n >= 100);	

	for (i = 0; i < n; i++) 
		r[i] = sorteia_r (n);
	imprimeVetor (r, n);	
	eliminaElementos (r, &n);
	imprimeVetor (r, n);
	ordenaRacional (r, n);
	imprimeVetor (r, n);
	somaVetor (r,n, &soma);
	imprime_r (soma);
	printf ("\n");
	return 0;
}
