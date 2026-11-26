#ifndef UTIL_H
#define UTIL_H

// Limpa o terminal antes de uma nova rodada.
void limparTerminal(void);

// Descarta os caracteres restantes da linha atual.
void limparBuffer(void);

// Le um inteiro no intervalo inclusivo; retorna -1 em EOF.
int lerInteiro(int minimo, int maximo);

// Le uma linha: 1 sucesso, 0 EOF/argumentos invalidos, -1 entrada longa.
int lerString(char *destino, int tamanho);

// Retorna 0 se o jogador venceu, 1 se perdeu e -1 para entrada invalida.
// Convencao: 1 = IMPAR; 2 = PAR, tanto para escolha quanto para resultado.
int determinarVencedorSorteio(int escolha, int resultado);

// Inicializa a semente aleatoria.
void inicializarAleatorio(void);

#endif
