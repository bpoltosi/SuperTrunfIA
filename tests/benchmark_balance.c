#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "jogo.h"

#define AMOSTRAS 2000
static int compararInt(const void *a, const void *b)
{
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}
int main(void)
{
    int duracoes[AMOSTRAS], total = 0, vitorias_primeiro = 0;
    int rodadas_com_empate = 0, total_rodadas = 0, maximo = 0;
    int aparicoes_classe[4] = {0}, vitorias_classe[4] = {0};

    for (unsigned seed = 1; seed <= AMOSTRAS; ++seed) {
        Jogo jogo;
        srand(seed);
        assert(inicializarJogo(&jogo, 2));
        int guard = 0, empates = 0;

        while (verificarFimJogo(&jogo) == 0 && guard++ < 20000) {
            Atributo atributo = (Atributo)(rand() % QUANTIDADE_ATRIBUTOS);
            Carta c0, c1;
            assert(obterCartaTopo(&jogo.jogadores[0], &c0));
            assert(obterCartaTopo(&jogo.jogadores[1], &c1));
            ++aparicoes_classe[c0.classe]; ++aparicoes_classe[c1.classe];
            int resultado = compararCartasComSuperTrunfo(c0, c1, atributo);
            assert(executarRodada(&jogo, atributo));
            if (resultado != 0) {
                int vencedor = resultado == 1 ? 0 : 1;
                ++vitorias_classe[(vencedor == 0 ? c0 : c1).classe];
            } else {
                ++empates;
                int limite = 0;
                while (verificarJogadorDesempate(&jogo, 0) &&
                       verificarJogadorDesempate(&jogo, 1) && limite++ < 100) {
                    Atributo desempate = (Atributo)(rand() % QUANTIDADE_ATRIBUTOS);
                    Carta a, b;
                    int add_a, add_b;
                    if (!obterCartaConfronto(&jogo, 0, &a, &add_a) ||
                        !obterCartaConfronto(&jogo, 1, &b, &add_b)) break;
                    ++aparicoes_classe[a.classe]; ++aparicoes_classe[b.classe];
                    int r = compararCartasComSuperTrunfo(a, b, desempate);
                    assert(executarDesempate(&jogo, desempate));
                    if (r != 0) {
                        int vencedor = r == 1 ? 0 : 1;
                        ++vitorias_classe[(vencedor == 0 ? a : b).classe];
                        break;
                    }
                }
                assert(limite < 100);
            }
            assert(jogo.jogadores[0].quantidade_cartas +
                   jogo.jogadores[1].quantidade_cartas +
                   jogo.monte_disputa.quantidade == MAX_CARTAS);
        }

        assert(verificarFimJogo(&jogo) == 1);
        Jogador *vencedor = determinarVencedorJogo(&jogo);
        if (vencedor == &jogo.jogadores[0]) ++vitorias_primeiro;
        int rodadas = jogo.rodada_atual - 1;
        duracoes[seed - 1] = rodadas;
        total += rodadas;
        total_rodadas += rodadas;
        rodadas_com_empate += empates;
        if (rodadas > maximo) maximo = rodadas;
        finalizarJogo(&jogo);
    }

    qsort(duracoes, AMOSTRAS, sizeof duracoes[0], compararInt);
    printf("AMOSTRAS=%d\n", AMOSTRAS);
    printf("MEDIA=%.2f\n", (double)total / AMOSTRAS);
    printf("MEDIANA=%d\n", duracoes[AMOSTRAS / 2]);
    printf("P90=%d\n", duracoes[(AMOSTRAS * 90) / 100]);
    printf("P95=%d\n", duracoes[(AMOSTRAS * 95) / 100]);
    printf("MAXIMO=%d\n", maximo);
    printf("EMPATES_POR_RODADA=%.4f\n", (double)rodadas_com_empate / total_rodadas);
    printf("VITORIAS_JOGADOR_0=%.2f%%\n", 100.0 * vitorias_primeiro / AMOSTRAS);
    for (int i=0;i<4;i++)
        printf("CLASSE_%c_APARICOES=%d_VITORIAS=%d_TAXA=%.2f%%\n",
               'A'+i, aparicoes_classe[i], vitorias_classe[i],
               aparicoes_classe[i] ? 100.0*vitorias_classe[i]/aparicoes_classe[i] : 0.0);
    return 0;
}
