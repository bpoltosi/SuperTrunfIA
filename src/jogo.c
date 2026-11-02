#include <string.h>

#include "jogo.h"
#include "interface.h"
#include "util.h"

int inicializarJogo(Jogo *jogo, int quantidade_jogadores)
{
    if (jogo == NULL || quantidade_jogadores < 2 ||
        quantidade_jogadores > MAX_JOGADORES)
        return 0;

    memset(jogo, 0, sizeof(*jogo));
    jogo->quantidade_jogadores = quantidade_jogadores;

    for (int i = 0; i < quantidade_jogadores; i++)
        inicializarJogador(&jogo->jogadores[i], i + 1, "");

    if (!carregarBaralhoCSV(&jogo->baralho, "data/cartas.csv"))
        return 0;

    embaralharBaralho(&jogo->baralho);

    if (!distribuirCartas(&jogo->baralho, jogo->jogadores,
                          quantidade_jogadores))
    {
        liberarBaralho(&jogo->baralho);
        return 0;
    }

    jogo->rodada_atual = 1;
    jogo->jogador_atual = 0;
    jogo->jogo_ativo = 1;
    return 1;
}

void finalizarJogo(Jogo *jogo)
{
    if (jogo == NULL)
        return;

    for (int i = 0; i < jogo->quantidade_jogadores; i++)
        liberarJogador(&jogo->jogadores[i]);

    liberarBaralho(&jogo->baralho);
    limparMonteDisputa(jogo);
    memset(jogo->estados, 0, sizeof(jogo->estados));
    jogo->quantidade_jogadores = 0;
    jogo->jogo_ativo = 0;
}

int executarRodada(Jogo *jogo, Atributo atributo)
{
    (void)jogo;
    (void)atributo;
    return -1;
}

int executarDesempate(Jogo *jogo, Atributo atributo)
{
    (void)jogo;
    (void)atributo;
    return -1;
}

int determinarEmpatados(Jogo *jogo, Atributo atributo, int *empatados)
{
    (void)jogo;
    (void)atributo;
    (void)empatados;
    return 0;
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
    if (jogo == NULL || vencedor < 0 ||
        vencedor >= jogo->quantidade_jogadores)
        return 0;

    for (int i = 0; i < jogo->monte_disputa.quantidade; i++)
    {
        if (!adicionarCarta(&jogo->jogadores[vencedor],
                            jogo->monte_disputa.cartas[i]))
            return 0;
    }

    limparMonteDisputa(jogo);
    return 1;
}

void limparMonteDisputa(Jogo *jogo)
{
    if (jogo != NULL)
        jogo->monte_disputa.quantidade = 0;
}

int obterCartaConfronto(Jogo *jogo, int indice_jogador, Carta *carta,
                        int *adicionar_ao_monte)
{
    (void)jogo;
    (void)indice_jogador;
    (void)carta;
    (void)adicionar_ao_monte;
    return 0;
}

void atualizarParticipantesDesempate(Jogo *jogo, int *empatados,
                                      int quantidade_empatados)
{
    (void)jogo;
    (void)empatados;
    (void)quantidade_empatados;
}

int verificarJogadorDesempate(Jogo *jogo, int indice_jogador)
{
    (void)jogo;
    (void)indice_jogador;
    return 0;
}

int verificarFimJogo(Jogo *jogo)
{
    (void)jogo;
    return 0;
}

Jogador *determinarVencedorJogo(Jogo *jogo)
{
    (void)jogo;
    return NULL;
}
