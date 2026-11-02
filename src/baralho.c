#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include "baralho.h"

#define TAMANHO_LINHA_CSV 1024
#define QUANTIDADE_CAMPOS_CSV 10
#define TAMANHO_CAMPO_CSV 256

static int separarCamposCSV(char *linha, char campos[QUANTIDADE_CAMPOS_CSV][TAMANHO_CAMPO_CSV])
{
    int campo = 0, posicao = 0, entre_aspas = 0;
    for (int i = 0; linha[i] != '\0'; i++) {
        char caractere = linha[i];
        if (caractere == '"') {
            if (entre_aspas && linha[i + 1] == '"') {
                if (posicao >= TAMANHO_CAMPO_CSV - 1) return 0;
                campos[campo][posicao++] = '"';
                i++;
            } else entre_aspas = !entre_aspas;
        } else if (caractere == ',' && !entre_aspas) {
            if (campo >= QUANTIDADE_CAMPOS_CSV - 1) return 0;
            campos[campo][posicao] = '\0';
            campo++;
            posicao = 0;
        } else if (caractere != '\r' && caractere != '\n') {
            if (posicao >= TAMANHO_CAMPO_CSV - 1) return 0;
            campos[campo][posicao++] = caractere;
        }
    }
    if (entre_aspas) return 0;
    campos[campo][posicao] = '\0';
    return campo == QUANTIDADE_CAMPOS_CSV - 1;
}

static int converterInteiro(const char *texto, int *valor)
{
    char *fim;
    long convertido;
    if (texto == NULL || valor == NULL || texto[0] == '\0') return 0;
    errno = 0;
    convertido = strtol(texto, &fim, 10);
    if (errno == ERANGE || texto == fim || *fim != '\0' ||
        convertido < INT_MIN || convertido > INT_MAX) return 0;
    *valor = (int)convertido;
    return 1;
}

static int converterClasse(const char *texto, ClasseCarta *classe)
{
    if (texto == NULL || classe == NULL) return 0;
    if (strcmp(texto, "A") == 0) *classe = CLASSE_A;
    else if (strcmp(texto, "B") == 0) *classe = CLASSE_B;
    else if (strcmp(texto, "C") == 0) *classe = CLASSE_C;
    else if (strcmp(texto, "D") == 0) *classe = CLASSE_D;
    else return 0;
    return 1;
}

int carregarBaralhoCSV(Baralho *baralho, const char *caminho)
{
    FILE *arquivo;
    char linha[TAMANHO_LINHA_CSV];
    char campos[QUANTIDADE_CAMPOS_CSV][TAMANHO_CAMPO_CSV];
    int primeira_linha = 1, quantidade_super_trunfo = 0;

    if (baralho == NULL || caminho == NULL) return 0;
    baralho->quantidade = 0;
    arquivo = fopen(caminho, "r");
    if (arquivo == NULL) return 0;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        Carta carta = {0};
        if (primeira_linha) { primeira_linha = 0; continue; }

        if (!separarCamposCSV(linha, campos) ||
            !converterInteiro(campos[0], &carta.id) ||
            !converterClasse(campos[4], &carta.classe) ||
            !converterInteiro(campos[5], &carta.raciocinio) ||
            !converterInteiro(campos[6], &carta.programacao) ||
            !converterInteiro(campos[7], &carta.matematica) ||
            !converterInteiro(campos[8], &carta.conhecimento) ||
            baralho->quantidade >= MAX_CARTAS) {
            fclose(arquivo); baralho->quantidade = 0; return 0;
        }

        if (strcmp(campos[9], "modelo") != 0 &&
            strcmp(campos[9], "super_trunfo") != 0) {
            fclose(arquivo); baralho->quantidade = 0; return 0;
        }

        strncpy(carta.empresa, campos[1], sizeof(carta.empresa) - 1);
        strncpy(carta.modelo, campos[2], sizeof(carta.modelo) - 1);
        strncpy(carta.caracteristicas, campos[3], sizeof(carta.caracteristicas) - 1);
        carta.super_trunfo = strcmp(campos[9], "super_trunfo") == 0;

        if (!validarCarta(&carta) ||
            (carta.super_trunfo && carta.classe != CLASSE_A)) {
            fclose(arquivo); baralho->quantidade = 0; return 0;
        }
        for (int i = 0; i < baralho->quantidade; i++) {
            if (baralho->cartas[i].id == carta.id) {
                fclose(arquivo); baralho->quantidade = 0; return 0;
            }
        }
        if (carta.super_trunfo) quantidade_super_trunfo++;
        baralho->cartas[baralho->quantidade++] = carta;
    }

    fclose(arquivo);
    if (baralho->quantidade != MAX_CARTAS || quantidade_super_trunfo != 1) {
        baralho->quantidade = 0;
        return 0;
    }
    return 1;
}

void embaralharBaralho(Baralho *baralho)
{
    if (baralho == NULL || baralho->quantidade <= 1) return;
    for (int i = baralho->quantidade - 1; i > 0; i--) {
        int indice = rand() % (i + 1);
        Carta temporaria = baralho->cartas[i];
        baralho->cartas[i] = baralho->cartas[indice];
        baralho->cartas[indice] = temporaria;
    }
}

int distribuirCartas(Baralho *baralho, Jogador *jogadores, int quantidade_jogadores)
{
    if (baralho == NULL || jogadores == NULL ||
        quantidade_jogadores != MAX_JOGADORES ||
        baralho->quantidade != MAX_CARTAS ||
        jogadores[0].quantidade_cartas != 0 ||
        jogadores[1].quantidade_cartas != 0) return 0;

    for (int i = 0; i < baralho->quantidade; i++) {
        int indice = i % quantidade_jogadores;
        if (!adicionarCarta(&jogadores[indice], baralho->cartas[i])) {
            jogadores[0].quantidade_cartas = 0;
            jogadores[1].quantidade_cartas = 0;
            return 0;
        }
    }
    baralho->quantidade = 0;
    return 1;
}

void liberarBaralho(Baralho *baralho)
{
    if (baralho != NULL) baralho->quantidade = 0;
}
