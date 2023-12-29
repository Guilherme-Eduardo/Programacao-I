/* Implementa o TAD Lista de Eventos Futuros (LEF) 
 * Feito em C para a disciplina CI1001 - Programacao 1 
 * Autor: Luis C. E. Bona, adaptado por Carlos Maziero
 *
 * Versao 1.0.0 10/11/2021
 * Versao 1.0.1 16/08/2022
 * Versao 2.0.0 14/12/2022
 * Versao 2.1.0 05/10/2023
 */

#include <stdio.h>
#include <stdlib.h>
#include "lef.h"

/* A  LEF é uma lista que armazena eventos ordenados pelo membro tempo 
 * do tipo evento_t. Cada evento pode ter um tipo e armazenar em dados 
 * diferentes estruturas de dados que permitem descrever cada evento. */

/* 
 * Cria um evento contendo os parâmetros informados.
 * Retorna um ponteiro para o evento ou NULL se falhar.
 */
struct evento_t *cria_evento (int tempo, int tipo, int dado1, int dado2) {
	struct evento_t *ev;
	ev = malloc (sizeof (struct evento_t));
	if (!ev)
		return NULL;
	ev->tempo = tempo;
	ev->tipo = tipo;
	ev->dado1 = dado1;
	ev->dado2 = dado2;
	return ev;
}

/* 
 * Destroi um evento e retorna NULL.
 */ 
struct evento_t *destroi_evento (struct evento_t *e) {
	if (!e)
		return NULL;
	free (e);
	return NULL;
}

/* 
 * Cria uma LEF vazia 
 * Retorna um ponteiro para a LEF ou NULL se falhar.
 */
struct lef_t *cria_lef () {
	struct lef_t *lef;
	lef = malloc (sizeof (struct lef_t));
	if (!lef)
		return NULL;
	lef->primeiro = NULL;
	return lef;
}

/* 
 * Destroi a LEF, liberando a memória ocupada por ela, inclusive os eventos.
 * Retorna NULL.
 */ 
struct lef_t *destroi_lef (struct lef_t *l) {
 	if (!l)
	       return NULL;
	struct nodo_lef_t *aux, *no;
	no = l->primeiro;
	while (no) {
		aux = no;
		aux->evento = destroi_evento (aux->evento);
		no = no->prox;
		free (aux);
	}
	free (l);
	return NULL;	
}

/*
 * Insere o evento apontado na LEF na ordem de tempos crescentes.
 * Eventos com o mesmo tempo devem respeitar a politica FIFO.
 * Retorna 1 em caso de sucesso ou 0 caso contrario.
*/
int insere_lef (struct lef_t *l, struct evento_t *e) {
	if (!l || !e)
		return 0;

	struct nodo_lef_t *aux, *no;
	no = malloc (sizeof (struct nodo_lef_t));
	if (!no)
		return 0;
	no->evento = e;
	no->prox = NULL;
	aux = l->primeiro;

	if (aux == NULL) {
		l->primeiro = no;
	}
	else if (aux->evento->tempo > no->evento->tempo) {
		l->primeiro = no;
		no->prox = aux;
	}
	else if (aux->prox == NULL) {
		aux->prox = no;
	}
 	else {
		while (aux->prox) {
			if (aux->prox->evento->tempo > no->evento->tempo) {
				no->prox = aux->prox;
				aux->prox = no;
				break;
			}
			aux = aux->prox;
		}
		aux->prox = no;
	}
	return 1;
}

/* 
 * Retira o primeiro evento da LEF.
 * Retorna ponteiro para o evento ou NULL se falhar.
 */
struct evento_t *retira_lef (struct lef_t *l) {
	if (!l)
		return NULL;
	if (vazia_lef(l))
		return NULL;

	struct nodo_lef_t *aux;
	struct evento_t *ev;
	aux = l->primeiro;
	ev = aux->evento;
	l->primeiro = aux->prox;
	free (aux);
	return ev;	
}

/* 
 * Informa se a LEF está vazia.
 * Retorna 1 se estiver vazia, 0 se não estiver ou -1 se falhar.
 */
int vazia_lef (struct lef_t *l) {

	if (!l)
    		return -1;

	  if (!l->primeiro)
		return 1;
	return 0 ;
}
/* 
 * Imprime a LEF. Não faz parte do TAD, mas serve para depuração.
 * Formato de saída:
 * tempo tipo dado1 dado2
 * tempo tipo dado1 dado2
 * ...
 * total XX eventos
 */
void imprime_lef (struct lef_t *l) {
	if (!l)
		return;
	
	int i;
	i = 0;
	struct nodo_lef_t *aux;
	aux = l->primeiro;
	printf ("LEF:\n");
	while (aux) {
		printf ("%2d %d %d %d\n", aux->evento->tempo,
		aux->evento->tipo, aux->evento->dado1, aux->evento->dado2);
		aux = aux->prox;
		i++;
	}
	printf ("total %d eventos\n", i);
}
