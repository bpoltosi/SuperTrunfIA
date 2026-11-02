#ifndef CARTA_H
#define CARTA_H

typedef enum {
    RACIOCINIO,
    PROGRAMACAO,
    MATEMATICA,
    CONHECIMENTO
} Atributo;

typedef struct {
    int id;
    char empresa[50];
    char modelo[80];
    char caracteristicas[200];

    int raciocinio;
    int programacao;
    int matematica;
    int conhecimento;

    int super_trunfo;
} Carta;

// consulta a pontuação de um atributo
int obterPontuacao(Carta carta, Atributo atributo);

// compara duas cartas
int compararCartas(Carta carta1, Carta carta2, Atributo atributo);

// verifica se a carta é um Super Trunfo
int verificarSuperTrunfo(Carta carta);

#endif