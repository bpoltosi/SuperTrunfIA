#ifndef BARALHO_H
#define BARALHO_H

#include "carta.h"
#include "jogador.h"

typedef struct {
    Carta cartas[MAX_CARTAS];
    int quantidade;
} Baralho;

int carregarBaralhoCSV(Baralho *baralho, const char *caminho);
void embaralharBaralho(Baralho *baralho);
int distribuirCartas(Baralho *baralho, Jogador *jogadores, int quantidade_jogadores);
void liberarBaralho(Baralho *baralho);

#endif
