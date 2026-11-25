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
    if (!fgets(linha, (int)tamanho, arquivo)) return 0;
    size_t n=strlen(linha);
    if (n && linha[n-1]!='\n' && !feof(arquivo)) {
        int c; while ((c=fgetc(arquivo))!='\n' && c!=EOF) { }
        return -1;
    }
    return 1;
}
static int separarCamposCSV(char *linha, char campos[QUANTIDADE_CAMPOS_CSV][TAMANHO_CAMPO_CSV])
{
    int campo=0, pos=0, aspas=0, fechou=0;
    for (size_t i=0;linha[i]!='\0';++i) {
        char c=linha[i];
        if (c=='"') {
            if (aspas && linha[i+1]=='"') {
                if (pos>=TAMANHO_CAMPO_CSV-1) return 0;
                campos[campo][pos++]='"'; ++i;
            } else if (aspas) { aspas=0; fechou=1; }
            else if (pos==0 && !fechou) aspas=1;
            else return 0;
        } else if (c==',' && !aspas) {
            if (campo>=QUANTIDADE_CAMPOS_CSV-1) return 0;
            campos[campo][pos]='\0'; ++campo; pos=0; fechou=0;
        } else if (c!='\r' && c!='\n') {
            if (fechou || pos>=TAMANHO_CAMPO_CSV-1) return 0;
            campos[campo][pos++]=c;
        }
    }
    if (aspas) return 0;
    campos[campo][pos]='\0';
    return campo==QUANTIDADE_CAMPOS_CSV-1;
}
static int converterInteiro(const char *texto, int *valor)
{
    char *fim; long convertido;
    if (!texto || !valor || !texto[0]) return 0;
    errno=0; convertido=strtol(texto,&fim,10);
    if (errno==ERANGE || texto==fim || *fim!='\0' || convertido<INT_MIN || convertido>INT_MAX) return 0;
    *valor=(int)convertido; return 1;
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
    FILE *arquivo; char linha[TAMANHO_LINHA_CSV];
    char campos[QUANTIDADE_CAMPOS_CSV][TAMANHO_CAMPO_CSV];
    Baralho temporario={0}; int quantidade_super=0, classes[4]={0}, numeroLinha=1;
    if (!baralho || !caminho) return 0;
    baralho->quantidade=0;
    arquivo=fopen(caminho,"r");
    if (!arquivo) { reportarErroCSV(0,"arquivo inacessivel"); return 0; }
    int status=lerLinha(arquivo,linha,sizeof linha);
    if (status!=1) { reportarErroCSV(1,"cabecalho ausente ou linha longa"); fclose(arquivo); return 0; }
    if (strlen(linha)>=3 && (unsigned char)linha[0]==0xEF &&
        (unsigned char)linha[1]==0xBB && (unsigned char)linha[2]==0xBF)
        memmove(linha,linha+3,strlen(linha+3)+1);
    linha[strcspn(linha,"\r\n")]='\0';
    if (strcmp(linha,CABECALHO_CSV)!=0) { reportarErroCSV(1,"cabecalho/schema"); fclose(arquivo); return 0; }
    while ((status=lerLinha(arquivo,linha,sizeof linha))==1) {
        ++numeroLinha; Carta carta={0};
        if (linha[0]=='\r' || linha[0]=='\n' || linha[0]=='\0') { reportarErroCSV(numeroLinha,"linha vazia"); fclose(arquivo); return 0; }
        memset(campos,0,sizeof campos);
        if (!separarCamposCSV(linha,campos)) { reportarErroCSV(numeroLinha,"formato ou quantidade de campos"); fclose(arquivo); return 0; }
        if (!converterInteiro(campos[0],&carta.id)) { reportarErroCSV(numeroLinha,"id"); fclose(arquivo); return 0; }
        if (!converterClasse(campos[4],&carta.classe)) { reportarErroCSV(numeroLinha,"classe"); fclose(arquivo); return 0; }
        if (!converterInteiro(campos[5],&carta.raciocinio)) { reportarErroCSV(numeroLinha,"raciocinio"); fclose(arquivo); return 0; }
        if (!converterInteiro(campos[6],&carta.programacao)) { reportarErroCSV(numeroLinha,"programacao"); fclose(arquivo); return 0; }
        if (!converterInteiro(campos[7],&carta.matematica)) { reportarErroCSV(numeroLinha,"matematica"); fclose(arquivo); return 0; }
        if (!converterInteiro(campos[8],&carta.conhecimento)) { reportarErroCSV(numeroLinha,"conhecimento"); fclose(arquivo); return 0; }
        if (temporario.quantidade>=MAX_CARTAS) { reportarErroCSV(numeroLinha,"quantidade de cartas excedida"); fclose(arquivo); return 0; }
        if (strcmp(campos[9],"modelo") && strcmp(campos[9],"super_trunfo")) { reportarErroCSV(numeroLinha,"tipo_carta"); fclose(arquivo); return 0; }
        if (strlen(campos[1])>=sizeof carta.empresa || strlen(campos[2])>=sizeof carta.modelo ||
            strlen(campos[3])>=sizeof carta.caracteristicas) { reportarErroCSV(numeroLinha,"campo de texto excede limite"); fclose(arquivo); return 0; }
        strncpy(carta.empresa,campos[1],sizeof carta.empresa-1);
        strncpy(carta.modelo,campos[2],sizeof carta.modelo-1);
        strncpy(carta.caracteristicas,campos[3],sizeof carta.caracteristicas-1);
        carta.super_trunfo=!strcmp(campos[9],"super_trunfo");
        if (!validarCarta(&carta)) { reportarErroCSV(numeroLinha,"campo obrigatorio, range ou flag"); fclose(arquivo); return 0; }
        for (int i=0;i<temporario.quantidade;i++)
            if (temporario.cartas[i].id==carta.id) { reportarErroCSV(numeroLinha,"id duplicado"); fclose(arquivo); return 0; }
        if (carta.super_trunfo) quantidade_super++;
        classes[carta.classe]++;
        temporario.cartas[temporario.quantidade++]=carta;
    }
    fclose(arquivo);
    if (status==-1) { reportarErroCSV(numeroLinha+1,"linha excede tamanho maximo"); return 0; }
    if (temporario.quantidade!=MAX_CARTAS || quantidade_super!=1 ||
        classes[CLASSE_A]!=5 || classes[CLASSE_B]!=6 || classes[CLASSE_C]!=9 || classes[CLASSE_D]!=14) {
        reportarErroCSV(numeroLinha,"quantidade total, Super Trunfo ou distribuicao de classes");
        return 0;
    }
    *baralho=temporario; /* publica apenas após validar o arquivo inteiro */
    return 1;
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
