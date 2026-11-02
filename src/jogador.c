#include <string.h>
#include "jogador.h"

void inicializarJogador(Jogador *jogador, int id, const char *nome)
{
    if (jogador == NULL)
        return;

    jogador->id = id;
    jogador->quantidade_cartas = 0;

    if (nome == NULL)
        jogador->nome[0] = '\0';
    else
    {
        strncpy(jogador->nome, nome, sizeof(jogador->nome) - 1);
        jogador->nome[sizeof(jogador->nome) - 1] = '\0';
    }
}

int adicionarCarta(Jogador *jogador, Carta carta)
{
    if (jogador == NULL || jogador->quantidade_cartas < 0 ||
        jogador->quantidade_cartas >= MAX_CARTAS)
        return 0;

    jogador->cartas[jogador->quantidade_cartas++] = carta;
    return 1;
}

int removerCarta(Jogador *jogador, int indice)
{
    if (jogador == NULL || indice < 0 ||
        indice >= jogador->quantidade_cartas)
        return 0;

    if (indice < jogador->quantidade_cartas - 1)
    {
        memmove(&jogador->cartas[indice],
                &jogador->cartas[indice + 1],
                (size_t)(jogador->quantidade_cartas - indice - 1) *
                    sizeof(Carta));
    }

    jogador->quantidade_cartas--;
    return 1;
}

int obterCartaTopo(const Jogador *jogador, Carta *carta)
{
    if (jogador == NULL || carta == NULL ||
        jogador->quantidade_cartas <= 0)
        return 0;

    *carta = jogador->cartas[0];
    return 1;
}

int retirarCartaTopo(Jogador *jogador, Carta *carta)
{
    if (!obterCartaTopo(jogador, carta))
        return 0;

    return removerCarta(jogador, 0);
}

void liberarJogador(Jogador *jogador)
{
    if (jogador == NULL)
        return;

    jogador->quantidade_cartas = 0;
    jogador->nome[0] = '\0';
}
