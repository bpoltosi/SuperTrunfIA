#include "baralho.h"

int carregarBaralhoCSV(Baralho *baralho, const char *caminho);

void embaralharBaralho(Baralho *baralho);

int distribuirCartas(Baralho *baralho, Jogador *jogadores, int quantidade_jogadores);

void liberarBaralho(Baralho *baralho);