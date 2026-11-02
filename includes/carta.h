#ifndef CARTA_H
#define CARTA_H

#define MAX_CARTAS 34

typedef enum {
    RACIOCINIO,
    PROGRAMACAO,
    MATEMATICA,
    CONHECIMENTO
} Atributo;

typedef struct {
    int id;
    char empresa[50];
    char modelo[50];
    char caracteristicas[200];

    int raciocinio;
    int programacao;
    int matematica;
    int conhecimento;

    int super_trunfo;
} Carta;

int obterPontuacao(Carta carta, Atributo atributo);
int compararCartas(Carta carta1, Carta carta2, Atributo atributo);
int verificarSuperTrunfo(Carta carta);

#endif
