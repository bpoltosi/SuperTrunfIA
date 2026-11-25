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
    static const char *nomes[] = {"Raciocinio","Programacao","Matematica","Conhecimento"};
    return a >= RACIOCINIO && a < QUANTIDADE_ATRIBUTOS ? nomes[a] : "?";
}
static Atributo atributoAleatorio(void) { return (Atributo)(rand() % QUANTIDADE_ATRIBUTOS); }
static int pausarOuSimular(void)
{
    char linha[32];
    for (;;) {
        printf("[ENTER] Proxima rodada | [P] Simular ate o fim: ");
        if (!fgets(linha, sizeof linha, stdin)) return -1;
        if (linha[0] == 'p' || linha[0] == 'P') { limparTerminal(); return 1; }
        if (linha[0] == '\n' || linha[0] == '\r' || linha[0] == '\0') { limparTerminal(); return 0; }
        puts("Opcao invalida.");
    }
}
static void mostrarConfronto(Jogo *jogo, Atributo atributo, int desempate)
{
    printf("\n===== %s | %s =====\n", desempate ? "DESEMPATE" : "RODADA", nomeAtributo(atributo));
    for (int i=0; i<2; ++i) {
        Carta carta;
        int adiciona;
        if (!obterCartaConfronto(jogo, i, &carta, &adiciona)) {
            printf("Jogador %d sem carta disponivel.\n",i+1); continue;
        }
        printf("\n%s | cartas na mao: %d\n", jogo->jogadores[i].nome, jogo->jogadores[i].quantidade_cartas);
        exibirCarta(carta); exibirAtributos(carta);
        printf("Atributo escolhido: %s = %d\n", nomeAtributo(atributo), obterPontuacao(carta, atributo));
    }
}
static int executarPartida(Jogo *jogo, int simulacao)
{
    int paridade, sorteio, seletor;
    printf("\nSorteio inicial: %s, escolha 1 (PAR) ou 2 (IMPAR).\n", jogo->jogadores[0].nome);
    paridade = simulacao ? (rand()%2+1) : lerInteiro(1,2);
    if (paridade < 1 || paridade > 2) return 0;
    /* O sorteio usa a mesma codificacao da entrada: 1 = PAR; 2 = IMPAR. */
    sorteio = rand()%2+1;
    printf("Escolha: %s; resultado do sorteio: %d (%s).\n",
           paridade==1?"PAR":"IMPAR", sorteio, sorteio==1?"PAR":"IMPAR");
    seletor = determinarVencedorSorteio(paridade, sorteio);
    if (seletor < 0) return 0;
    printf("%s venceu o sorteio e escolhe o primeiro atributo.\n", jogo->jogadores[seletor].nome);
    /* A primeira rodada é obrigatoriamente manual; simulação só é oferecida após ela. */
    while (verificarFimJogo(jogo)==0) {
        int escolha_desempate = seletor;
        printf("\n\nRODADA %d | %s deve escolher o atributo\n\n",
               jogo->rodada_atual, jogo->jogadores[seletor].nome);
        Atributo atributo = simulacao ? atributoAleatorio() : solicitarAtributo();
        if (atributo < RACIOCINIO || atributo >= QUANTIDADE_ATRIBUTOS) return 0;
        mostrarConfronto(jogo, atributo, 0);
        int participantes[2];
        int resultado = determinarEmpatados(jogo,atributo,participantes);
        if (resultado < 1) { exibirErro("Confronto invalido."); return 0; }
        exibirResultadoRodada(resultado == 1 ? participantes[0] : -1);
        if (!executarRodada(jogo,atributo)) { exibirErro("Falha ao processar rodada."); return 0; }
        if (resultado == 2) {
            int desempate=1;
            while (verificarJogadorDesempate(jogo,0) && verificarJogadorDesempate(jogo,1)) {
                printf("\nDesempate %d — escolha de %s\n",
                       desempate++, jogo->jogadores[escolha_desempate].nome);
                Atributo attr = simulacao ? atributoAleatorio() : solicitarAtributo();
                if (attr < RACIOCINIO || attr >= QUANTIDADE_ATRIBUTOS) return 0;
                mostrarConfronto(jogo,attr,1);
                int participantesTie[2];
                int tieResult = determinarEmpatados(jogo,attr,participantesTie);
                if (tieResult < 1) { exibirErro("Desempate invalido."); return 0; }
                if (!executarDesempate(jogo,attr)) { exibirErro("Falha no desempate."); return 0; }
                exibirResultadoRodada(tieResult == 1 ? participantesTie[0] : -1);
                if (tieResult == 1) break;
                puts("Novo empate: as cartas reveladas sao reutilizadas; escolha outro atributo.");
            }
        }
        int fim=verificarFimJogo(jogo);
        if (fim < 0) { exibirErro("Estado inconsistente."); return 0; }
        if (fim==1) break;
        printf("\nContagem: %s=%d | %s=%d\n",jogo->jogadores[0].nome,jogo->jogadores[0].quantidade_cartas,jogo->jogadores[1].nome,jogo->jogadores[1].quantidade_cartas);
        seletor = jogo->jogador_atual;
        if (!simulacao) {
            int controle=pausarOuSimular();
            if (controle < 0) return 0;
            if (controle == 1) {
                simulacao=1;
                puts("SIMULACAO AUTOMATICA ATIVADA: ate o fim da partida.");
            }
        }
    }
    Jogador *vencedor=determinarVencedorJogo(jogo);
    if (vencedor) exibirResultadoFinal(*vencedor);
    return vencedor != NULL;
}
int main(void)
{
    configurarTerminalUTF8();
    inicializarAleatorio();
    for (;;) {
        exibirMenu();
        int opcao=lerInteiro(0,2);
        if (opcao < 0 || opcao==0) break;
        if (opcao==2) { exibirRegras(); continue; }
        Jogo jogo;
        if (!inicializarJogo(&jogo,solicitarQuantidadeJogadores())) {
            exibirErro("Nao foi possivel carregar ou distribuir o baralho."); continue;
        }
        solicitarNomesJogadores(jogo.jogadores,MAX_JOGADORES);
        executarPartida(&jogo,0);
        finalizarJogo(&jogo);
    }
    puts("Obrigado por jogar SuperTrunfIA!");
    return 0;
}
