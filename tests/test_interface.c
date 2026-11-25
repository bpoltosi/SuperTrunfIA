#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "interface.h"

int main(void)
{
    Jogador jogadores[MAX_JOGADORES] = {0};
    snprintf(jogadores[0].nome, sizeof jogadores[0].nome, "Jogador Um");
    snprintf(jogadores[1].nome, sizeof jogadores[1].nome, "Jogador Dois");
    jogadores[0].quantidade_cartas = 12;
    jogadores[1].quantidade_cartas = 22;

    assert(freopen("tests/interface_output.txt", "w", stdout) != NULL);
    exibirResultadoRodada(jogadores[0].nome);
    exibirResultadoRodada(jogadores[1].nome);
    exibirResultadoFinal(&jogadores[1], jogadores, MAX_JOGADORES);
    assert(fflush(stdout) == 0);
    assert(fclose(stdout) == 0);

    FILE *arquivo = fopen("tests/interface_output.txt", "r");
    assert(arquivo != NULL);
    char saida[4096] = {0};
    size_t lidos = fread(saida, 1, sizeof saida - 1, arquivo);
    assert(!ferror(arquivo));
    saida[lidos] = '\0';
    assert(fclose(arquivo) == 0);

    assert(strstr(saida, "Jogador Um venceu a disputa!") != NULL);
    assert(strstr(saida, "Jogador Dois venceu a disputa!") != NULL);
    assert(strstr(saida, "CAMPEAO: Jogador Dois") != NULL);
    assert(strstr(saida, "Cartas de Jogador Um: 12") != NULL);
    assert(strstr(saida, "Cartas de Jogador Dois: 22") != NULL);
    assert(remove("tests/interface_output.txt") == 0);
    fprintf(stderr, "TESTES DA INTERFACE: NOMES E ENCERRAMENTO PASSARAM\n");
    return 0;
}
