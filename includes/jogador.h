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

void inicializarJogador(Jogador *jogador, int id, const char *nome);
int adicionarCarta(Jogador *jogador, Carta carta);
int removerCarta(Jogador *jogador, int indice);
int obterCartaTopo(const Jogador *jogador, Carta *carta);
int retirarCartaTopo(Jogador *jogador, Carta *carta);
void liberarJogador(Jogador *jogador);

#endif
