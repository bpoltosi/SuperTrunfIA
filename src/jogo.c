#include <string.h>
#include <stdlib.h>
#include "jogo.h"
#include "interface.h"
#include "util.h"

static int atributoValido(Atributo atributo)
{
    return atributo >= RACIOCINIO && atributo < QUANTIDADE_ATRIBUTOS;
}

/*
 * Garante que as duas maos e o monte contenham exatamente as 34 cartas
 * validas, sem IDs repetidos entre quaisquer zonas.
 */
static int validarIntegridadeZonas(const Jogo *jogo)
{
    int ids[MAX_CARTAS];
    int quantidadeIds = 0;

    if (!jogo ||
        jogo->quantidade_jogadores != MAX_JOGADORES ||
        jogo->jogadores[0].quantidade_cartas < 0 ||
        jogo->jogadores[0].quantidade_cartas > MAX_CARTAS ||
        jogo->jogadores[1].quantidade_cartas < 0 ||
        jogo->jogadores[1].quantidade_cartas > MAX_CARTAS ||
        jogo->monte_disputa.quantidade < 0 ||
        jogo->monte_disputa.quantidade > MAX_CARTAS ||
        jogo->jogadores[0].quantidade_cartas +
                jogo->jogadores[1].quantidade_cartas +
                jogo->monte_disputa.quantidade !=
            MAX_CARTAS)
        return 0;

    for (int jogador = 0; jogador < MAX_JOGADORES; ++jogador)
    {
        const Jogador *mao = &jogo->jogadores[jogador];

        for (int i = 0; i < mao->quantidade_cartas; ++i)
        {
            const Carta *carta = &mao->cartas[i];

            if (!validarCarta(carta))
                return 0;

            for (int j = 0; j < quantidadeIds; ++j)
            {
                if (ids[j] == carta->id)
                    return 0;
            }
            ids[quantidadeIds++] = carta->id;
        }
    }

    for (int i = 0; i < jogo->monte_disputa.quantidade; ++i)
    {
        const Carta *carta = &jogo->monte_disputa.cartas[i];

        if (!validarCarta(carta))
            return 0;

        for (int j = 0; j < quantidadeIds; ++j)
        {
            if (ids[j] == carta->id)
                return 0;
        }
        ids[quantidadeIds++] = carta->id;
    }
    return quantidadeIds == MAX_CARTAS;
}

int inicializarJogo(Jogo *jogo, int quantidade_jogadores)
{
    if (!jogo || quantidade_jogadores != MAX_JOGADORES)
        return 0;
    memset(jogo, 0, sizeof(*jogo));
    jogo->quantidade_jogadores = quantidade_jogadores;
    for (int i = 0; i < quantidade_jogadores; ++i)
        inicializarJogador(&jogo->jogadores[i], i + 1, "");
    if (!carregarBaralhoCSV(&jogo->baralho, "data/cartas.csv"))
    {
        finalizarJogo(jogo);
        return 0;
    }
    embaralharBaralho(&jogo->baralho);
    if (!distribuirCartas(&jogo->baralho, jogo->jogadores, quantidade_jogadores))
    {
        finalizarJogo(jogo);
        return 0;
    }
    jogo->rodada_atual = 1;
    jogo->jogador_atual = 0;
    jogo->jogo_ativo = 1;
    return 1;
}

void finalizarJogo(Jogo *jogo)
{
    if (!jogo)
        return;
    for (int i = 0; i < MAX_JOGADORES; ++i)
        liberarJogador(&jogo->jogadores[i]);
    liberarBaralho(&jogo->baralho);
    limparMonteDisputa(jogo);
    memset(jogo->estados, 0, sizeof jogo->estados);
    jogo->quantidade_jogadores = 0;
    jogo->jogo_ativo = 0;
}

