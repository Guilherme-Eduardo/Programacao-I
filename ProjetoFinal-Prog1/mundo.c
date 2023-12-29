// programa principal do projeto "The Boys - 2023"
// Autor: , GRR: 

// seus #includes vão aqui
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "set.h"
#include "lista.h"
#include "lef.h"
#include "mundo.h"

// seus #defines vão aqui
#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS N_HABILIDADES * 5
#define N_BASES N_HEROIS / 6
#define N_MISSOES T_FIM_DO_MUNDO / 100

#define CHEGA 1
#define ESPERA 2
#define DESISTE 3
#define AVISA 4
#define ENTRA 5
#define SAI 6
#define VIAJA 7
#define MISSAO 8
#define FIM 9
#define TRES_DIAS 4320

// 
int aleat (int min, int max) {
	return rand() % (max - min + 1) + min;
}

struct set_t *sorteia_hab (struct set_t *hab, int min, int max) {
	int i, valor;
	for (i = 0; i < hab->size; i++) {
		valor = aleat (min, max);
		set_add (hab, valor);
	}
	return hab;
}

struct heroi_t *criar_heroi (int id_heroi) {
	struct heroi_t *h;
	h = malloc (sizeof (struct heroi_t));
	if (!h)
		return NULL;
	
	h->id = id_heroi;
	h->exp = 0;
	h->paciencia = aleat (0,100);
	h->vel = aleat (50,5000);
	h->habilidade = set_create (N_HABILIDADES);
	int tam = aleat (1,3);
	while (set_card(h->habilidade) < tam) 
		set_add (h->habilidade, aleat (0, N_HABILIDADES -1));
	return h;
}

struct base_t *criar_base (int id_base) {
	struct base_t *b;
	b = malloc (sizeof (struct base_t));
	b->local = malloc (sizeof (struct coord));
	if (!b || !b->local)
		return NULL;
	b->id = id_base;
	b->local->x = aleat (0, N_TAMANHO_MUNDO);
	b->local->y = aleat (0, N_TAMANHO_MUNDO);
	b->lot = aleat (3,10);
	b->presentes = set_create (N_HEROIS);
	b->espera = lista_cria ();
	return b;
}	

struct missao_t *criar_missao (int id_missao) {
	struct missao_t *m;
	m = malloc (sizeof (struct missao_t));
	m->local = malloc (sizeof (struct coord));
	if (!m || !m->local)
		return NULL;
	m->id = id_missao;
	m->local->x = aleat (0, N_TAMANHO_MUNDO);
	m->local->y = aleat (0, N_TAMANHO_MUNDO);
	m->habilidades = set_create (N_HABILIDADES);
	int tam = aleat (6,10);
	while (set_card (m->habilidades) < tam)
		set_add (m->habilidades, aleat (0 , N_HABILIDADES - 1));
	return m;
}

struct mundo_t *criar_mundo () {
	struct mundo_t *w;
	w = malloc (sizeof (struct mundo_t));
	w->tamanho = malloc (sizeof (struct coord));
	if (!w || !w->tamanho)
		return NULL;
	w->total_herois = N_HEROIS;
	w->herois = NULL;
	w->total_bases = N_BASES;
	w->bases = NULL;
	w->total_missoes = N_MISSOES;
	w->missoes = NULL;
	w->total_habilidades = N_HABILIDADES;
	w->tamanho->x = N_TAMANHO_MUNDO;
	w->tamanho->y = N_TAMANHO_MUNDO;
	w->relogio = 0;
	w->tentativas = 0;
	return w;
}

struct heroi_t **iniciar_herois (int n_heroi) {
	struct heroi_t **h;
	h = malloc (n_heroi * sizeof (struct heroi_t));
	if (!h)
		return NULL;
	int i;
	for (i = 0; i < N_HEROIS; i++) {
		h[i] = criar_heroi (i);
	}
	return h;
}

struct base_t **iniciar_bases (int n_base) {
	struct base_t **b;
	b = malloc (n_base * sizeof (struct base_t));
	if (!b)
		return NULL;
	int i;
	for (i = 0; i < N_BASES; i++)
		b[i] = criar_base (i);
	return b;
}


struct missao_t **iniciar_missoes (int n_missao) {
	struct missao_t **m;
	m = malloc (n_missao * sizeof (struct missao_t));
	if (!m)
		return NULL;
	int i;
	for (i = 0; i < N_MISSOES; i++)
		m[i] = criar_missao (i);
	return m;
}


