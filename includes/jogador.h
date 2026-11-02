#ifndef JOGADOR_H
#define JOGADOR_H
#include "carta.h"
#define MAX_JOGADORES 2

typedef struct {
    int id;
    char nome[50];
    Carta cartas[MAX_CARTAS];
    int quantidade_cartas;
} Jogador;

/* Inicializa o jogador; nome nulo resulta em string vazia. */
void inicializarJogador(Jogador *jogador, int id, const char *nome);
/* 1 sucesso; 0 para ponteiro nulo ou capacidade esgotada. */
int adicionarCarta(Jogador *jogador, Carta carta);
/* 1 sucesso; 0 para índice inválido ou ponteiro nulo. */
int removerCarta(Jogador *jogador, int indice);
/* Copia o topo sem removê-lo: 1 sucesso, 0 se vazio ou argumentos inválidos. */
int obterCartaTopo(const Jogador *jogador, Carta *carta);
/* Copia e remove o topo: 1 sucesso, 0 em falha. */
int retirarCartaTopo(Jogador *jogador, Carta *carta);
/* Esvazia logicamente o jogador; aceita ponteiro nulo. */
void liberarJogador(Jogador *jogador);
#endif
