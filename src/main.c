#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include "jogo.h"
#include "interface.h"
#include "util.h"

static void configurarTerminalUTF8(void)
{
#ifdef _WIN32
    (void)setlocale(LC_ALL, ".UTF-8");
    (void)SetConsoleOutputCP(CP_UTF8);
    (void)SetConsoleCP(CP_UTF8);
#else
    (void)setlocale(LC_ALL, "");
#endif
}
static const char *nomeAtributo(Atributo a)
{
    static const char *nomes[] = {"Raciocinio", "Programacao", "Matematica", "Conhecimento"};
    return a >= RACIOCINIO && a < QUANTIDADE_ATRIBUTOS ? nomes[a] : "?";
}
static Atributo atributoAleatorio(void) { return (Atributo)(rand() % QUANTIDADE_ATRIBUTOS); }
static int pausarOuSimular(void)
{
    char linha[32];
    for (;;)
    {
        printf("[ENTER] Proxima rodada | [P] Simular ate o fim: ");
        if (!fgets(linha, sizeof linha, stdin))
            return -1;
        size_t tamanho = strlen(linha);
        if (tamanho > 0 && linha[tamanho - 1] != '\n' && !feof(stdin))
        {
            int caractere = getchar();
            if (caractere != '\n' && caractere != EOF)
            {
                while (caractere != '\n' && caractere != EOF)
                    caractere = getchar();
                puts("Entrada muito longa. Tente novamente.");
                continue;
            }
        }
        if (tamanho > 0 && linha[tamanho - 1] == '\n')
            linha[tamanho - 1] = '\0';
        else if (tamanho > 0 && linha[tamanho - 1] == '\r')
            linha[tamanho - 1] = '\0';
        if (linha[0] == 'p' || linha[0] == 'P')
        {
            if (linha[1] == '\0')
            {
                limparTerminal();
                return 1;
            }
        }
        else if (linha[0] == '\0')
        {
            limparTerminal();
            return 0;
        }
        puts("Opcao invalida.");
    }
}
static void mostrarConfronto(Jogo *jogo, Atributo atributo, int desempate)
{
    printf("\n===== %s | %s =====\n", desempate ? "DESEMPATE" : "RODADA", nomeAtributo(atributo));
    for (int i = 0; i < 2; ++i)
    {
        Carta carta;
        int adiciona;
        if (!obterCartaConfronto(jogo, i, &carta, &adiciona))
        {
            printf("Jogador %d sem carta disponivel.\n", i + 1);
            continue;
        }
        printf("\n%s | cartas na mao: %d\n", jogo->jogadores[i].nome, jogo->jogadores[i].quantidade_cartas);
        exibirCarta(carta);
        exibirAtributos(carta);
        printf("Atributo escolhido: %s = %d\n\n", nomeAtributo(atributo), obterPontuacao(carta, atributo));
        if (i == 0)
            puts("============================================================");
    }
}
static int sortearPrimeiroJogador(Jogo *jogo)
{
    int escolha;
    int resultadoSorteio;
    int jogadorEscolhedor;

    printf("\nSorteio inicial: %s, escolha 1 (PAR) ou 2 (IMPAR).\n",
           jogo->jogadores[0].nome);

    /* O sorteio inicial e sempre uma escolha manual. */
    escolha = lerInteiro(1, 2);
    if (escolha < 1 || escolha > 2)
        return -1;

    /* A entrada e o resultado usam a mesma codificacao: 1=PAR, 2=IMPAR. */
    resultadoSorteio = rand() % 2 + 1;
    printf("Escolha: %s; resultado do sorteio: %d (%s).\n",
           escolha == 1 ? "PAR" : "IMPAR",
           resultadoSorteio,
           resultadoSorteio == 1 ? "PAR" : "IMPAR");

    jogadorEscolhedor = determinarVencedorSorteio(escolha, resultadoSorteio);
    if (jogadorEscolhedor < 0)
        return -1;

    printf("%s venceu o sorteio e escolhe o primeiro atributo.\n",
           jogo->jogadores[jogadorEscolhedor].nome);
    return jogadorEscolhedor;
}
static int executarCicloDesempate(Jogo *jogo, int jogadorEscolhedor, int simulacao)
{
    int numeroDesempate = 1;

    while (verificarFimJogo(jogo) == 0 &&
           verificarJogadorDesempate(jogo, 0) &&
           verificarJogadorDesempate(jogo, 1))
    {
        int participantes[2];
        int resultado;
        Atributo atributo;

        printf("\nDesempate %d — escolha de %s\n",
               numeroDesempate++, jogo->jogadores[jogadorEscolhedor].nome);

        atributo = simulacao ? atributoAleatorio() : solicitarAtributo();
        if (atributo < RACIOCINIO || atributo >= QUANTIDADE_ATRIBUTOS)
            return 0;

        mostrarConfronto(jogo, atributo, 1);
        resultado = determinarEmpatados(jogo, atributo, participantes);
        if (resultado < 1)
        {
            exibirErro("Desempate invalido.");
            return 0;
        }

        if (!executarDesempate(jogo, atributo))
        {
            exibirErro("Falha no desempate.");
            return 0;
        }

        exibirResultadoRodada(resultado == 1
                                  ? jogo->jogadores[participantes[0]].nome
                                  : NULL);

        if (resultado == 1)
            break;

        puts("Novo empate: as cartas reveladas sao reutilizadas; escolha outro atributo.");
    }

    return 1;
}
static int processarRodada(Jogo *jogo, int jogadorEscolhedor, int simulacao)
{
    Atributo atributo;
    int participantes[2];
    int resultado;

    printf("\n\nRODADA %d | %s deve escolher o atributo\n\n",
           jogo->rodada_atual, jogo->jogadores[jogadorEscolhedor].nome);

    atributo = simulacao ? atributoAleatorio() : solicitarAtributo();
    if (atributo < RACIOCINIO || atributo >= QUANTIDADE_ATRIBUTOS)
        return 0;

    mostrarConfronto(jogo, atributo, 0);
    resultado = determinarEmpatados(jogo, atributo, participantes);
    if (resultado < 1)
    {
        exibirErro("Confronto invalido.");
        return 0;
    }

    exibirResultadoRodada(resultado == 1
                              ? jogo->jogadores[participantes[0]].nome
                              : NULL);

    if (!executarRodada(jogo, atributo))
    {
        exibirErro("Falha ao processar rodada.");
        return 0;
    }

    if (resultado == 2 &&
        !executarCicloDesempate(jogo, jogadorEscolhedor, simulacao))
        return 0;

    return 1;
}
static int executarPartida(Jogo *jogo, int simulacao)
{
    int seletor = sortearPrimeiroJogador(jogo);
    int estadoJogo;

    if (seletor < 0)
        return 0;

    /* A primeira rodada e manual; a simulacao so pode ser ativada na pausa. */
    estadoJogo = verificarFimJogo(jogo);
    if (estadoJogo < 0)
    {
        exibirErro("Estado inconsistente.");
        return 0;
    }

    while (estadoJogo == 0)
    {
        int controle;

        if (!processarRodada(jogo, seletor, simulacao))
            return 0;

        estadoJogo = verificarFimJogo(jogo);
        if (estadoJogo < 0)
        {
            exibirErro("Estado inconsistente.");
            return 0;
        }
        if (estadoJogo == 1)
            break;

        printf("\nRodada atual: %d\n", jogo->rodada_atual);
        printf("Contagem de Cartas: %s=%d | %s=%d\n\n",
               jogo->jogadores[0].nome,
               jogo->jogadores[0].quantidade_cartas,
               jogo->jogadores[1].nome,
               jogo->jogadores[1].quantidade_cartas);

        seletor = jogo->jogador_atual;
        if (simulacao)
            continue;

        controle = pausarOuSimular();
        if (controle < 0)
            return 0;

        if (controle == 1)
        {
            simulacao = 1;
            puts("SIMULACAO AUTOMATICA ATIVADA: ate o fim da partida.");
        }
    }

    exibirResultadoFinal(
        determinarVencedorJogo(jogo),
        jogo->jogadores,
        jogo->quantidade_jogadores);
    return estadoJogo == 1;
}
int main(void)
{
    configurarTerminalUTF8();
    inicializarAleatorio();
    for (;;)
    {
        exibirMenu();
        int opcao = lerInteiro(0, 2);
        if (opcao < 0 || opcao == 0)
            break;
        if (opcao == 2)
        {
            exibirRegras();
            continue;
        }
        Jogo jogo;
        if (!inicializarJogo(&jogo, solicitarQuantidadeJogadores()))
        {
            exibirErro("Nao foi possivel carregar ou distribuir o baralho.");
            continue;
        }
        solicitarNomesJogadores(jogo.jogadores, MAX_JOGADORES);
        executarPartida(&jogo, 0);
        finalizarJogo(&jogo);
    }
    puts("Obrigado por jogar SuperTrunfIA!");
    return 0;
}
