#ifndef JOGO_H
#define JOGO_H

#include "baralho.h"
#include "jogador.h"

typedef struct {
    Jogador *jogadores;
    int quantidade_jogadores;

    Baralho baralho;

    int rodada_atual;
    int jogador_atual;
    int jogo_ativo;
} Jogo;

// inicializa uma nova partida
int inicializarJogo(Jogo *jogo, int quantidade_jogadores);

// executa o ciclo de uma rodada
void executarRodada(Jogo *jogo);

// solicita a escolha do atributo
Atributo selecionarAtributo(Jogo *jogo);

// determina o vencedor da rodada
int determinarVencedor(Jogo *jogo, Atributo atributo);

// atualiza as cartas dos jogadores após a rodada
void atualizarRodada(Jogo *jogo, int vencedor);

// verifica se a partida terminou
int verificarFimJogo(Jogo *jogo);

// retorna o vencedor da partida
Jogador *determinarVencedorJogo(Jogo *jogo);

// encerra a partida e libera os recursos
void finalizarJogo(Jogo *jogo);

#endif