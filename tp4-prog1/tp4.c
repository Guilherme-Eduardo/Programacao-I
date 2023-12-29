// TAD lista de números inteiros - programa de teste
// Carlos Maziero - DINF/UFPR, Set 2023

// Coloque os includes necessários a este arquivo aqui.

// Eventuais funções auxiliares (usadas somente neste arquivo) podem vir aqui.

#include <stdio.h>
#include <stdlib.h>
#include "liblista.h"

int main ()
{
	// cria uma lista L vazia
	lista_t *lst;
	int num;
	char *nome = "L";
	lst = lista_cria ();
	lista_imprime (nome,lst);
	// insere no final de L os valores 10, 11, 12, 13 e 14, nessa ordem
	for (int i = 0; i < 5; i++) {
		lista_insere (lst, 10 + i, i);
	}
	lista_imprime (nome,lst);	
	lista_insere (lst, 32, 0);
	lista_insere (lst, 64, 0);
	lista_imprime (nome, lst);
	lista_insere (lst, 103, lista_tamanho (lst) / 2);
	lista_insere (lst, 47, lista_tamanho (lst) / 2);
	lista_imprime (nome, lst);

	// imprime o conteúdo das posições início, 5, última e 100 de L
	printf ("\n");
	lista_consulta (lst, &num, 0);
	lista_consulta (lst, &num, 5);
	lista_consulta (lst, &num, -1);
	lista_consulta (lst, &num, 100);

	printf ("\n");

	// imprime as posições dos valores 5, 10 e 14 em L
	lista_procura (lst, 5);
	lista_procura (lst, 10);
	lista_procura (lst, 14);
	printf ("\n");
	

	// retira de L os valores 12, 103 e 79
	while (!lista_vazia(lst)) {
		lista_retira (lst, &num, 0);
		printf ("Retira primeiro: %d\n", num);
		lista_retira (lst, &num, lista_tamanho(lst) - 1);
		printf ("Retira ultimo: : %d\n", num);
		lista_imprime (nome,lst);	
	
	}
	lista_destroi (lst);
	return 0;
}
