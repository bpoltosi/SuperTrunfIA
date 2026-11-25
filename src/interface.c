#include <stdio.h>
#include "interface.h"
#include "util.h"

void exibirMenu(void)
{
    puts("\n============================================");
    puts("             SUPERTRUNFIA");
    puts("============================================");
    puts("\n[1] Iniciar partida\n");
    puts("[2] Regras\n");
    puts("[0] Sair\n");
    printf("Opcao: ");
}
void exibirRegras(void)
{
    puts("\nREGRAS:");
    puts("- Dois jogadores, 34 cartas distribuídas igualmente.");
    puts("- O jogador que escolhe o atributo vence se tiver a maior pontuação.");
    puts("- Super Trunfo vence cartas B/C/D; contra classe A compara atributo.");
    puts("- Empates acumulam cartas no monte da mesa e são resolvidos entre empatados.");
    puts("- O vencedor recebe o monte de disputa; ganha a partida com 34 cartas.");
    puts("- A partida começa manual. P ativa simulação nas pausas.");
}
int solicitarQuantidadeJogadores(void)
{
    puts("A V1 suporta exatamente 2 jogadores.");
    return 2;
}
void solicitarNomesJogadores(Jogador *jogadores, int quantidade)
{
    if (!jogadores || quantidade < 1 || quantidade > MAX_JOGADORES) return;
    for (int i = 0; i < quantidade; ++i) {
        printf("Nome do Jogador %d: ", i + 1);
        lerString(jogadores[i].nome, (int)sizeof jogadores[i].nome);
        if (!jogadores[i].nome[0]) snprintf(jogadores[i].nome, sizeof jogadores[i].nome, "Jogador %d", i+1);
    }
}
void exibirCarta(Carta carta)
{
    printf("\n%s (%s) | Classe %c%s\n\n", carta.modelo, carta.empresa,
           'A' + carta.classe, carta.super_trunfo ? " | SUPER TRUNFO" : "");
}
void exibirAtributos(Carta carta)
{
    printf("Raciocinio: %d | Programacao: %d | Matematica: %d | Conhecimento: %d\n\n",
           carta.raciocinio, carta.programacao, carta.matematica, carta.conhecimento);
}
Atributo solicitarAtributo(void)
{
    puts("[1] Raciocinio [2] Programacao [3] Matematica [4] Conhecimento");
    printf("Atributo: ");
    int escolha=lerInteiro(1,4);
    return escolha < 1 ? (Atributo)-1 : (Atributo)(escolha-1);
}
void exibirResultadoRodada(int vencedor)
{
    if (vencedor == 0) puts("Jogador 1 venceu a disputa!");
    else if (vencedor == 1) puts("Jogador 2 venceu a disputa!");
    else puts("Empate! Inicia desempate.");
}
void exibirResultadoFinal(Jogador jogador)
{
    printf("\nCAMPEAO: %s | Total de cartas: %d\n", jogador.nome, jogador.quantidade_cartas);
}
void exibirErro(const char *mensagem)
{
    if (mensagem) fprintf(stderr, "Erro: %s\n", mensagem);
}
