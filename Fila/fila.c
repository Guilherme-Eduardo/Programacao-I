#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

/* 
 * Cria e retorna uma nova fila.
 * Retorna NULL em caso de erro de alocação.
*/
struct fila *fila_cria () {
    struct fila *fila;
    fila = malloc (sizeof (struct fila));
    if (!fila)
        return NULL;
    fila->ini = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
    return fila;
}

/* Desaloca toda memoria da fila e faz fila receber NULL. */
void fila_destroi (struct fila **fila) {
    if (!(*fila))
        return;
    struct nodo *aux;
    aux = (*fila)->ini;
    while ((*fila)->ini) {
        aux = (*fila)->ini;
        (*fila)->ini = (*fila)->ini->prox;
        free(aux);
    }
    free (*fila);
    return ;
}

/* 
 * Insere dado na fila (politica FIFO). Retorna 1
 * em caso de sucesso e 0 em caso de falha.
*/
int enqueue (struct fila *fila, int dado) {
    if (!fila)
        return 0;
    struct nodo *no;
    no = malloc (sizeof (struct nodo));
    if (!no)
        return 0;

    no->chave = dado;
    no->prox = NULL;
    if (fila->ini == NULL) {
        fila->ini = no;
        fila->fim = no;
    }
    else {
        fila->fim->prox = no;
        fila->fim = no;
    }
    fila->tamanho++;
    return 1;
}

/* 
 * Remove dado da fila (politica FIFO) e retorna o elemento 
 * no parametro dado. A funcao retorna 1 em caso de 
 * sucesso e 0 no caso da fila estar vazia.
*/
int dequeue (struct fila *fila, int *dado) {
    if (!fila || fila->tamanho == 0)
        return 0;
    if (!fila->ini)
        return 0;
    struct nodo *aux;
    aux = fila->ini;
    fila->ini = fila->ini->prox;
    fila->tamanho--;
    *dado = aux->chave;
    free (aux);
    return 1;
}
 
/* Retorna o numero de elementos da pilha, que pode ser 0. */
int fila_tamanho (struct fila *fila) {
    if (!fila)
        return 0;
    return fila->tamanho;
}

/* Retorna 1 se fila vazia, 0 em caso contrario. */ 
int fila_vazia (struct fila *fila) {
    if (!fila || fila->tamanho > 0)
        return 0;
    return 1;
}
