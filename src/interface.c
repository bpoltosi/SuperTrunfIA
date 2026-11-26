#include <stdio.h>
#include "interface.h"
#include "util.h"

static void exibirSeparador(void)
{
    puts("============================================================");
}

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
    puts("- Dois jogadores, 34 cartas distribuidas igualmente.");
    puts("- O jogador que escolhe o atributo vence se tiver a maior pontuacao.");
    puts("- Super Trunfo vence cartas B/C/D; contra classe A compara atributo.");
    puts("- Empates acumulam cartas no monte da mesa e sao resolvidos entre empatados.");
    puts("- O vencedor recebe o monte de disputa; ganha a partida com 34 cartas.");
    puts("- A partida comeca manual. P ativa simulacao nas pausas.");
}

int solicitarQuantidadeJogadores(void)
{
    /* A V1 mantem dois participantes sem repetir uma mensagem redundante. */
    return 2;
}

void solicitarNomesJogadores(Jogador *jogadores, int quantidade)
{
    if (!jogadores || quantidade < 1 || quantidade > MAX_JOGADORES)
        return;
    for (int i = 0; i < quantidade; ++i)
    {
        printf("Nome do Jogador %d: ", i + 1);
        int leitura;
        do
        {
            leitura = lerString(jogadores[i].nome, (int)sizeof jogadores[i].nome);
            if (leitura < 0)
                puts("Nome muito longo (maximo 49 caracteres). Tente novamente.");
        } while (leitura < 0);
        if (!jogadores[i].nome[0])
            snprintf(jogadores[i].nome, sizeof jogadores[i].nome, "Jogador %d", i + 1);
        if (leitura == 0)
            return;
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
    int escolha = lerInteiro(1, 4);
    return escolha < 1 ? (Atributo)-1 : (Atributo)(escolha - 1);
}

void exibirResultadoRodada(const char *nome_vencedor)
{
    exibirSeparador();
    if (nome_vencedor && nome_vencedor[0])
        printf("\n%s venceu a disputa!\n", nome_vencedor);
    else
        puts("Empate! Inicia desempate.");
}

void exibirResultadoFinal(const Jogador *vencedor, const Jogador jogadores[], int quantidade)
{
    if (!jogadores || quantidade != MAX_JOGADORES)
        return;

    puts("\n");
    exibirSeparador();
    puts("                         FIM DE JOGO");
    exibirSeparador();
    if (vencedor)
        printf("                         CAMPEAO: %s\n", vencedor->nome);
    else
        puts("                 PARTIDA ENCERRADA EM EMPATE");
    exibirSeparador();
    printf("Cartas de %s: %d\n", jogadores[0].nome, jogadores[0].quantidade_cartas);
    printf("Cartas de %s: %d\n", jogadores[1].nome, jogadores[1].quantidade_cartas);
    exibirSeparador();
}

void exibirErro(const char *mensagem)
{
    if (mensagem)
        fprintf(stderr, "Erro: %s\n", mensagem);
}
