#include "interface.h"

void exibirMenu(void);

void exibirRegras(void);

int solicitarQuantidadeJogadores(void);

void solicitarNomesJogadores(Jogador *jogadores, int quantidade);

void exibirCarta(Carta carta);

void exibirAtributos(Carta carta);

Atributo solicitarAtributo(void);

void exibirResultadoRodada(int vencedor);

void exibirResultadoFinal(Jogador jogador);

void exibirErro(const char *mensagem);