void imprime_mundo (struct mundo_t *w) {
	if (!w)
		return;
	int i;
	for (i = 0; i < w->total_herois; i++) {
		printf ("Heroi id: %d\n", w->herois[i]->id);
		set_print (w->herois[i]->habilidade);
	}

	for (i = 0; i < w->total_bases; i++) {
		printf ("base id: %d\n", w->bases[i]->id);
		set_print (w->bases[i]->presentes);
	}

	for (i = 0; i < w->total_missoes; i++) {
		printf ("Missao id: %d\n", w->missoes[i]->id);
		set_print (w->missoes[i]->habilidades);
	}
}

struct mundo_t *iniciar_mundo (struct mundo_t *w) {
	if (!w)
		return NULL;
	w->herois = iniciar_herois (w->total_herois);
	w->bases = iniciar_bases (w->total_bases);
	w->missoes = iniciar_missoes (w->total_missoes);
	return w;
}

struct mundo_t *destroi_mundo (struct mundo_t *w) {
	if(!w)
		return NULL;
	int i;
	for (i = 0 ; i < w->total_herois ; i++) { 
		set_destroy (w->herois[i]->habilidade);
		free (w->herois[i]);
	}

	for (i = 0 ; i < w->total_bases ; i++) {
		set_destroy (w->bases[i]->presentes);
		lista_destroi (w->bases[i]->espera);
		free (w->bases[i]->local);
		free (w->bases[i]);
	}

	for (i = 0; i < w->total_missoes ; i++) {
		set_destroy (w->missoes[i]->habilidades);
		free (w->missoes[i]->local);
		free (w->missoes[i]);
	}

	free(w->missoes);
	free(w->herois);
	free(w->bases);
	free (w->tamanho);
	free(w);
	return NULL;
}

void simula_mundo (struct mundo_t *w, struct lef_t *l, struct evento_t *ev) {
	bool fim_simulacao = false;
	while (!fim_simulacao) {
		ev = retira_lef (l);
		w->relogio = ev->tempo; 
		switch (ev->tipo) {
			case CHEGA:
				trata_evento_chega (l, relogio_mundo(w), w->herois[ev->dado1], w->bases[ev->dado2]);
				break;
			case ESPERA:
				trata_evento_espera (l, relogio_mundo(w), w->herois[ev->dado1], w->bases[ev->dado2]);
				break;
			case DESISTE:
				trata_evento_desiste (l, relogio_mundo(w), w->herois[ev->dado1], w->bases[ev->dado2]);
				break;
			case AVISA:
				trata_evento_avisa (l, relogio_mundo (w), w->bases[ev->dado2]);
				break;
			case ENTRA:
				trata_evento_entra (l, relogio_mundo (w), w->herois[ev->dado1], w->bases[ev->dado2]);
				break;
			case SAI:
				trata_evento_sai (l, relogio_mundo (w), w->herois[ev->dado1], w->bases[ev->dado2]);
				break;
			case VIAJA:
				trata_evento_viaja (l, relogio_mundo (w), w->herois[ev->dado1], w->bases[ev->dado2], w);
				break;
			case MISSAO:
				trata_evento_missao (l, relogio_mundo (w), w->missoes[ev->dado1], w);
				break;
			case FIM:
				trata_evento_fim (relogio_mundo (w), w, l);
				fim_simulacao = true;
				break;
		}
		destroi_evento (ev);
	}

}

void calcula_distancia_missao (struct mundo_t *w, struct missao_t *m, struct distancia_t *d) {
	int i;
	if (!w || !d)
		return;
	for (i = 0; i < w->total_bases; i++) {
		d[i].dist = sqrt(pow(m->local->x - w->bases[i]->local->x,2) + pow (m->local->y -w->bases[i]->local->y, 2)) ;
		d[i].id_base = i;
	}
}

void insertionSort(struct distancia_t *d, int n) {
    int i, j;
    struct distancia_t tmp;

    for (i = 1; i < n; i++) {
        tmp = d[i];
        j = i - 1;

        // Move os elementos do vetor[0..i-1] que são maiores que tmp
        // para uma posição à frente de sua posição atual
        while (j >= 0 && d[j].dist > tmp.dist) {
            d[j + 1] = d[j];
            j--;
        }
        d[j + 1] = tmp;
    }
}


