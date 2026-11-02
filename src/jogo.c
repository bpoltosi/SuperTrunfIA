#include "jogo.h"

int inicializarJogo(Jogo *jogo, int quantidade_jogadores);

void executarRodada(Jogo *jogo);

Atributo selecionarAtributo(Jogo *jogo);

int determinarVencedor(Jogo *jogo, Atributo atributo);

void atualizarRodada(Jogo *jogo, int vencedor);

int verificarFimJogo(Jogo *jogo);

Jogador *determinarVencedorJogo(Jogo *jogo);

void finalizarJogo(Jogo *jogo);