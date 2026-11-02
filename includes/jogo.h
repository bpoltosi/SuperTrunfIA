#ifndef JOGO_H
#define JOGO_H

#include "baralho.h"
#include "jogador.h"
#include "carta.h"

typedef struct
{
    Carta cartas[MAX_CARTAS];
    int quantidade;
} MonteDisputa;

typedef struct
{
    int participa_desempate;
    int tem_carta_reutilizada;
    Carta carta_reutilizada;
} EstadoDesempate;

typedef struct
{
    Jogador jogadores[MAX_JOGADORES];
    int quantidade_jogadores;

    Baralho baralho;
    MonteDisputa monte_disputa;
    EstadoDesempate estados[MAX_JOGADORES];

    int rodada_atual;
    int jogador_atual;
    int jogo_ativo;
} Jogo;

int inicializarJogo(Jogo *jogo, int quantidade_jogadores);
void finalizarJogo(Jogo *jogo);

int executarRodada(Jogo *jogo, Atributo atributo);
int executarDesempate(Jogo *jogo, Atributo atributo);
int determinarEmpatados(Jogo *jogo, Atributo atributo, int *empatados);

int adicionarCartaDisputa(Jogo *jogo, Carta carta);
int entregarMonteDisputa(Jogo *jogo, int vencedor);
void limparMonteDisputa(Jogo *jogo);

int obterCartaConfronto(Jogo *jogo, int indice_jogador, Carta *carta, int *adicionar_ao_monte);
void atualizarParticipantesDesempate(Jogo *jogo, int *empatados, int quantidade_empatados);
int verificarJogadorDesempate(Jogo *jogo, int indice_jogador);

int verificarFimJogo(Jogo *jogo);
Jogador *determinarVencedorJogo(Jogo *jogo);

#endif
