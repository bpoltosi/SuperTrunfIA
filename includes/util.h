#ifndef UTIL_H
#define UTIL_H

// limpa caracteres restantes da entrada
void limparBuffer(void);

// lê um número inteiro validado
int lerInteiro(int minimo, int maximo);

// lê uma string
void lerString(char *destino, int tamanho);

// inicializa a semente aleatória
void inicializarAleatorio(void);

#endif