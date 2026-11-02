#ifndef JOGADOR_H
#define JOGADOR_H

#include "carta.h"

typedef struct {
    int id;
    char nome[50];

    Carta *cartas;
    int quantidade_cartas;
    int capacidade_cartas;
} Jogador;

// Inicializa um jogador sem alocar cartas inicialmente.
void inicializarJogador(Jogador *jogador, int id, const char *nome);

// Adiciona uma carta ao final da pilha do jogador.
int adicionarCarta(Jogador *jogador, Carta carta);

// Remove uma carta pelo índice informado.
int removerCarta(Jogador *jogador, int indice);

// Consulta a carta da frente sem removê-la.
int obterCartaTopo(const Jogador *jogador, Carta *carta);

// Retira e devolve a carta da frente da pilha.
int retirarCartaTopo(Jogador *jogador, Carta *carta);

// Libera a memória das cartas do jogador.
void liberarJogador(Jogador *jogador);

#endif