int adicionarCartaDisputa(Jogo *jogo, Carta carta)
{
    if (!jogo || jogo->quantidade_jogadores != MAX_JOGADORES ||
        !validarCarta(&carta) || jogo->monte_disputa.quantidade < 0 ||
        jogo->monte_disputa.quantidade >= MAX_CARTAS)
        return 0;
    for (int i = 0; i < jogo->monte_disputa.quantidade; ++i)
        if (jogo->monte_disputa.cartas[i].id == carta.id)
            return 0;
    jogo->monte_disputa.cartas[jogo->monte_disputa.quantidade++] = carta;
    return 1;
}

int entregarMonteDisputa(Jogo *jogo, int vencedor)
{
    if (!jogo || vencedor < 0 || vencedor >= MAX_JOGADORES ||
        !validarIntegridadeZonas(jogo) ||
        jogo->jogadores[vencedor].quantidade_cartas +
                jogo->monte_disputa.quantidade >
            MAX_CARTAS)
        return 0;

    /* A integridade de todas as zonas e validada antes da primeira mutacao. */
    Jogador *j = &jogo->jogadores[vencedor];
    int base = j->quantidade_cartas;
    /* Ordem do monte de disputa aleatorizada para evitar ciclos deterministas. */
    for (int i = jogo->monte_disputa.quantidade - 1; i > 0; --i)
    {
        int indice = rand() % (i + 1);
        Carta temporaria = jogo->monte_disputa.cartas[i];
        jogo->monte_disputa.cartas[i] = jogo->monte_disputa.cartas[indice];
        jogo->monte_disputa.cartas[indice] = temporaria;
    }
    for (int i = 0; i < jogo->monte_disputa.quantidade; ++i)
        j->cartas[base + i] = jogo->monte_disputa.cartas[i];
    j->quantidade_cartas += jogo->monte_disputa.quantidade;
    limparMonteDisputa(jogo);
    return 1;
}

void limparMonteDisputa(Jogo *jogo)
{
    if (jogo)
        jogo->monte_disputa.quantidade = 0;
}

int obterCartaConfronto(Jogo *jogo, int indice_jogador, Carta *carta, int *adicionar_ao_monte)
{
    if (!jogo || jogo->quantidade_jogadores != MAX_JOGADORES ||
        !carta || !adicionar_ao_monte || indice_jogador < 0 ||
        indice_jogador >= MAX_JOGADORES)
        return 0;
    EstadoDesempate *estado = &jogo->estados[indice_jogador];
    Jogador *j = &jogo->jogadores[indice_jogador];
    if ((estado->tem_carta_reutilizada != 0 && estado->tem_carta_reutilizada != 1) ||
        j->quantidade_cartas <= 0 || j->quantidade_cartas > MAX_CARTAS)
        return 0;
    if (estado->tem_carta_reutilizada == 1)
    {
        if (!validarCarta(&estado->carta_reutilizada) ||
            estado->carta_reutilizada.id != j->cartas[0].id)
            return 0;
        *carta = estado->carta_reutilizada;
        *adicionar_ao_monte = 0;
        return 1;
    }
    *carta = j->cartas[0];
    *adicionar_ao_monte = 1;
    return 1;
}

int determinarEmpatados(Jogo *jogo, Atributo atributo, int *empatados)
{
    if (!jogo || !empatados || !jogo->jogo_ativo || !atributoValido(atributo) ||
        verificarFimJogo(jogo) != 0)
        return -1;
    Carta cartas[2];
    int ignorarAdicaoAoMonte;
    for (int i = 0; i < 2; ++i)
    {
        if (!obterCartaConfronto(jogo, i, &cartas[i], &ignorarAdicaoAoMonte))
            return -1;
    }
    int resultado = compararCartasComSuperTrunfo(cartas[0], cartas[1], atributo);
    if (resultado == -2)
        return -1;
    if (resultado == 0)
    {
        empatados[0] = 0;
        empatados[1] = 1;
        return 2;
    }
    empatados[0] = resultado == 1 ? 0 : 1;
    return 1;
}

