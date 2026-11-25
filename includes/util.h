#ifndef UTIL_H
#define UTIL_H

// Limpa o terminal antes de iniciar uma nova rodada.
void limparTerminal(void);


// limpa caracteres restantes da entrada
void limparBuffer(void);

// lê um número inteiro validado
int lerInteiro(int minimo, int maximo);

// lê uma string
void lerString(char *destino, int tamanho);

// Retorna 0 se o jogador venceu, 1 se perdeu e -1 para entrada invalida.
// Convencao: 1 = PAR; 2 = IMPAR, tanto para escolha quanto para resultado.
int determinarVencedorSorteio(int escolha, int resultado);

// inicializa a semente aleatoria
void inicializarAleatorio(void);

#endif
