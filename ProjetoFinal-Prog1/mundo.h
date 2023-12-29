#ifndef _MUNDO_H
#define _MUNDO_H

struct coord {
	int x;
	int y;
};

struct distancia_t {
	int id_base;
	int dist;
};

struct heroi_t {
	int id;
	struct set_t *habilidade;
	int paciencia;
	int vel;
	int exp;
	int id_base;
};

struct base_t {
	int id;
	int lot;
	struct set_t *presentes;
	lista_t *espera;
	struct coord *local;
};

struct missao_t {
	int id;
	struct set_t *habilidades;
	struct coord *local;
};

struct mundo_t {
	int total_herois;
	struct heroi_t **herois;
	int total_bases;
	struct base_t **bases;
	int total_missoes;
	struct missao_t **missoes;
	int total_habilidades;
	struct coord *tamanho;
	int relogio;
	int tentativas;
};

struct heroi_t **iniciar_herois (int n_heroi);

struct mundo_t *criar_mundo ();

struct mundo_t *destroi_mundo (struct mundo_t *w);

struct base_t **iniciar_bases (int n_base);

struct missao_t **iniciar_missao (int n_missao);

struct mundo_t * iniciar_mundo () ;

void simula_mundo (struct mundo_t *w, struct lef_t *l, struct evento_t *ev);

struct lef_t *cria_eventos_iniciais (struct mundo_t *w, struct lef_t *l);

int aleat (int min, int max);

void trata_evento_chega (struct lef_t *l, int tempo, struct heroi_t *t, struct base_t *b);

void trata_evento_espera (struct lef_t *l, int tempo, struct heroi_t *h, struct base_t *b);

void trata_evento_desiste (struct lef_t *l, int tempo, struct heroi_t *h, struct base_t *b);

void trata_evento_avisa (struct lef_t *l, int tempo, struct base_t *b);

void trata_evento_sai (struct lef_t *l, int tempo, struct heroi_t *h, struct base_t *b);

void trata_evento_entra (struct lef_t *l, int tempo, struct heroi_t *h, struct base_t *b);

void trata_evento_viaja (struct lef_t *l, int tempo, struct heroi_t *h, struct base_t *b, struct mundo_t *w);

void trata_evento_missao (struct lef_t *l, int tempo, struct missao_t *m, struct mundo_t *w);

void trata_evento_fim (int tempo, struct mundo_t *w, struct lef_t *l);

int relogio_mundo (struct mundo_t *w);

int atualiza_relogio_mundo (struct mundo_t *w, struct evento_t *ev);

#endif
