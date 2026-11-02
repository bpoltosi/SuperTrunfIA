#include <string.h>

#include "jogo.h"
#include "interface.h"
#include "util.h"

int inicializarJogo(Jogo *jogo, int quantidade_jogadores)
{
    if (jogo == NULL || quantidade_jogadores != MAX_JOGADORES)
        return 0;

    memset(jogo, 0, sizeof(*jogo));
    jogo->quantidade_jogadores = quantidade_jogadores;

    for (int i = 0; i < quantidade_jogadores; i++)
        inicializarJogador(&jogo->jogadores[i], i + 1, "");

    if (!carregarBaralhoCSV(&jogo->baralho, "data/cartas.csv")) {
        finalizarJogo(jogo);
        return 0;
    }

    embaralharBaralho(&jogo->baralho);
    if (!distribuirCartas(&jogo->baralho, jogo->jogadores, quantidade_jogadores)) {
        finalizarJogo(jogo);
        return 0;
    }

    jogo->rodada_atual = 1;
    jogo->jogador_atual = 0;
    jogo->jogo_ativo = 1;
    return 1;
}

void finalizarJogo(Jogo *jogo)
{
    if (jogo == NULL) return;
    for (int i = 0; i < MAX_JOGADORES; i++)
        liberarJogador(&jogo->jogadores[i]);
    liberarBaralho(&jogo->baralho);
    limparMonteDisputa(jogo);
    memset(jogo->estados, 0, sizeof(jogo->estados));
    jogo->quantidade_jogadores = 0;
    jogo->jogo_ativo = 0;
}

int executarRodada(Jogo *jogo, Atributo atributo)
{
    (void)jogo; (void)atributo;
    return 0;
}

int executarDesempate(Jogo *jogo, Atributo atributo)
{
    (void)jogo; (void)atributo;
    return 0;
}

int determinarEmpatados(Jogo *jogo, Atributo atributo, int *empatados)
{
    (void)jogo; (void)atributo; (void)empatados;
    return -1;
}

int adicionarCartaDisputa(Jogo *jogo, Carta carta)
{
    if (jogo == NULL || jogo->monte_disputa.quantidade < 0 ||
        jogo->monte_disputa.quantidade >= MAX_CARTAS)
        return 0;
    jogo->monte_disputa.cartas[jogo->monte_disputa.quantidade++] = carta;
    return 1;
}

int entregarMonteDisputa(Jogo *jogo, int vencedor)
{
    int quantidade_atual, quantidade_monte;
    if (jogo == NULL || vencedor < 0 ||
        vencedor >= jogo->quantidade_jogadores ||
        jogo->monte_disputa.quantidade < 0 ||
        jogo->monte_disputa.quantidade > MAX_CARTAS)
        return 0;

    quantidade_atual = jogo->jogadores[vencedor].quantidade_cartas;
    quantidade_monte = jogo->monte_disputa.quantidade;
    if (quantidade_atual < 0 || quantidade_atual + quantidade_monte > MAX_CARTAS)
        return 0;

    for (int i = 0; i < quantidade_monte; i++)
        jogo->jogadores[vencedor].cartas[quantidade_atual + i] =
            jogo->monte_disputa.cartas[i];

    jogo->jogadores[vencedor].quantidade_cartas += quantidade_monte;
    limparMonteDisputa(jogo);
    return 1;
}

void limparMonteDisputa(Jogo *jogo)
{
    if (jogo != NULL) jogo->monte_disputa.quantidade = 0;
}

int obterCartaConfronto(Jogo *jogo, int indice_jogador, Carta *carta,
                        int *adicionar_ao_monte)
{
    (void)jogo; (void)indice_jogador; (void)carta; (void)adicionar_ao_monte;
    return 0;
}

void atualizarParticipantesDesempate(Jogo *jogo, int *empatados,
                                      int quantidade_empatados)
{
    (void)jogo; (void)empatados; (void)quantidade_empatados;
}

int verificarJogadorDesempate(Jogo *jogo, int indice_jogador)
{
    (void)jogo; (void)indice_jogador;
    return 0;
}

int verificarFimJogo(Jogo *jogo)
{
    if (jogo == NULL || jogo->quantidade_jogadores != MAX_JOGADORES)
        return -1;

    if (jogo->jogadores[0].quantidade_cartas == MAX_CARTAS ||
        jogo->jogadores[1].quantidade_cartas == MAX_CARTAS)
        return 1;

    return 0;
}

Jogador *determinarVencedorJogo(Jogo *jogo)
{
    if (verificarFimJogo(jogo) != 1)
        return NULL;

    for (int i = 0; i < MAX_JOGADORES; i++)
        if (jogo->jogadores[i].quantidade_cartas == MAX_CARTAS)
            return &jogo->jogadores[i];

    return NULL;
}
