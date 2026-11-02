
#include <stdlib.h>
#include <string.h>

#include "jogo.h"
#include "interface.h"
#include "util.h"

// INICIALIZAÇÃO E FINALIZAÇÃO

int inicializarJogo(Jogo *jogo, int quantidade_jogadores)
{

    // Inicializar os campos da estrutura Jogo

    // Alocar memória para os jogadores

    // Alocar memória para os estados de desempate

    // Inicializar o Monte de Disputa

    // Carregar o baralho

    // Embaralhar as cartas

    // Distribuir as cartas

    // Inicializar contador de rodadas

    return 1;
}

void finalizarJogo(Jogo *jogo)
{

    // Liberar memória dos jogadores

    // Liberar memória do baralho

    // Liberar memória do Monte de Disputa

    // Liberar memória dos estados
}

// CONTROLE DAS RODADAS

int executarRodada(Jogo *jogo, Atributo atributo)
{

    // 1. Obter a carta de cada jogador ativo

    // 2. Adicionar as cartas utilizadas ao Monte de Disputa

    // 3. Comparar as pontuações

    // 4. Identificar o maior resultado

    // 5. Verificar se houve empate

    // 6. Se houver empate:
    //    - Identificar os jogadores empatados
    //    - Atualizar os participantes do desempate
    //    - Executar o desempate

    // 7. Se não houver empate:
    //    - Entregar o Monte ao vencedor

    // 8. Atualizar a rodada

    return -1;
}

int executarDesempate(Jogo *jogo, Atributo atributo)
{

    // Enquanto houver empate:

    // 1. Obter as cartas dos participantes

    // 2. Comparar as pontuações

    // 3. Identificar quem obteve a maior pontuação

    // 4. Atualizar os participantes empatados

    // 5. Se houver um único vencedor:
    //    - Entregar todo o Monte de Disputa
    //    - Encerrar o desempate

    return -1;
}

int determinarEmpatados(Jogo *jogo, Atributo atributo, int *empatados)
{

    // Encontrar a maior pontuação

    // Identificar todos os jogadores com essa pontuação

    // Armazenar os índices dos empatados

    // Retornar a quantidade de jogadores empatados

    return 0;
}

// MONTE DE DISPUTA

int adicionarCartaDisputa(Jogo *jogo, Carta carta)
{

    // Verificar se existe capacidade disponível

    // Se necessário, aumentar a capacidade com realloc

    // Adicionar a carta ao Monte de Disputa

    // Atualizar a quantidade de cartas

    return 1;
}

int entregarMonteDisputa(Jogo *jogo, int vencedor)
{

    // Adicionar todas as cartas do Monte
    // à pilha do jogador vencedor

    // Limpar o Monte após a transferência

    return 1;
}

void limparMonteDisputa(Jogo *jogo)
{

    // Zerar a quantidade de cartas do monte
}

// CARTAS E DESEMPATE

int obterCartaConfronto(Jogo *jogo, int indice_jogador, Carta *carta, int *adicionar_ao_monte)
{

    // Se o jogador possui cartas:
    //    - Retirar a carta do topo
    //    - Retornar a carta
    //    - Indicar que deve entrar no Monte
    //
    // Se não possui cartas, mas tem carta reutilizável:
    //    - Retornar a referência à carta reutilizável
    //    - Indicar que NÃO deve entrar no Monte
    //
    // Caso contrário:
    //    - Jogador não pode participar

    return 0;
}

void atualizarParticipantesDesempate(Jogo *jogo, int *empatados, int quantidade_empatados)
{

    // Desativar todos os participantes anteriores

    // Ativar somente os jogadores empatados

    // Preservar as cartas reutilizáveis
}

int verificarJogadorDesempate(Jogo *jogo, int indice_jogador)
{

    // Verificar se participa do desempate

    // Verificar se possui cartas disponíveis
    // ou uma carta reutilizável

    return 0;
}

// CONDIÇÕES DE VITÓRIA

int verificarFimJogo(Jogo *jogo)
{

    // Verificar quantos jogadores ainda possuem cartas

    // Se restar apenas um jogador:
    //    - Encerrar a partida

    return 0;
}

Jogador *determinarVencedorJogo(Jogo *jogo)
{

    // Identificar o jogador que possui
    // as cartas restantes da partida

    return NULL;
}
