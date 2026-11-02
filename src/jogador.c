#include "jogador.h"

void inicializarJogador(Jogador *jogador, int id, const char *nome);

int adicionarCarta(Jogador *jogador, Carta carta);

void removerCarta(Jogador *jogador, int indice);

Carta obterCartaTopo(Jogador *jogador);

void liberarJogador(Jogador *jogador);