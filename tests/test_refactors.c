#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "baralho.h"
#include "carta.h"
#include "jogo.h"

static Carta criarCarta(int id, ClasseCarta classe, int raciocinio)
{
    Carta carta = {0};
    carta.id = id;
    strcpy(carta.empresa, "Empresa");
    strcpy(carta.modelo, "Modelo");
    strcpy(carta.caracteristicas, "Caracteristica");
    carta.classe = classe;
    carta.raciocinio = raciocinio;
    carta.programacao = 50;
    carta.matematica = 50;
    carta.conhecimento = 50;
    return carta;
}

static void preencherJogo(Jogo *jogo, int primeiro, int segundo, int monte)
{
    int proximoId = 1;
    memset(jogo, 0, sizeof(*jogo));
    jogo->quantidade_jogadores = MAX_JOGADORES;
    jogo->jogo_ativo = 1;
    jogo->jogadores[0].quantidade_cartas = primeiro;
    jogo->jogadores[1].quantidade_cartas = segundo;
    jogo->monte_disputa.quantidade = monte;

    for (int i = 0; i < primeiro; ++i)
        jogo->jogadores[0].cartas[i] =
            criarCarta(proximoId++, (ClasseCarta)(i % 4), 50);
    for (int i = 0; i < segundo; ++i)
        jogo->jogadores[1].cartas[i] =
            criarCarta(proximoId++, (ClasseCarta)(i % 4), 50);
    for (int i = 0; i < monte; ++i)
        jogo->monte_disputa.cartas[i] =
            criarCarta(proximoId++, (ClasseCarta)(i % 4), 50);
}

static void testarComparacaoSuperTrunfo(void)
{
    Carta super = criarCarta(1, CLASSE_A, 20);
    Carta cartaB = criarCarta(2, CLASSE_B, 99);
    Carta cartaC = criarCarta(3, CLASSE_C, 99);
    Carta cartaD = criarCarta(4, CLASSE_D, 99);
    Carta cartaA = criarCarta(5, CLASSE_A, 99);
    Carta cartaComum = criarCarta(6, CLASSE_B, 20);
    super.super_trunfo = 1;

    assert(compararCartasComSuperTrunfo(super, cartaB, RACIOCINIO) == 1);
    assert(compararCartasComSuperTrunfo(super, cartaC, RACIOCINIO) == 1);
    assert(compararCartasComSuperTrunfo(super, cartaD, RACIOCINIO) == 1);
    assert(compararCartasComSuperTrunfo(cartaB, super, RACIOCINIO) == -1);
    assert(compararCartasComSuperTrunfo(cartaC, super, RACIOCINIO) == -1);
    assert(compararCartasComSuperTrunfo(cartaD, super, RACIOCINIO) == -1);
    assert(compararCartasComSuperTrunfo(super, cartaA, RACIOCINIO) == -1);
    assert(compararCartasComSuperTrunfo(super, cartaA, PROGRAMACAO) == 0);
    assert(compararCartasComSuperTrunfo(cartaB, cartaA, RACIOCINIO) == 0);
    assert(compararCartas(cartaB, cartaComum, RACIOCINIO) == 1);
    assert(compararCartas(cartaB, cartaA, PROGRAMACAO) == 0);
    assert(compararCartasComSuperTrunfo(super, cartaB, (Atributo)99) == -2);
    assert(compararCartas(super, cartaB, (Atributo)99) == -2);
}

static void testarIntegridadeDasZonas(void)
{
    Jogo jogo;
    preencherJogo(&jogo, 16, 16, 2);
    assert(verificarFimJogo(&jogo) == 0);

    jogo.jogadores[1].cartas[0].id = jogo.jogadores[0].cartas[0].id;
    assert(verificarFimJogo(&jogo) == -1);

    preencherJogo(&jogo, 16, 16, 2);
    jogo.monte_disputa.cartas[0].raciocinio = 101;
    assert(verificarFimJogo(&jogo) == -1);

    preencherJogo(&jogo, 0, 0, MAX_CARTAS);
    assert(verificarFimJogo(&jogo) == 1);
    assert(determinarVencedorJogo(&jogo) == NULL);
}

static void testarTransferenciaAtomica(void)
{
    Jogo jogo;
    preencherJogo(&jogo, 16, 16, 2);
    assert(entregarMonteDisputa(&jogo, 0) == 1);
    assert(jogo.jogadores[0].quantidade_cartas == 18);
    assert(jogo.jogadores[1].quantidade_cartas == 16);
    assert(jogo.monte_disputa.quantidade == 0);
    assert(verificarFimJogo(&jogo) == 0);

    preencherJogo(&jogo, 16, 16, 2);
    jogo.monte_disputa.cartas[0].id = jogo.jogadores[0].cartas[0].id;
    assert(entregarMonteDisputa(&jogo, 0) == 0);
    assert(jogo.jogadores[0].quantidade_cartas == 16);
    assert(jogo.jogadores[1].quantidade_cartas == 16);
    assert(jogo.monte_disputa.quantidade == 2);
}

