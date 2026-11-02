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

int obterPontuacao(Carta carta, Atributo atributo);
int compararCartas(Carta carta1, Carta carta2, Atributo atributo);
/* Aplica a regra especial; retorno: 1 carta1, -1 carta2, 0 empate, -2 atributo inválido. */
int compararCartasComSuperTrunfo(Carta carta1, Carta carta2, Atributo atributo);
int verificarSuperTrunfo(Carta carta);
ClasseCarta obterClasseCarta(const Carta *carta);
int validarCarta(const Carta *carta);
#endif
