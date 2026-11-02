#ifndef BARALHO_H
#define BARALHO_H
#include "carta.h"
#include "jogador.h"

typedef struct { Carta cartas[MAX_CARTAS]; int quantidade; } Baralho;

/* Carrega exatamente 34 cartas válidas; em falha, retorna 0 e zera quantidade. */
int carregarBaralhoCSV(Baralho *baralho, const char *caminho);
/* Embaralha sem alterar a quantidade. */
void embaralharBaralho(Baralho *baralho);
/* Distribui igualmente o baralho completo entre dois jogadores vazios; 1 sucesso, 0 falha. */
int distribuirCartas(Baralho *baralho, Jogador *jogadores, int quantidade_jogadores);
/* Zera logicamente o baralho; aceita ponteiro nulo. */
void liberarBaralho(Baralho *baralho);
#endif
