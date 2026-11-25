#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include "util.h"

void limparTerminal(void)
{
#ifdef _WIN32
    (void)system("cls");
#else
    fputs("\033[2J\033[H", stdout);
    fflush(stdout);
#endif
}

void limparBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int lerInteiro(int minimo, int maximo)
{
    if (minimo > maximo) return -1;
    char linha[128], *fim;
    long valor;

    for (;;) {
        if (!fgets(linha, sizeof linha, stdin)) return -1;

        size_t tamanho = strlen(linha);
        if (tamanho > 0 && linha[tamanho - 1] != '\n' && !feof(stdin)) {
            int caractere = getchar();
            if (caractere != '\n' && caractere != EOF) {
                while (caractere != '\n' && caractere != EOF) caractere = getchar();
                puts("Entrada muito longa. Tente novamente.");
                continue;
            }
        }

        errno = 0;
        valor = strtol(linha, &fim, 10);
        while (*fim == ' ' || *fim == '\t' || *fim == '\r' || *fim == '\n') ++fim;
        if (fim != linha && *fim == '\0' && errno != ERANGE &&
            valor >= minimo && valor <= maximo)
            return (int)valor;

        printf("Entrada invalida. Informe um numero entre %d e %d: ", minimo, maximo);
    }
}

/* 1 = linha lida; 0 = EOF/argumento invalido; -1 = entrada excedeu o buffer. */
int lerString(char *destino, int tamanho)
{
    if (!destino || tamanho <= 0) return 0;
    destino[0] = '\0';
    if (!fgets(destino, tamanho, stdin)) return 0;

    size_t n = strlen(destino);
    if (n > 0 && destino[n - 1] == '\n') {
        destino[n - 1] = '\0';
        return 1;
    }

    int caractere = getchar();
    if (caractere == '\n' || caractere == EOF) return 1;

    while (caractere != '\n' && caractere != EOF) caractere = getchar();
    destino[0] = '\0';
    return -1;
}

int determinarVencedorSorteio(int escolha, int resultado)
{
    if ((escolha != 1 && escolha != 2) || (resultado != 1 && resultado != 2))
        return -1;
    return escolha == resultado ? 0 : 1;
}

void inicializarAleatorio(void)
{
    srand((unsigned)time(NULL));
}