void trata_evento_missao(struct lef_t *l, int tempo, struct missao_t *m, struct mundo_t *w) {
	if (!l || !m || !w)
		return;

	int i, j, bmp, menor;
	struct evento_t *ev;
	struct set_t *hab;
	struct distancia_t *dist;
	dist = malloc (w->total_bases * sizeof (struct distancia_t));
	calcula_distancia_missao(w, m, dist);	

	bmp = menor = -1;
	printf ("%6d: MISSAO %d HAB REQ:", tempo, m->id);
	set_print (m->habilidades);
	insertionSort (dist, N_BASES);

	for (i = 0; i < w->total_bases; i++) {
		hab = set_create (N_HABILIDADES);
		printf ("%6d: MISSAO %d HAB BASE %d:", tempo, m->id, w->bases[dist[i].id_base]->id);
		for (j = 0; j < w->total_herois; j++) {
			if (set_in (w->bases[dist[i].id_base]->presentes, w->herois[j]->id))
				set_union (hab, w->herois[j]->habilidade, hab);
		}
		set_print (hab);
		if (set_contains (hab, m->habilidades)) {
			bmp = dist[i].id_base;
			for (i = 0; i < w->total_herois; i++) {
				if (w->herois[i]->id_base == bmp)
					w->herois[i]->exp++;
				}
			printf ("%6d: MISSAO %d CUMPRIDA BASE %d HEROIS:", tempo, m->id, bmp);
			set_print (w->bases[bmp]->presentes);
			set_destroy (hab);			
			free (dist);
			return;
		}
		set_destroy (hab);
	}
	if (bmp == -1) {
		ev = cria_evento (tempo + 24 * 60, MISSAO, m->id, 0);
		insere_lef (l, ev);
		printf ("%6d: MISSAO %d IMPOSSIVEL\n", tempo, m->id);
		w->tentativas++;
	}
	free (dist);


}

void trata_evento_viaja (struct lef_t *l, int tempo, struct heroi_t *h, struct base_t *b, struct mundo_t *w) {
	if (!l || !h || !b)
		return;
	struct evento_t *ev;
	int dist = sqrt(pow(w->bases[h->id_base]->local->x - b->local->x, 2) + pow(w->bases[h->id_base]->local->y - b->local->y, 2));
	int duracao = dist / h->vel;
	ev = cria_evento (tempo + duracao, CHEGA, h->id, b->id);
	insere_lef (l, ev);
	printf ("%6d: VIAJA  HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n", tempo, h->id, w->bases[h->id_base]->id, b->id, dist,  h->vel, duracao + tempo);
}

void trata_evento_avisa(struct lef_t *l, int tempo, struct base_t *b) {
	if (!l || !b)
		return;

	int id_heroi;
	struct evento_t *ev;
	printf ("%6d: AVISA  PORTEIRO BASE %d (%2d/%2d) FILA", tempo, b->id, b->presentes->num, b->lot);
	lista_imprime ("", b->espera);

	while ((b->presentes->num < b->lot) && (!lista_vazia (b->espera))) {
		lista_retira (b->espera, &id_heroi, 0);
		set_add (b->presentes, id_heroi);
		ev = cria_evento (tempo, ENTRA, id_heroi, b->id);
		insere_lef (l, ev);
		printf ("%6d: AVISA  PORTEIRO BASE %d ADMITE %2d\n", tempo, b->id, id_heroi);
	}
}

void trata_evento_entra (struct lef_t *l, int tempo, struct heroi_t *h, struct base_t *b) {
	if (!h || !b)
		return;
	int tpb;
	struct evento_t *ev;
	set_add (b->presentes, h->id);
	tpb = 15 + h->paciencia * aleat (1, 20);
	ev = cria_evento (tempo + tpb, SAI, h->id, b->id);
	insere_lef (l, ev);
	printf ("%6d: ENTRA  HEROI %2d BASE %d (%2d/%2d) SAI %d\n", tempo, h->id, b->id, b->presentes->num, b->lot, tpb + tempo);
}

void trata_evento_sai (struct lef_t *l, int tempo, struct heroi_t *h, struct base_t *b) {
	if (!h || !b)
		return;
	struct evento_t *ev;
	int dest_aleat;
	set_del (b->presentes, h->id);
	dest_aleat = aleat (0, N_BASES - 1);
	ev = cria_evento (tempo, VIAJA, h->id, dest_aleat);
	insere_lef (l, ev);
	ev = cria_evento (tempo, AVISA, 0, 0);
	insere_lef (l, ev);
	printf ("%6d: SAI    HEROI %2d BASE %d (%2d/%2d)\n", tempo, h->id, b->id, b->presentes->num, b->lot);
}

