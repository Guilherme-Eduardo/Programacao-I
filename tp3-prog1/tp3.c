// Arquivo MAIN que usa o TAD racionais

// coloque os includes necessários aqui

// coloque funcoes adicionais desejadas aqui.
// Exemplo: ordenar, eliminar invalidos...
#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"

int preencheVetor (struct racional **v, int n) {
	if (!v)
		return 0;
	if (n < 1)
		return 0;
	int i, num, den;
	for (i = 0; i < n; i++) {
		scanf ("%d %d", &num, &den);
		v[i] = cria_r (num, den);
	}
	return 1;
}

int destroiVetor (struct racional **v, int n) {
	if (!v) {
		printf ("ERRO AO LIBERAR MEMORIA\n");
		return 0;
	}
	if (n < 1) {
		printf ("ERRO AO LIBERAR MEMORIA\n");
		return 0;
	}
	int i;
	for (i = 0; i < n; i++) {
		destroi_r (v[i]);
	}
	free (v);
	printf ("\nMemoria liberada com sucesso!\n");
	return 1;
}


int eliminaElemento(struct racional **v, int *n) {
	struct racional **copia;
	int i, j;
	j = 0;
	
	copia = malloc(*n * sizeof(struct racional ));
	if (!copia)
		return 0; // Falha na alocação de memória.
	
	
	for (i = 0; i < *n; i++) {
		if (valido_r(v[i])) {
			copia[j] = v[i];
			j++;
		}
	}

	*n = j;
	for (i = 0; i < *n; i++)
		v[i] = copia[i];
	free (copia);
	return 1;
}

void trocar (struct racional **v, int a, int b) {
	struct racional *aux;
	aux = v[a];
	v[a] = v[b];
	v[b] = aux;
}

int minimo (struct racional **v,int inicio, int n) {
	if (!v)
		return 0;

	if (inicio >= n)
		return inicio;
	int m;
	m = minimo (v, inicio, n - 1);
	if (compara_r (v[n], v[m]) == -1)
		m = n;
	return m;
}

void selectionSort (struct racional **v, int inicio, int n) {
	if (!v || inicio >= n)
		return ;
	int m;
	m = minimo (v, inicio, n);
	trocar (v, inicio, m);
	selectionSort (v, inicio + 1, n);
}

void imprimeVetor (struct racional **v, int n) {
	if (!v || n < 1) {
		printf ("Falha ao imprimir\n");
		return;
	}
	int i;
	for (i = 0; i < n; i++)
		imprime_r (v[i]);
	printf ("\n");
}

struct racional* somaVetor (struct racional **v, int n) {
	struct racional *soma;
	soma = cria_r (0,1);
	
	for (int i = 0; i < n; i++) {
		soma_r (v[i], soma, soma);
	}
	return soma;
}

int main () {
	// vetor de ponteiros para racionais
	struct racional **v;  // equivalente a struct racional *v[]
	struct racional *soma;
	int n, tam;
	
	//leia um n tal que 0 < n < 100
	do {
		scanf ("%d", &n);
	} while (n <= 0 || n >= 100);

	/*crie um vetor de n posicoes contendo ponteiros para numeros racionais
	- os racionais deverao ser inicializados com valores lidos do teclado
	- este vetor tambem deve ser alocado dinamicamente*/
	v = malloc(n * sizeof (struct racional));
	preencheVetor (v, n);
	imprimeVetor (v, n);
	tam = n;

	printf ("Eliminando elementos...\n");
	eliminaElemento (v, &n);
	imprimeVetor (v, n);
		
	printf ("Ordenando...\n");
	selectionSort (v, 0, n - 1);
	imprimeVetor (v, n);

	//calcule e imprima a soma de todos os racionais apontados pelo vetor
	soma = somaVetor (v, n);
	imprime_r (soma);
	
	//Liberando memoria
	destroiVetor (v, n);
	destroi_r (soma);
	printf ("\n");
  	return 0;
}
