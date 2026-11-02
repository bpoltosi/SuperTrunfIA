#ifndef JOGO_H
#define JOGO_H
#include "baralho.h"
#include "jogador.h"
#include "carta.h"

typedef struct { Carta cartas[MAX_CARTAS]; int quantidade; } MonteDisputa;
typedef struct {
    int participa_desempate;
    int tem_carta_reutilizada;
    Carta carta_reutilizada;
} EstadoDesempate;
typedef struct {
    Jogador jogadores[MAX_JOGADORES];
    int quantidade_jogadores;
    Baralho baralho;
    MonteDisputa monte_disputa;
    EstadoDesempate estados[MAX_JOGADORES];
    int rodada_atual;
    int jogador_atual;
    int jogo_ativo;
} Jogo;

/* 1 sucesso; 0 se argumentos, CSV ou distribuição forem inválidos. */
int inicializarJogo(Jogo *jogo, int quantidade_jogadores);
/* Finaliza e limpa o estado lógico; aceita ponteiro nulo. */
void finalizarJogo(Jogo *jogo);
/* 1 se etapa resolvida; 0 em estado inválido ou impossibilidade de execução. */
int executarRodada(Jogo *jogo, Atributo atributo);
int executarDesempate(Jogo *jogo, Atributo atributo);
/* Quantidade de empatados; -1 para argumentos ou estado inválidos. */
int determinarEmpatados(Jogo *jogo, Atributo atributo, int *empatados);
/* 1 sucesso; 0 para ponteiro inválido ou monte cheio. */
int adicionarCartaDisputa(Jogo *jogo, Carta carta);
/* 1 se transferiu integralmente; 0 se falhou sem transferência parcial. */
int entregarMonteDisputa(Jogo *jogo, int vencedor);
/* Esvazia o monte; aceita ponteiro nulo. */
void limparMonteDisputa(Jogo *jogo);
/* 1 sucesso; 0 em falha. Cartas reutilizadas no desempate não entram duas vezes no monte. */
int obterCartaConfronto(Jogo *jogo, int indice_jogador, Carta *carta, int *adicionar_ao_monte);
/* Atualiza participantes; entradas inválidas não devem alterar o estado. */
void atualizarParticipantesDesempate(Jogo *jogo, int *empatados, int quantidade_empatados);
/* 1 se participa do desempate; 0 caso contrário. */
int verificarJogadorDesempate(Jogo *jogo, int indice_jogador);
/* 1 terminou; 0 continua; -1 estado inválido. */
int verificarFimJogo(Jogo *jogo);
/* Ponteiro do vencedor ou NULL se não houver vencedor determinado. */
Jogador *determinarVencedorJogo(Jogo *jogo);
#endif
