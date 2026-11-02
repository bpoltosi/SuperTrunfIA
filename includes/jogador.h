#ifndef JOGADOR_H
#define JOGADOR_H

#include "carta.h"

typedef struct {
    int id;
    char nome[50];

    Carta *cartas;
    int quantidade_cartas;
} Jogador;

// inicializa um jogador
void inicializarJogador(Jogador *jogador, int id, const char *nome);

// adiciona uma carta à mão
int adicionarCarta(Jogador *jogador, Carta carta);

// remove uma carta da mão
void removerCarta(Jogador *jogador, int indice);

// retorna a carta do topo
Carta obterCartaTopo(Jogador *jogador);

// libera a memória do jogador
void liberarJogador(Jogador *jogador);

#endif