#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "util.h"

void limparBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int lerInteiro(int minimo, int maximo)
{
    char linha[128], *fim; long valor;
    for (;;) {
        if (!fgets(linha, sizeof linha, stdin)) return -1;
        valor = strtol(linha, &fim, 10);
        while (*fim == ' ' || *fim == '\t' || *fim == '\r' || *fim == '\n') ++fim;
        if (fim != linha && *fim == '\0' && valor >= minimo && valor <= maximo) return (int)valor;
        printf("Entrada invalida. Informe um numero entre %d e %d: ", minimo, maximo);
    }
}

void lerString(char *destino, int tamanho)
{
    if (!destino || tamanho <= 0) return;
    if (!fgets(destino, tamanho, stdin)) { destino[0] = '\0'; return; }
    size_t n = strlen(destino);
    if (n && destino[n-1] == '\n') destino[n-1] = '\0';
    else limparBuffer();
}

void inicializarAleatorio(void)
{
    srand((unsigned)time(NULL));
}