static void testarDeterminacaoDeEmpatados(void)
{
    Jogo jogo;
    int empatados[2] = {-1, -1};
    int adicionarAoMonte = 1;
    Carta cartaConfronto;

    preencherJogo(&jogo, 16, 16, 2);

    assert(determinarEmpatados(&jogo, RACIOCINIO, empatados) == 2);
    assert(empatados[0] == 0 && empatados[1] == 1);

    atualizarParticipantesDesempate(&jogo, empatados, 2);
    assert(executarDesempate(&jogo, RACIOCINIO) == 1);
    assert(obterCartaConfronto(&jogo, 0, &cartaConfronto, &adicionarAoMonte) == 1);
    assert(adicionarAoMonte == 0);
    assert(cartaConfronto.id == jogo.jogadores[0].cartas[0].id);

    jogo.estados[0].carta_reutilizada.raciocinio = 70;
    jogo.estados[1].carta_reutilizada.raciocinio = 40;
    assert(determinarEmpatados(&jogo, RACIOCINIO, empatados) == 1);
    assert(empatados[0] == 0);
}

static void testarLeituraCSV(void)
{
    Baralho baralho = {0};
    FILE *entrada;
    FILE *saida;
    char linha[2048];
    const unsigned char bomUtf8[] = {0xEF, 0xBB, 0xBF};

    assert(carregarBaralhoCSV(&baralho, "data/cartas.csv") == 1);
    assert(baralho.quantidade == MAX_CARTAS);

    entrada = fopen("data/cartas.csv", "r");
    saida = fopen("tests/test_bom.csv", "w");
    assert(entrada != NULL && saida != NULL);
    assert(fwrite(bomUtf8, 1, sizeof bomUtf8, saida) == sizeof bomUtf8);
    while (fgets(linha, sizeof linha, entrada) != NULL)
        fputs(linha, saida);
    fclose(entrada);
    fclose(saida);

    assert(carregarBaralhoCSV(&baralho, "tests/test_bom.csv") == 1);
    assert(baralho.quantidade == MAX_CARTAS);
    remove("tests/test_bom.csv");

    entrada = fopen("data/cartas.csv", "r");
    saida = fopen("tests/test_invalid.csv", "w");
    assert(entrada != NULL && saida != NULL);

    assert(fgets(linha, sizeof linha, entrada) != NULL);
    fputs(linha, saida);
    assert(fgets(linha, sizeof linha, entrada) != NULL);
    fputs(linha, saida);
    fputs("id-invalido,Empresa,Modelo,Caracteristica,A,50,50,50,50,modelo\n",
          saida);
    fclose(entrada);
    fclose(saida);

    assert(carregarBaralhoCSV(&baralho, "tests/test_invalid.csv") == 0);
    assert(baralho.quantidade == 0);
    remove("tests/test_invalid.csv");

    entrada = fopen("data/cartas.csv", "r");
    saida = fopen("tests/test_duplicate.csv", "w");
    assert(entrada != NULL && saida != NULL);
    assert(fgets(linha, sizeof linha, entrada) != NULL);
    fputs(linha, saida);
    assert(fgets(linha, sizeof linha, entrada) != NULL);
    fputs(linha, saida);
    fputs(linha, saida);
    fclose(entrada);
    fclose(saida);

    assert(carregarBaralhoCSV(&baralho, "tests/test_duplicate.csv") == 0);
    assert(baralho.quantidade == 0);
    remove("tests/test_duplicate.csv");

    saida = fopen("tests/test_long.csv", "w");
    assert(saida != NULL);
    fputs("id,empresa,modelo,caracteristicas,classe,raciocinio,programacao,matematica,conhecimento,tipo_carta\n",
          saida);
    for (int i = 0; i < 1100; ++i)
        fputc('x', saida);
    fputc('\n', saida);
    fclose(saida);

    assert(carregarBaralhoCSV(&baralho, "tests/test_long.csv") == 0);
    assert(baralho.quantidade == 0);
    remove("tests/test_long.csv");

    assert(carregarBaralhoCSV(&baralho, "data/arquivo-inexistente.csv") == 0);
    assert(baralho.quantidade == 0);
}

int main(void)
{
    testarComparacaoSuperTrunfo();
    testarIntegridadeDasZonas();
    testarTransferenciaAtomica();
    testarDeterminacaoDeEmpatados();
    testarLeituraCSV();
    puts("Testes de refatoracao: todos passaram.");
    return 0;
}
