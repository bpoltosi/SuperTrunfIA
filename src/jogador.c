#include <stdlib.h>
#include <string.h>

#include "jogador.h"

#define CAPACIDADE_INICIAL_CARTAS 4

void inicializarJogador(Jogador *jogador, int id, const char *nome)
{
    if (jogador == NULL)
        return;

    jogador->id = id;
    jogador->cartas = NULL;
    jogador->quantidade_cartas = 0;
    jogador->capacidade_cartas = 0;

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
    Carta *novo_vetor;
    int nova_capacidade;

    if (jogador == NULL)
        return 0;

    if (jogador->quantidade_cartas == jogador->capacidade_cartas)
    {
        nova_capacidade = (jogador->capacidade_cartas == 0)
                              ? CAPACIDADE_INICIAL_CARTAS
                              : jogador->capacidade_cartas * 2;

        novo_vetor = realloc(jogador->cartas,
                             (size_t)nova_capacidade * sizeof(Carta));

        if (novo_vetor == NULL)
            return 0;

        jogador->cartas = novo_vetor;
        jogador->capacidade_cartas = nova_capacidade;
    }

    jogador->cartas[jogador->quantidade_cartas] = carta;
    jogador->quantidade_cartas++;

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
        jogador->quantidade_cartas <= 0 || jogador->cartas == NULL)
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

    free(jogador->cartas);

    jogador->cartas = NULL;
    jogador->quantidade_cartas = 0;
    jogador->capacidade_cartas = 0;
}
