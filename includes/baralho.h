#ifndef BARALHO_H
#define BARALHO_H

#include "carta.h"
#include "jogador.h"

typedef struct {
    Carta *cartas;
    int quantidade;
} Baralho;

// carrega as cartas do arquivo CSV
int carregarBaralhoCSV(Baralho *baralho, const char *caminho);

// embaralha as cartas
void embaralharBaralho(Baralho *baralho);

// distribui as cartas entre os jogadores
int distribuirCartas(Baralho *baralho, Jogador *jogadores, int quantidade_jogadores);

// libera a memória do baralho
void liberarBaralho(Baralho *baralho);

#endif