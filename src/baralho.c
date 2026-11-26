#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include "baralho.h"

#define TAMANHO_LINHA_CSV 1024
#define QUANTIDADE_CAMPOS_CSV 10
#define TAMANHO_CAMPO_CSV 256
#define CABECALHO_CSV "id,empresa,modelo,caracteristicas,classe,raciocinio,programacao,matematica,conhecimento,tipo_carta"

static int lerLinha(FILE *arquivo, char *linha, size_t tamanho)
{
    size_t comprimento;

    if (!fgets(linha, (int)tamanho, arquivo))
        return 0;

    comprimento = strlen(linha);
    if (comprimento > 0 && linha[comprimento - 1] != '\n' && !feof(arquivo)) {
        int caractere;

        do {
            caractere = fgetc(arquivo);
        } while (caractere != '\n' && caractere != EOF);

        return -1;
    }

    return 1;
}
static int separarCamposCSV(char *linha, char campos[QUANTIDADE_CAMPOS_CSV][TAMANHO_CAMPO_CSV])
{
    int indiceCampo = 0;
    size_t posicaoCampo = 0;
    int dentroDeAspas = 0;
    int aspasFechadas = 0;

    for (size_t i = 0; linha[i] != '\0'; ++i) {
        char caractere = linha[i];

        if (caractere == '"') {
            if (dentroDeAspas && linha[i + 1] == '"') {
                if (posicaoCampo >= TAMANHO_CAMPO_CSV - 1)
                    return 0;

                campos[indiceCampo][posicaoCampo++] = '"';
                ++i;
            } else if (dentroDeAspas) {
                dentroDeAspas = 0;
                aspasFechadas = 1;
            } else if (posicaoCampo == 0 && !aspasFechadas) {
                dentroDeAspas = 1;
            } else {
                return 0;
            }
        } else if (caractere == ',' && !dentroDeAspas) {
            if (indiceCampo >= QUANTIDADE_CAMPOS_CSV - 1)
                return 0;

            campos[indiceCampo][posicaoCampo] = '\0';
            ++indiceCampo;
            posicaoCampo = 0;
            aspasFechadas = 0;
        } else if (caractere != '\r' && caractere != '\n') {
            if (aspasFechadas || posicaoCampo >= TAMANHO_CAMPO_CSV - 1)
                return 0;

            campos[indiceCampo][posicaoCampo++] = caractere;
        }
    }

    if (dentroDeAspas)
        return 0;

    campos[indiceCampo][posicaoCampo] = '\0';
    return indiceCampo == QUANTIDADE_CAMPOS_CSV - 1;
}
static int converterInteiro(const char *texto, int *valor)
{
    char *fim;
    long convertido;

    if (!texto || !valor || texto[0] == '\0')
        return 0;

    errno = 0;
    convertido = strtol(texto, &fim, 10);

    if (errno == ERANGE || texto == fim || *fim != '\0' ||
        convertido < INT_MIN || convertido > INT_MAX)
        return 0;

    *valor = (int)convertido;
    return 1;
}
static void reportarErroCSV(int linha, const char *campo)
{
    if (linha>0) fprintf(stderr,"CSV: linha %d, campo/validacao %s.\n",linha,campo);
    else fprintf(stderr,"CSV: %s.\n",campo);
}
static int converterClasse(const char *texto, ClasseCarta *classe)
{
    if (!texto || !classe) return 0;
    if (!strcmp(texto,"A")) *classe=CLASSE_A;
    else if (!strcmp(texto,"B")) *classe=CLASSE_B;
    else if (!strcmp(texto,"C")) *classe=CLASSE_C;
    else if (!strcmp(texto,"D")) *classe=CLASSE_D;
    else return 0;
    return 1;
}
int carregarBaralhoCSV(Baralho *baralho, const char *caminho)
{
    FILE *arquivo;
    char linha[TAMANHO_LINHA_CSV];
    char campos[QUANTIDADE_CAMPOS_CSV][TAMANHO_CAMPO_CSV];
    Baralho temporario = {0};
    int quantidadeSuper = 0;
    int classes[4] = {0};
    int numeroLinha = 1;
    int status;
    int sucesso = 0;
    int linhaErro = 0;
    const char *erro = NULL;

    if (!baralho || !caminho)
        return 0;

    baralho->quantidade = 0;
    arquivo = fopen(caminho, "r");
    if (!arquivo) {
        reportarErroCSV(0, "arquivo inacessivel");
        return 0;
    }

    status = lerLinha(arquivo, linha, sizeof linha);
    if (status != 1) {
        linhaErro = 1;
        erro = "cabecalho ausente ou linha longa";
        goto finalizar;
    }

    /* Remove somente o BOM UTF-8 inicial, quando presente. */
    if (strlen(linha) >= 3 &&
        (unsigned char)linha[0] == 0xEF &&
        (unsigned char)linha[1] == 0xBB &&
        (unsigned char)linha[2] == 0xBF) {
        memmove(linha, linha + 3, strlen(linha + 3) + 1);
    }

    linha[strcspn(linha, "\r\n")] = '\0';
    if (strcmp(linha, CABECALHO_CSV) != 0) {
        linhaErro = 1;
        erro = "cabecalho/schema";
        goto finalizar;
    }

    while ((status = lerLinha(arquivo, linha, sizeof linha)) == 1) {
        Carta carta = {0};
        ++numeroLinha;

        if (linha[0] == '\r' || linha[0] == '\n' || linha[0] == '\0') {
            erro = "linha vazia";
            goto finalizar;
        }

        memset(campos, 0, sizeof campos);
        if (!separarCamposCSV(linha, campos)) {
            erro = "formato ou quantidade de campos";
            goto finalizar;
        }

        if (!converterInteiro(campos[0], &carta.id)) {
            erro = "id";
            goto finalizar;
        }
        if (!converterClasse(campos[4], &carta.classe)) {
            erro = "classe";
            goto finalizar;
        }
        if (!converterInteiro(campos[5], &carta.raciocinio)) {
            erro = "raciocinio";
            goto finalizar;
        }
        if (!converterInteiro(campos[6], &carta.programacao)) {
            erro = "programacao";
            goto finalizar;
        }
        if (!converterInteiro(campos[7], &carta.matematica)) {
            erro = "matematica";
            goto finalizar;
        }
        if (!converterInteiro(campos[8], &carta.conhecimento)) {
            erro = "conhecimento";
            goto finalizar;
        }

        if (temporario.quantidade >= MAX_CARTAS) {
            erro = "quantidade de cartas excedida";
            goto finalizar;
        }
        if (strcmp(campos[9], "modelo") != 0 &&
            strcmp(campos[9], "super_trunfo") != 0) {
            erro = "tipo_carta";
            goto finalizar;
        }

        if (strlen(campos[1]) >= sizeof carta.empresa ||
            strlen(campos[2]) >= sizeof carta.modelo ||
            strlen(campos[3]) >= sizeof carta.caracteristicas) {
            erro = "campo de texto excede limite";
            goto finalizar;
        }

        memcpy(carta.empresa, campos[1], strlen(campos[1]) + 1);
        memcpy(carta.modelo, campos[2], strlen(campos[2]) + 1);
        memcpy(carta.caracteristicas, campos[3], strlen(campos[3]) + 1);
        carta.super_trunfo = strcmp(campos[9], "super_trunfo") == 0;

        if (!validarCarta(&carta)) {
            erro = "campo obrigatorio, range ou flag";
            goto finalizar;
        }

        for (int i = 0; i < temporario.quantidade; ++i) {
            if (temporario.cartas[i].id == carta.id) {
                erro = "id duplicado";
                goto finalizar;
            }
        }

        if (carta.super_trunfo)
            ++quantidadeSuper;
        ++classes[carta.classe];
        temporario.cartas[temporario.quantidade++] = carta;
    }

    if (status == -1) {
        linhaErro = numeroLinha + 1;
        erro = "linha excede tamanho maximo";
        goto finalizar;
    }
    if (ferror(arquivo)) {
        linhaErro = numeroLinha + 1;
        erro = "falha de leitura do arquivo";
        goto finalizar;
    }

    if (temporario.quantidade != MAX_CARTAS || quantidadeSuper != 1 ||
        classes[CLASSE_A] != 5 || classes[CLASSE_B] != 6 ||
        classes[CLASSE_C] != 9 || classes[CLASSE_D] != 14) {
        erro = "quantidade total, Super Trunfo ou distribuicao de classes";
        goto finalizar;
    }

    /* Publica o resultado somente depois da validacao completa. */
    *baralho = temporario;
    sucesso = 1;

finalizar:
    fclose(arquivo);
    if (!sucesso)
        reportarErroCSV(linhaErro ? linhaErro : numeroLinha, erro);

    return sucesso;
}
void embaralharBaralho(Baralho *baralho)
{
    if (!baralho || baralho->quantidade<0 || baralho->quantidade>MAX_CARTAS || baralho->quantidade<=1) return;
    for (int i=baralho->quantidade-1;i>0;i--) {
        int j=rand()%(i+1); Carta t=baralho->cartas[i];
        baralho->cartas[i]=baralho->cartas[j]; baralho->cartas[j]=t;
    }
}
int distribuirCartas(Baralho *baralho, Jogador *jogadores, int quantidade_jogadores)
{
    if (!baralho || !jogadores || quantidade_jogadores!=MAX_JOGADORES ||
        baralho->quantidade!=MAX_CARTAS || jogadores[0].quantidade_cartas!=0 ||
        jogadores[1].quantidade_cartas!=0) return 0;
    for (int i=0;i<MAX_CARTAS;i++) {
        if (!validarCarta(&baralho->cartas[i]) || baralho->cartas[i].id<=0) return 0;
        for (int j=0;j<i;j++) if (baralho->cartas[i].id==baralho->cartas[j].id) return 0;
    }
    Jogador temporarios[MAX_JOGADORES]={jogadores[0],jogadores[1]};
    for (int i=0;i<MAX_CARTAS;i++)
        if (!adicionarCarta(&temporarios[i%quantidade_jogadores],baralho->cartas[i])) return 0;
    if (temporarios[0].quantidade_cartas!=17 || temporarios[1].quantidade_cartas!=17) return 0;
    jogadores[0]=temporarios[0]; jogadores[1]=temporarios[1];
    baralho->quantidade=0;
    return 1;
}
void liberarBaralho(Baralho *baralho)
{
    if (baralho) baralho->quantidade=0;
}
