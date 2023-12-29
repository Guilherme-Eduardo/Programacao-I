// TAD lista de números inteiros - interface
// Carlos Maziero - DINF/UFPR, Set 2023

#include <stdio.h>
#include <stdlib.h>
#include "liblista.h"

// Cria uma lista vazia.
// Retorno: ponteiro p/ a lista ou NULL se falhar.
lista_t* lista_cria () {
	
	lista_t *l;
	l = malloc (sizeof (lista_t));
	if (!l)
		return NULL;
	l->head = NULL;
	l->tail = NULL;
	l->size = 0;
	return l;
}

// Remove todos os elementos da lista, libera espaço.
// Retorno: NULL.
lista_t* lista_destroi (lista_t* lst) {
	if (!lst)
		return NULL;
	if (lista_vazia(lst)) {
		free (lst);
		return NULL;
	}
	lnode_t *no, *aux;
	no = lst->head;
	while (no) {
		aux = no;
		no = no->next;
		free (aux);
	}
	free(lst);
	return NULL;
}

// Nas operações insere/retira/consulta, a posição 0 indica o início da lista;
// se a posição for -1 ou for além do fim, considerar o fim da lista.

// Insere o elemento na lista na posição indicada.
// Retorno: número de elementos na lista após a operação ou -1 se falhar.
int lista_insere (lista_t* lst, int elem, int pos) {
	if (!lst)
		return -1;
	lnode_t *no;
	no = malloc (sizeof (lnode_t));
	if (!no)
		return -1;
	no->val = elem;

	if (lst->size == 0) {
		no->next = NULL;
		no->prev = NULL;
		lst->head = no;
		lst->tail = no;

	}
	else if (pos == 0) {
		no->next = lst->head;
		no->prev = NULL;
		lst->head->prev = no;
		lst->head = no;
	}

	else if (pos == -1 || pos >= lst->size) {
		no->next = NULL;
		lst->tail->next = no;
		no->prev = lst->tail;
		lst->tail = no;
	}

	else {
		lnode_t *aux;
		aux = lst->head;
		for (int i = 0; i < pos - 1; i++) {
			aux = aux->next;
		}
		no->prev = aux;
		no->next = aux->next;
		aux->next = no;
		aux->next->prev = no;
	}
	lst->size++;
	return lst->size;
}

// Retira o elemento da lista, na posição indicada.
// Retorno: número de elementos na lista após a operação ou -1 se falhar.
int lista_retira (lista_t* lst, int* elem, int pos) {
	lnode_t *aux ;
	int i;
	if (!lst)
		return -1;			
	if (pos < 0 || pos > lst->size) {
		printf ("NAO ENCONTRADO\n");
		return -1;
	}
	if ( pos == 0 && lst->size == 1) { //caso onde a lista tem so um elemento
		aux = lst->head;
		lst->tail = NULL;
		lst->head = NULL;
	}
	else if ( pos == 0 && lst->size > 1 ) { //caso onde head é alterado
		aux = lst->head;
		lst->head = aux->next;
		lst->head->prev = NULL;
		aux->next = NULL;
	}
	else if ( pos == lst->size -1 && lst->size > 1) { //caso onde o elemento a ser tirado é o ultimo
		aux = lst->tail;
		lst->tail = aux->prev;
		//lst->tail->next = NULL;
		aux->prev = NULL;
	}
	else if( pos > 0 && pos < lst->size -1) { //inserção entre head e tail
		aux = lst->head;
		for (i = 0; i < pos && i < lst->size - 1; i++) 
			aux = aux->next;
		//desconecta o node a ser retirado e conecta o antecessor ao sucessor
		aux->next->prev = aux->prev;
		aux->prev->next = aux->next;
		aux->prev = NULL;
		aux->next = NULL;
	}
	lst->size--;
	*elem = aux->val;
	free(aux);
	return lista_tamanho(lst);
}

// Informa o valor do elemento na posição indicada, sem retirá-lo.
// Retorno: número de elementos na lista ou -1 se falhar.
int lista_consulta (lista_t* lst, int* elem, int pos) {
	if (!lst)
		return -1;
	if (pos < 0 || pos > lst->size - 1) {
		printf ("VALOR NA POSICAO %d: %d\n", pos, lst->tail->val);
		return -1;
	}
	lnode_t *no;
	no = lst->head;
	for (int i = 0; i < pos; i++) {
		no = no->next; 
	}
	printf ("VALOR NA POSICAO %d: %d\n", pos, no->val);
	*elem = no->val;
	return lst->size;
}

// Informa a posição da 1ª ocorrência do elemento indicado.
// Retorno: posição do elemento ou -1 se não encontrar ou falhar.
int lista_procura (lista_t* lst, int elem) {
	if (!lst)
		return -1;
	lnode_t *no;
	no = lst->head;
	for (int i = 0; i < lst->size; i++) {
		if (no->val == elem) {
			printf ("POSICAO DO VALOR %d: %d\n", elem, i);
			return i;
		}
		no = no->next;
	}
	printf ("POSICAO DO VALOR %d: NAO ENCONTRADO\n", elem);	
	return -1;
}

// Informa se a lista está vazia.
// Retorno: 1 se a lista está vazia ou 0 caso contrário.
int lista_vazia (lista_t* lst) {
	if (!lst)
		return -1;
	if (lst->size == 0)
		return 1;
	return 0;
}

// Informa o tamanho da lista (o número de elementos presentes nela).
// Retorno: número de elementos na lista ou -1 se falhar.
int lista_tamanho (lista_t* lst) {
	if (!lst)
		return -1;
	return lst->size;
}

// Imprime o conteúdo da lista, do inicio ao fim, neste formato:
// nome: [ valor valor valor valor ... ] (nnn elementos)
// Esta função não faz parte do TAD, mas é útil para testes.
void lista_imprime (char *nome, lista_t* lst) {
	if (!lst)
		return;
	int i;
	lnode_t *no;
	printf ("%c: [", *nome);
	if (lista_vazia(lst)) {
		printf ("] (0 elementos)\n");
		return;
	}
	no = lst->head;
	for (i = 0; i < lst->size; i++){
		printf (" %d ", no->val);
		no = no->next;
	}	
	printf ("] (%d elementos)\n", i);
}
