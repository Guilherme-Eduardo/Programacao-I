#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

/* 
 * Cria e retorna uma nova pilha.
 * Retorna NULL em caso de erro de alocação.
*/
struct pilha *pilha_cria () {
    struct pilha *p;
    p = malloc (sizeof (struct pilha));
    if (!p)
        return NULL;
    p->topo = NULL;
    p->tamanho = 0;
    return p;
}

/* Desaloca toda memoria da pilha e faz pilha receber NULL. */
void pilha_destroi(struct pilha **pilha) {
    if (!pilha || !(*pilha))
        return;

    while ((*pilha)->topo) {
        struct nodo *temp = (*pilha)->topo;
        (*pilha)->topo = (*pilha)->topo->prox;
        free(temp);
    }
    
    free(*pilha);
    *pilha = NULL;
}

/* 
 * Insere dado na pilha (politica LIFO). Retorna 1
 * em caso de sucesso e 0 em caso de falha.
*/
int push (struct pilha *pilha, int dado) {
    if (!pilha)
        return 0;
    struct nodo *novoNo;
    novoNo = malloc (sizeof (struct nodo));
    if (!novoNo)
        return 0;
    novoNo->chave = dado;
    novoNo->prox = pilha->topo;
    pilha->topo = novoNo;
    pilha->tamanho++;
    return 1;
}

/* 
 * Remove o topo (politica LIFO) e retorna o elemento 
 * no parametro dado. A funcao retorna 1 em caso de 
 * sucesso e 0 no caso da pilha estar vazia.
*/
int pop (struct pilha *pilha, int *dado) {
    if (pilha == NULL || pilha->topo == NULL)
        return 0;
    *dado = pilha->topo->chave;
    struct nodo *temp = pilha->topo;
    pilha->topo = pilha->topo->prox;
    free(temp);
    pilha->tamanho--;
    return 1;
}
 
/* 
 * Similar ao pop, mas retorna o elemento dado sem remove-lo. 
 * A funcao retorna 1 em caso de sucesso e 0 no caso 
 * da pilha estar vazia.
*/
int pilha_topo (struct pilha *pilha, int *dado) {
    if (!pilha || !pilha->topo)
        return 0;
    *dado = pilha->topo->chave;
    return 1;
}

/* Retorna o numero de elementos da pilha, que pode ser 0. */
int pilha_tamanho (struct pilha *pilha) {
    if (!pilha)
        return 0;
    return pilha->tamanho;
}

/* Retorna 1 se pilha vazia, 0 em caso contrario. */ 
int pilha_vazia (struct pilha *pilha) {
    if (!pilha || pilha->tamanho > 0)
        return 0;
    return 1;
}

