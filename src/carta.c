#include "carta.h"

int obterPontuacao(Carta carta, Atributo atributo)
{
    switch (atributo)
    {
        case RACIOCINIO:
            return carta.raciocinio;

        case PROGRAMACAO:
            return carta.programacao;

        case MATEMATICA:
            return carta.matematica;

        case CONHECIMENTO:
            return carta.conhecimento;

        default:
            return -1;
    }
}

/*
 * Retorno:
 *  1: carta1 vence
 * -1: carta2 vence
 *  0: empate
 * -2: atributo inválido
 */
int compararCartas(Carta carta1, Carta carta2, Atributo atributo)
{
    int pontos1 = obterPontuacao(carta1, atributo);
    int pontos2 = obterPontuacao(carta2, atributo);

    if (pontos1 < 0 || pontos2 < 0)
        return -2;

    if (pontos1 > pontos2)
        return 1;

    if (pontos1 < pontos2)
        return -1;

    return 0;
}

int verificarSuperTrunfo(Carta carta)
{
    return carta.super_trunfo != 0;
}
