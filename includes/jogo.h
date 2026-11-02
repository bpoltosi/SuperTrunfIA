
#ifndef JOGO_H
#define JOGO_H

#include "baralho.h"
#include "jogador.h"
#include "carta.h"

// Monte que acumula as cartas durante os empates
typedef struct
{
    Carta *cartas;
    int quantidade;
    int capacidade;
} MonteDisputa;

// Controle individual dos jogadores durante um desempate
typedef struct
{
    int participa_desempate;

    // Referência à carta que já está no Monte de Disputa
    int tem_carta_reutilizada;
    Carta carta_reutilizada;

} EstadoDesempate;

// Estrutura principal da partida
typedef struct
{
    Jogador *jogadores;
    int quantidade_jogadores;

    Baralho baralho;
    MonteDisputa monte_disputa;

    EstadoDesempate *estados;

    int rodada_atual;
    int jogador_atual;
    int jogo_ativo;

} Jogo;

                    // INICIALIZAÇÃO E FINALIZAÇÃO

// Inicializa uma partida
int inicializarJogo(Jogo *jogo, int quantidade_jogadores);

// Libera os recursos utilizados pela partida
void finalizarJogo(Jogo *jogo);

                    // CONTROLE DAS RODADAS

// Executa uma rodada normal
int executarRodada(Jogo *jogo, Atributo atributo);

// Executa uma sequência de desempates
int executarDesempate(Jogo *jogo, Atributo atributo);

// Determina os jogadores empatados na maior pontuação
int determinarEmpatados(Jogo *jogo, Atributo atributo, int *empatados);

                    // MONTE DE DISPUTA

// Adiciona uma carta ao monte
int adicionarCartaDisputa(Jogo *jogo, Carta carta);

// Entrega todas as cartas ao vencedor
int entregarMonteDisputa(Jogo *jogo, int vencedor);

// Limpa o monte após a resolução
void limparMonteDisputa(Jogo *jogo);

                    // CARTAS E DESEMPATE

// Obtém a carta que o jogador utilizará
int obterCartaConfronto(Jogo *jogo, int indice_jogador, Carta *carta, int *adicionar_ao_monte);

// Prepara os jogadores que continuarão no desempate
void atualizarParticipantesDesempate(Jogo *jogo, int *empatados, int quantidade_empatados);

// Verifica se o jogador pode continuar participando
int verificarJogadorDesempate(Jogo *jogo, int indice_jogador);

                    // CONDIÇÕES DE VITÓRIA

// Verifica se a partida terminou
int verificarFimJogo(Jogo *jogo);

// Identifica o vencedor da partida
Jogador *determinarVencedorJogo(Jogo *jogo);

#endif