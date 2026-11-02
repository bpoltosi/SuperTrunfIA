#ifndef CARTA_H
#define CARTA_H
#define MAX_CARTAS 34

typedef enum { RACIOCINIO = 0, PROGRAMACAO, MATEMATICA, CONHECIMENTO, QUANTIDADE_ATRIBUTOS } Atributo;
typedef enum { CLASSE_INVALIDA = -1, CLASSE_A = 0, CLASSE_B, CLASSE_C, CLASSE_D } ClasseCarta;

typedef struct {
    int id;
    char empresa[50];
    char modelo[50];
    char caracteristicas[200];
    ClasseCarta classe;
    int raciocinio;
    int programacao;
    int matematica;
    int conhecimento;
    int super_trunfo;
} Carta;

/* Pontuação 0–100; -1 se o atributo for inválido. */
int obterPontuacao(Carta carta, Atributo atributo);
/* 1: carta1 vence; -1: carta2 vence; 0: empate; -2: atributo inválido. */
int compararCartas(Carta carta1, Carta carta2, Atributo atributo);
/* 1 se Super Trunfo; 0 caso contrário. */
int verificarSuperTrunfo(Carta carta);
/* Classe A–D; CLASSE_INVALIDA para ponteiro nulo. */
ClasseCarta obterClasseCarta(const Carta *carta);
/* 1 se os campos da carta forem válidos; 0 caso contrário. */
int validarCarta(const Carta *carta);
#endif
