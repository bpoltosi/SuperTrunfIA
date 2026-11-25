#ifndef INTERFACE_H
#define INTERFACE_H

#include "jogo.h"

// exibe o menu principal
void exibirMenu(void);

// exibe as regras
void exibirRegras(void);

// solicita a quantidade de jogadores
int solicitarQuantidadeJogadores(void);

// solicita o nome dos jogadores
void solicitarNomesJogadores(Jogador *jogadores, int quantidade);

// exibe uma carta
void exibirCarta(Carta carta);

// exibe a pontuação dos atributos
void exibirAtributos(Carta carta);

// solicita a escolha do atributo
Atributo solicitarAtributo(void);

// exibe o resultado da rodada
void exibirResultadoRodada(const char *nome_vencedor);

// exibe o resultado final
void exibirResultadoFinal(const Jogador *vencedor, const Jogador jogadores[], int quantidade);

// exibe mensagens de erro
void exibirErro(const char *mensagem);

#endif