void trata_evento_espera (struct lef_t *l, int tempo, struct heroi_t *h, struct base_t *b) {
	if (!h || !b)
		return;
	struct evento_t *ev;
	lista_insere (b->espera, h->id, -1);
	ev = cria_evento (tempo, AVISA, 0, b->id);
	insere_lef (l, ev);
	printf ("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", tempo, h->id, b->id, lista_tamanho (b->espera) - 1);
}

void trata_evento_desiste (struct lef_t *l, int tempo, struct heroi_t *h, struct base_t *b) {
	if (!h || !b)
		return;
	struct evento_t *ev;
	int baseRand;
	baseRand = aleat (0, N_BASES - 1);
	ev = cria_evento (tempo, VIAJA, h->id, baseRand);
	insere_lef (l, ev);
	printf ("%6d: DESIST HEROI %2d BASE %d\n", tempo, h->id, b->id);
}

void trata_evento_chega (struct lef_t *l, int tempo, struct heroi_t *h, struct base_t *b) {
	if (!h || !b)
		return;
	bool espera;
	struct evento_t *ev;
	//set_add (b->presentes, h->id);
	h->id_base = b->id;

	if (b->presentes->num < b->lot && lista_vazia (b->espera))
		espera = true;
	
	else
		espera = (h->paciencia) > (10 * b->espera->size);
	
	if (espera) {
		ev = cria_evento (tempo, ESPERA, h->id,b->id);
		printf ("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) ESPERA\n", tempo, h->id, b->id, b->presentes->num ,b->lot);
	}
	else {
		ev = cria_evento (tempo, DESISTE, h->id, b->id);
		printf ("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) DESISTE\n", tempo, h->id, b->id, b->presentes->num ,b->lot);
		
	}
	insere_lef (l, ev);
}

struct lef_t *cria_eventos_iniciais (struct mundo_t *w, struct lef_t *l) {
	if (!l)
		return NULL;
	int base, tempo, i;
	struct evento_t *ev;
	
	for (i = 0; i < N_HEROIS; i++) {
		base = aleat (0, N_BASES - 1);
		tempo = aleat (0, TRES_DIAS);
		ev = cria_evento (tempo, CHEGA, w->herois[i]->id, w->bases[base]->id);
		insere_lef (l, ev);
	}
	
	for (i = 0; i < N_MISSOES; i++) {
		tempo = aleat (0, T_FIM_DO_MUNDO);
		ev = cria_evento (tempo, MISSAO, w->missoes[i]->id, 0);
		insere_lef (l, ev);
	}

	ev = cria_evento (T_FIM_DO_MUNDO, FIM, 0, 0);
	insere_lef (l, ev);
	return l;
}

void trata_evento_fim (int tempo, struct mundo_t *w, struct lef_t *l) {
	printf ("%6d: FIM\n", tempo);
	int i, m_completas;
       	float media, cont, tentativas;
	struct evento_t *ev;
	cont = 0;
	for (i = 0; i < N_HEROIS; i++) {
		printf ("HEROI %2d PAC %3d VEL %4d EXP %4d HABS", w->herois[i]->id, w->herois[i]->paciencia, w->herois[i]->vel, w->herois[i]->exp);
		set_print (w->herois[i]->habilidade);
	}
	while (l->primeiro) {
		ev = retira_lef (l);
		if (ev->tipo == MISSAO)
			cont++;
		destroi_evento (ev);
	}
	m_completas = w->total_missoes - cont;
	media = (float)m_completas / w->total_missoes * 100;
	tentativas = (float) w->tentativas / w->total_missoes;
	printf ("%d/%d MISSOES CUMPRIDAS (%.2f%%), MEDIA %.2f TENTATIVAS/MISSAO\n", m_completas, w->total_missoes, media, tentativas);
}

int relogio_mundo (struct mundo_t *w) {
	if (!w)
		return -1;
	return w->relogio;
}

int atualiza_relogio_mundo (struct mundo_t *w, struct evento_t *ev) {
	if (!w || !ev)
		return -1;
	w->relogio = ev->tempo;
	return 1;
}