void atualizarParticipantesDesempate(Jogo *jogo, int *empatados, int quantidade_empatados)
{
    if (!jogo || jogo->quantidade_jogadores != MAX_JOGADORES || !empatados ||
        quantidade_empatados < 1 || quantidade_empatados > MAX_JOGADORES)
        return;
    int novos[2] = {0, 0};
    for (int i = 0; i < quantidade_empatados; ++i)
    {
        if (empatados[i] < 0 || empatados[i] >= MAX_JOGADORES || novos[empatados[i]])
            return;
        novos[empatados[i]] = 1;
    }
    for (int i = 0; i < 2; ++i)
        jogo->estados[i].participa_desempate = novos[i];
}

int verificarJogadorDesempate(Jogo *jogo, int indice_jogador)
{
    if (!jogo || !jogo->jogo_ativo || jogo->quantidade_jogadores != MAX_JOGADORES ||
        indice_jogador < 0 || indice_jogador >= MAX_JOGADORES)
        return 0;
    return jogo->estados[indice_jogador].participa_desempate == 1;
}

int executarRodada(Jogo *jogo, Atributo atributo)
{
    if (!jogo || !jogo->jogo_ativo || !atributoValido(atributo) ||
        jogo->quantidade_jogadores != MAX_JOGADORES || verificarFimJogo(jogo) != 0 ||
        jogo->monte_disputa.quantidade != 0 ||
        jogo->jogadores[0].quantidade_cartas <= 0 || jogo->jogadores[1].quantidade_cartas <= 0)
        return 0;
    Carta cartas[2];
    for (int i = 0; i < 2; ++i)
        if (!obterCartaTopo(&jogo->jogadores[i], &cartas[i]))
            return 0;
    int vencedor = compararCartasComSuperTrunfo(cartas[0], cartas[1], atributo);
    if (vencedor == -2)
        return 0;
    if (!adicionarCartaDisputa(jogo, cartas[0]) || !adicionarCartaDisputa(jogo, cartas[1]))
    {
        limparMonteDisputa(jogo);
        return 0;
    }
    for (int i = 0; i < 2; ++i)
        if (!removerCarta(&jogo->jogadores[i], 0))
            return 0;
    jogo->rodada_atual++;
    if (vencedor != 0)
    {
        int indice_vencedor = vencedor == 1 ? 0 : 1;
        jogo->jogador_atual = indice_vencedor;
        memset(jogo->estados, 0, sizeof jogo->estados);
        return entregarMonteDisputa(jogo, indice_vencedor);
    }
    int empatados[2] = {0, 1};
    atualizarParticipantesDesempate(jogo, empatados, 2);

    if ((jogo->jogadores[0].quantidade_cartas == 0) !=
        (jogo->jogadores[1].quantidade_cartas == 0))
    {
        int vencedor_desempate = jogo->jogadores[0].quantidade_cartas == 0 ? 1 : 0;
        jogo->jogador_atual = vencedor_desempate;
        memset(jogo->estados, 0, sizeof jogo->estados);
        return entregarMonteDisputa(jogo, vencedor_desempate);
    }
    return 1;
}

