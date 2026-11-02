#include "carta.h"

int obterPontuacao(Carta carta, Atributo atributo)
{
    switch (atributo) {
        case RACIOCINIO: return carta.raciocinio;
        case PROGRAMACAO: return carta.programacao;
        case MATEMATICA: return carta.matematica;
        case CONHECIMENTO: return carta.conhecimento;
        default: return -1;
    }
}

int compararCartas(Carta carta1, Carta carta2, Atributo atributo)
{
    int pontos1 = obterPontuacao(carta1, atributo);
    int pontos2 = obterPontuacao(carta2, atributo);
    if (pontos1 < 0 || pontos2 < 0) return -2;
    if (pontos1 > pontos2) return 1;
    if (pontos1 < pontos2) return -1;
    return 0;
}

int verificarSuperTrunfo(Carta carta)
{
    return carta.super_trunfo == 1;
}

ClasseCarta obterClasseCarta(const Carta *carta)
{
    return carta == 0 ? CLASSE_INVALIDA : carta->classe;
}

int validarCarta(const Carta *carta)
{
    if (carta == 0 || carta->id <= 0 ||
        carta->empresa[0] == '\0' || carta->modelo[0] == '\0' ||
        carta->caracteristicas[0] == '\0' ||
        carta->classe < CLASSE_A || carta->classe > CLASSE_D ||
        carta->raciocinio < 0 || carta->raciocinio > 100 ||
        carta->programacao < 0 || carta->programacao > 100 ||
        carta->matematica < 0 || carta->matematica > 100 ||
        carta->conhecimento < 0 || carta->conhecimento > 100 ||
        (carta->super_trunfo != 0 && carta->super_trunfo != 1))
        return 0;
    return 1;
}
