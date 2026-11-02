#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "baralho.h"

#define TAMANHO_LINHA_CSV 1024
#define QUANTIDADE_CAMPOS_CSV 9
#define TAMANHO_CAMPO_CSV 256

static int separarCamposCSV(char *linha, char campos[QUANTIDADE_CAMPOS_CSV][TAMANHO_CAMPO_CSV])
{
    int campo = 0;
    int posicao = 0;
    int entre_aspas = 0;

    for (int i = 0; linha[i] != '\0'; i++)
    {
        char caractere = linha[i];

        if (caractere == '"')
        {
            if (entre_aspas && linha[i + 1] == '"')
            {
                if (posicao >= TAMANHO_CAMPO_CSV - 1)
                    return 0;
                campos[campo][posicao++] = '"';
                i++;
            }
            else
                entre_aspas = !entre_aspas;
        }
        else if (caractere == ',' && !entre_aspas)
        {
            if (campo >= QUANTIDADE_CAMPOS_CSV - 1)
                return 0;
            campos[campo][posicao] = '\0';
            campo++;
            posicao = 0;
        }
        else if (caractere != '\r' && caractere != '\n')
        {
            if (posicao >= TAMANHO_CAMPO_CSV - 1)
                return 0;
            campos[campo][posicao++] = caractere;
        }
    }

    if (entre_aspas)
        return 0;

    campos[campo][posicao] = '\0';
    return campo == QUANTIDADE_CAMPOS_CSV - 1;
}

static int converterInteiro(const char *texto, int *valor)
{
    char *fim;
    long convertido = strtol(texto, &fim, 10);

    if (texto == fim || *fim != '\0')
        return 0;

    *valor = (int)convertido;
    return 1;
}

int carregarBaralhoCSV(Baralho *baralho, const char *caminho)
{
    FILE *arquivo;
    char linha[TAMANHO_LINHA_CSV];
    char campos[QUANTIDADE_CAMPOS_CSV][TAMANHO_CAMPO_CSV];
    int primeira_linha = 1;

    if (baralho == NULL || caminho == NULL)
        return 0;

    baralho->quantidade = 0;
    arquivo = fopen(caminho, "r");
    if (arquivo == NULL)
        return 0;

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        Carta carta = {0};

        if (primeira_linha)
        {
            primeira_linha = 0;
            continue;
        }

        if (!separarCamposCSV(linha, campos) ||
            !converterInteiro(campos[0], &carta.id) ||
            !converterInteiro(campos[4], &carta.raciocinio) ||
            !converterInteiro(campos[5], &carta.programacao) ||
            !converterInteiro(campos[6], &carta.matematica) ||
            !converterInteiro(campos[7], &carta.conhecimento) ||
            baralho->quantidade >= MAX_CARTAS)
        {
            fclose(arquivo);
            baralho->quantidade = 0;
            return 0;
        }

        strncpy(carta.empresa, campos[1], sizeof(carta.empresa) - 1);
        strncpy(carta.modelo, campos[2], sizeof(carta.modelo) - 1);
        strncpy(carta.caracteristicas, campos[3],
                sizeof(carta.caracteristicas) - 1);
        carta.super_trunfo = strcmp(campos[8], "super_trunfo") == 0;

        baralho->cartas[baralho->quantidade++] = carta;
    }

    fclose(arquivo);
    return baralho->quantidade == MAX_CARTAS;
}

void embaralharBaralho(Baralho *baralho)
{
    if (baralho == NULL || baralho->quantidade <= 1)
        return;

    for (int i = baralho->quantidade - 1; i > 0; i--)
    {
        int indice = rand() % (i + 1);
        Carta temporaria = baralho->cartas[i];
        baralho->cartas[i] = baralho->cartas[indice];
        baralho->cartas[indice] = temporaria;
    }
}

int distribuirCartas(Baralho *baralho, Jogador *jogadores, int quantidade_jogadores)
{
    if (baralho == NULL || jogadores == NULL ||
        quantidade_jogadores < 2 || quantidade_jogadores > MAX_JOGADORES ||
        baralho->quantidade != MAX_CARTAS ||
        baralho->quantidade % quantidade_jogadores != 0)
        return 0;

    for (int i = 0; i < quantidade_jogadores; i++)
        jogadores[i].quantidade_cartas = 0;

    for (int i = 0; i < baralho->quantidade; i++)
    {
        int indice_jogador = i % quantidade_jogadores;
        if (!adicionarCarta(&jogadores[indice_jogador], baralho->cartas[i]))
        {
            for (int j = 0; j < quantidade_jogadores; j++)
                jogadores[j].quantidade_cartas = 0;
            return 0;
        }
    }

    baralho->quantidade = 0;
    return 1;
}

void liberarBaralho(Baralho *baralho)
{
    if (baralho != NULL)
        baralho->quantidade = 0;
}
