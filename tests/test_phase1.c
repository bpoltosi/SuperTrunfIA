#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "carta.h"
#include "jogador.h"
#include "baralho.h"

static Carta cartaValida(int id, int r, int p, int m, int c, ClasseCarta classe, int super)
{
    Carta carta = {0};
    carta.id = id;
    strcpy(carta.empresa, "Teste");
    strcpy(carta.modelo, "Modelo");
    strcpy(carta.caracteristicas, "Caracteristica");
    carta.classe = classe;
    carta.raciocinio = r;
    carta.programacao = p;
    carta.matematica = m;
    carta.conhecimento = c;
    carta.super_trunfo = super;
    return carta;
}

static void testarCarta(void)
{
    Carta a = cartaValida(1, 90, 80, 70, 60, CLASSE_A, 0);
    Carta b = cartaValida(2, 89, 81, 70, 61, CLASSE_B, 0);
    Carta super = cartaValida(3, 90, 70, 99, 80, CLASSE_A, 1);
    Carta invalida = a;
    assert(validarCarta(&a));
    assert(!validarCarta(NULL));
    assert(obterClasseCarta(&a) == CLASSE_A);
    assert(obterClasseCarta(NULL) == CLASSE_INVALIDA);
    assert(obterPontuacao(a, RACIOCINIO) == 90);
    assert(obterPontuacao(a, PROGRAMACAO) == 80);
    assert(obterPontuacao(a, MATEMATICA) == 70);
    assert(obterPontuacao(a, CONHECIMENTO) == 60);
    assert(obterPontuacao(a, (Atributo)99) == -1);
    assert(compararCartas(a, b, RACIOCINIO) == 1);
    assert(compararCartas(a, b, PROGRAMACAO) == -1);
    assert(compararCartas(a, b, MATEMATICA) == 0);
    assert(compararCartas(a, b, (Atributo)99) == -2);
    assert(verificarSuperTrunfo(super) == 1);
    assert(verificarSuperTrunfo(a) == 0);
    assert(compararCartasComSuperTrunfo(super, b, CONHECIMENTO) == 1);
    assert(compararCartasComSuperTrunfo(super, a, RACIOCINIO) == 0);
    assert(compararCartasComSuperTrunfo(super, super, MATEMATICA) == 0);
    invalida.raciocinio = 101; assert(!validarCarta(&invalida));
    invalida = a; invalida.id = 0; assert(!validarCarta(&invalida));
    invalida = a; invalida.super_trunfo = 2; assert(!validarCarta(&invalida));
    invalida = b; invalida.super_trunfo = 1; assert(!validarCarta(&invalida));
    invalida = a; invalida.empresa[0] = '\0'; assert(!validarCarta(&invalida));
    puts("testarCarta: OK");
}

static void testarJogador(void)
{
    Jogador j;
    Carta c = cartaValida(1, 1, 2, 3, 4, CLASSE_D, 0), saida;
    inicializarJogador(&j, 7, "Jogador teste");
    assert(j.id == 7 && strcmp(j.nome, "Jogador teste") == 0 && j.quantidade_cartas == 0);
    inicializarJogador(NULL, 1, "Nulo");
    assert(adicionarCarta(&j, c));
    assert(adicionarCarta(&j, c));
    assert(obterCartaTopo(&j, &saida) && saida.id == 1);
    assert(!obterCartaTopo(NULL, &saida));
    assert(!obterCartaTopo(&j, NULL));
    assert(retirarCartaTopo(&j, &saida) && j.quantidade_cartas == 1);
    assert(removerCarta(&j, 0) && j.quantidade_cartas == 0);
    assert(!removerCarta(&j, 0));
    assert(!retirarCartaTopo(&j, &saida));
    for (int i = 0; i < MAX_CARTAS; i++) assert(adicionarCarta(&j, c));
    assert(j.quantidade_cartas == MAX_CARTAS);
    assert(!adicionarCarta(&j, c));
    liberarJogador(&j);
    assert(j.quantidade_cartas == 0 && j.nome[0] == '\0');
    liberarJogador(NULL);
    puts("testarJogador: OK");
}

static void testarCSVDistribuicao(void)
{
    Baralho b = {0};
    Jogador js[MAX_JOGADORES];
    int classes[4] = {0}, supers = 0;
    inicializarJogador(&js[0], 1, "J1");
    inicializarJogador(&js[1], 2, "J2");
    assert(carregarBaralhoCSV(&b, "data/cartas.csv"));
    assert(b.quantidade == MAX_CARTAS);
    for (int i = 0; i < b.quantidade; i++) {
        assert(validarCarta(&b.cartas[i]));
        classes[b.cartas[i].classe]++;
        supers += b.cartas[i].super_trunfo;
    }
    assert(classes[CLASSE_A] == 5 && classes[CLASSE_B] == 6 && classes[CLASSE_C] == 9 && classes[CLASSE_D] == 14);
    assert(supers == 1);
    embaralharBaralho(&b);
    assert(b.quantidade == MAX_CARTAS);
    assert(distribuirCartas(&b, js, MAX_JOGADORES));
    assert(js[0].quantidade_cartas == 17 && js[1].quantidade_cartas == 17);
    assert(b.quantidade == 0);
    assert(!distribuirCartas(&b, js, MAX_JOGADORES));
    liberarBaralho(&b);
    assert(b.quantidade == 0);
    /* CSV inválido deve falhar sem deixar cartas parcialmente carregadas. */
    {
        FILE *arquivo = fopen("tests/invalid.csv", "w");
        assert(arquivo != NULL);
        fputs("id,empresa,modelo,caracteristicas,classe,raciocinio,programacao,matematica,conhecimento,tipo_carta\\n", arquivo);
        fputs("linha-invalida\\n", arquivo);
        fclose(arquivo);
        assert(!carregarBaralhoCSV(&b, "tests/invalid.csv"));
        assert(b.quantidade == 0);
        remove("tests/invalid.csv");
    }
    puts("testarCSVDistribuicao: OK");
}

int main(void)
{
    testarCarta();
    testarJogador();
    testarCSVDistribuicao();
    puts("TODOS OS TESTES PASSARAM");
    return 0;
}
