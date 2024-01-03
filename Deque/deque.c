#include <stdio.h>
#include <stdlib.h>

//TAD Deque
typedef struct deque_t {
    struct no_t *cabeca;
    struct no_t *cauda;
} deque_t;

//Estrutura dos nós
typedef struct no_t {
    struct no_t *next;
    struct no_t *prev;
    int valor;
} no_t;

deque_t* criaDeque () {
    deque_t *d = (deque_t *)malloc(sizeof(deque_t));
    d->cabeca = NULL;
    d->cauda = NULL;
    return d;
}

int estaVazio (struct deque_t *d) {
    return d->cabeca == NULL;
}

int insereInicio (struct deque_t *d, int elem) {
    no_t *novoNo;
    novoNo = (no_t *) malloc (sizeof (struct no_t));
    novoNo->valor = elem;
    novoNo->next = d->cabeca;
    novoNo->prev = NULL;  

    if (estaVazio(d))
        d->cauda = novoNo;    
    else 
        d->cabeca->prev = novoNo;        
    
    d->cabeca = novoNo;    
    return 1;
}

int insereFim (struct deque_t *d, int elem) {
    no_t *novoNo;
    novoNo = (no_t *) malloc (sizeof (struct no_t));
    novoNo->valor = elem;
    novoNo->prev = d->cauda;
    novoNo->next = NULL;

    if (estaVazio(d))
        d->cabeca = novoNo;    
    else        
        d->cauda->next = novoNo;   

    d->cauda = novoNo;
    return 1;
}
int removeInicio (struct deque_t *d) {
    no_t *no;
    if (estaVazio(d))
        return 0;
    no = d->cabeca;
    if (d->cauda != d->cabeca) {
        d->cabeca = no->next;
        d->cabeca->prev = NULL;        
    }
    else {        
        d->cabeca = NULL;
        d->cauda = NULL;
    }
    free(no);
    return 1;
}

int removeFim (struct deque_t *d) {
    no_t *no;
    if (estaVazio(d))
        return 0;
    no = d->cauda;
    if (d->cabeca != d->cauda) {
        d->cauda = no->prev;
        d->cauda->next = NULL;
    }
    else {
        d->cabeca = NULL;
        d->cauda = NULL;
    }
    free(no);
    return 1;
}

//
int destroiDeque (deque_t *d) {
    while (d->cabeca)
        removeInicio(d);
    free (d);
    return 1;

}

void imprimeDeque (struct deque_t *d) {
    no_t *no;
    no = d->cabeca;
    if (!estaVazio(d)) {
        while (no) {
            printf("%d ", no->valor);
            no = no->next;
        }
    }
}

int main () {
    struct deque_t *d = criaDeque();

    insereInicio(d, 1);
    insereInicio(d, 2);
    insereFim(d, 3);

    printf("Deque: ");
    imprimeDeque(d); // Deve imprimir: 2 1 3

    removeInicio(d);

    printf("\nDeque após remover o início: ");
    imprimeDeque(d); // Deve imprimir: 1 3

    removeFim(d);

    printf("\nDeque após remover o fim: ");
    imprimeDeque(d); // Deve imprimir: 1

    destroiDeque(d);

    return 0;
}