int executarDesempate(Jogo *jogo, Atributo atributo)
{
    if (!jogo || !jogo->jogo_ativo || !atributoValido(atributo) ||
        verificarFimJogo(jogo) != 0 ||
        !verificarJogadorDesempate(jogo, 0) || !verificarJogadorDesempate(jogo, 1) ||
        jogo->monte_disputa.quantidade <= 0 ||
        jogo->monte_disputa.quantidade > MAX_CARTAS - 2)
        return 0;
    Carta cartas[2];
    int add[2];
    for (int i = 0; i < 2; ++i)
        if (!obterCartaConfronto(jogo, i, &cartas[i], &add[i]))
            return 0;
    if (cartas[0].id == cartas[1].id)
        return 0;
    int resultado = compararCartasComSuperTrunfo(cartas[0], cartas[1], atributo);
    if (resultado == -2)
        return 0;
    if (resultado == 0)
    {
        int mascara = 0;
        for (int i = 0; i < 2; ++i)
        {
            jogo->estados[i].tem_carta_reutilizada = 1;
            jogo->estados[i].carta_reutilizada = cartas[i];
            jogo->estados[i].atributos_tentados |= (1 << atributo);
            mascara |= jogo->estados[i].atributos_tentados;
        }
        /* Evita desempate infinito: após testar os quatro atributos, as cartas
           empatadas são recolhidas uma única vez e um novo par é revelado. */
        if (mascara == (1 << QUANTIDADE_ATRIBUTOS) - 1)
        {
            for (int i = 0; i < 2; ++i)
            {
                if (!adicionarCartaDisputa(jogo, cartas[i]) ||
                    !removerCarta(&jogo->jogadores[i], 0))
                    return 0;
                jogo->estados[i].tem_carta_reutilizada = 0;
                memset(&jogo->estados[i].carta_reutilizada, 0, sizeof(Carta));
                jogo->estados[i].atributos_tentados = 0;
            }
            if ((jogo->jogadores[0].quantidade_cartas == 0) !=
                (jogo->jogadores[1].quantidade_cartas == 0))
            {
                int vencedor_desempate = jogo->jogadores[0].quantidade_cartas == 0 ? 1 : 0;
                jogo->jogador_atual = vencedor_desempate;
                memset(jogo->estados, 0, sizeof jogo->estados);
                return entregarMonteDisputa(jogo, vencedor_desempate);
            }
        }
        return 1;
    }
    int vencedor = resultado == 1 ? 0 : 1;
    for (int i = 0; i < 2; ++i)
    {
        if (!adicionarCartaDisputa(jogo, cartas[i]))
            return 0;
        if (!removerCarta(&jogo->jogadores[i], 0))
            return 0;
    }
    jogo->jogador_atual = vencedor;
    memset(jogo->estados, 0, sizeof jogo->estados);
    return entregarMonteDisputa(jogo, vencedor);
}

int verificarFimJogo(Jogo *jogo)
{
    if (!jogo || (jogo->jogo_ativo != 0 && jogo->jogo_ativo != 1) ||
        !validarIntegridadeZonas(jogo))
        return -1;

    /* Desempate flags and cached cards must match the current hand tops. */
    for (int jogador = 0; jogador < MAX_JOGADORES; ++jogador)
    {
        EstadoDesempate *estado = &jogo->estados[jogador];
        if ((estado->participa_desempate != 0 && estado->participa_desempate != 1) ||
            (estado->tem_carta_reutilizada != 0 && estado->tem_carta_reutilizada != 1) ||
            estado->atributos_tentados < 0 ||
            estado->atributos_tentados >= (1 << QUANTIDADE_ATRIBUTOS))
            return -1;
        if (estado->tem_carta_reutilizada)
        {
            if (!estado->participa_desempate || estado->atributos_tentados == 0 ||
                jogo->jogadores[jogador].quantidade_cartas <= 0 ||
                !validarCarta(&estado->carta_reutilizada) ||
                estado->carta_reutilizada.id != jogo->jogadores[jogador].cartas[0].id)
                return -1;
        }
        else if (estado->atributos_tentados != 0)
        {
            return -1;
        }
    }

    /* validarIntegridadeZonas ja garantiu cartas, contagem e IDs unicos. */

    if (jogo->jogadores[0].quantidade_cartas == MAX_CARTAS ||
        jogo->jogadores[1].quantidade_cartas == MAX_CARTAS ||
        (jogo->jogadores[0].quantidade_cartas == 0 &&
         jogo->jogadores[1].quantidade_cartas == 0 &&
         jogo->monte_disputa.quantidade == MAX_CARTAS))
    {
        jogo->jogo_ativo = 0;
        return 1;
    }
    return 0;
}

Jogador *determinarVencedorJogo(Jogo *jogo)
{
    if (verificarFimJogo(jogo) != 1)
        return NULL;
    for (int i = 0; i < 2; ++i)
        if (jogo->jogadores[i].quantidade_cartas == MAX_CARTAS)
            return &jogo->jogadores[i];
    return NULL;
}
