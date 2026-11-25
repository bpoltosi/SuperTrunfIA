#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "carta.h"
#include "jogador.h"
#include "baralho.h"

#define CSV_HEADER "id,empresa,modelo,caracteristicas,classe,raciocinio,programacao,matematica,conhecimento,tipo_carta\n"
static Carta cartaValida(int id, int r, int p, int m, int c, ClasseCarta classe, int super)
{
    Carta carta={0}; carta.id=id; strcpy(carta.empresa,"Teste"); strcpy(carta.modelo,"Modelo");
    strcpy(carta.caracteristicas,"Caracteristica"); carta.classe=classe;
    carta.raciocinio=r; carta.programacao=p; carta.matematica=m; carta.conhecimento=c;
    carta.super_trunfo=super; return carta;
}
static void testarCarta(void)
{
    Carta a=cartaValida(1,90,80,70,60,CLASSE_A,0);
    Carta b=cartaValida(2,89,81,70,61,CLASSE_B,0);
    Carta super=cartaValida(3,90,70,99,80,CLASSE_A,1), invalid=a;
    assert(validarCarta(&a) && !validarCarta(NULL));
    assert(obterClasseCarta(&a)==CLASSE_A && obterClasseCarta(NULL)==CLASSE_INVALIDA);
    assert(obterPontuacao(a,RACIOCINIO)==90 && obterPontuacao(a,PROGRAMACAO)==80);
    assert(obterPontuacao(a,MATEMATICA)==70 && obterPontuacao(a,CONHECIMENTO)==60);
    assert(obterPontuacao(a,(Atributo)99)==-1);
    assert(compararCartas(a,b,RACIOCINIO)==1 && compararCartas(a,b,PROGRAMACAO)==-1);
    assert(compararCartas(a,b,MATEMATICA)==0 && compararCartas(a,b,CONHECIMENTO)==-1);
    assert(compararCartas(a,b,(Atributo)99)==-2);
    assert(verificarSuperTrunfo(super) && !verificarSuperTrunfo(a));
    b.conhecimento=99;
    assert(compararCartas(super,b,CONHECIMENTO)==-1);
    assert(compararCartasComSuperTrunfo(super,b,CONHECIMENTO)==1);
    assert(compararCartasComSuperTrunfo(super,a,RACIOCINIO)==0);
    Carta classeAAlta=cartaValida(4,90,70,80,95,CLASSE_A,0);
    assert(compararCartasComSuperTrunfo(super,classeAAlta,CONHECIMENTO)==-1);
    assert(compararCartasComSuperTrunfo(super,super,MATEMATICA)==0);
    invalid.raciocinio=101; assert(!validarCarta(&invalid));
    invalid=a; invalid.id=0; assert(!validarCarta(&invalid));
    invalid=a; invalid.super_trunfo=2; assert(!validarCarta(&invalid));
    invalid=b; invalid.super_trunfo=1; assert(!validarCarta(&invalid));
    invalid=a; invalid.empresa[0]='\0'; assert(!validarCarta(&invalid));
    invalid=a; memset(invalid.modelo,'X',sizeof invalid.modelo); assert(!validarCarta(&invalid));
    invalid=a; memset(invalid.empresa,'X',sizeof invalid.empresa); assert(!validarCarta(&invalid));
    puts("testarCarta: OK");
}
static void testarJogador(void)
{
    Jogador j; Carta c=cartaValida(1,1,2,3,4,CLASSE_D,0), out;
    inicializarJogador(&j,7,"Jogador teste");
    assert(j.id==7 && !strcmp(j.nome,"Jogador teste") && j.quantidade_cartas==0);
    inicializarJogador(NULL,1,"Nulo");
    assert(adicionarCarta(&j,c) && adicionarCarta(&j,c));
    assert(obterCartaTopo(&j,&out) && out.id==1);
    assert(!obterCartaTopo(NULL,&out) && !obterCartaTopo(&j,NULL));
    assert(retirarCartaTopo(&j,&out) && j.quantidade_cartas==1);
    assert(removerCarta(&j,0) && j.quantidade_cartas==0);
    assert(!removerCarta(&j,0) && !retirarCartaTopo(&j,&out));
    for(int i=0;i<MAX_CARTAS;i++) assert(adicionarCarta(&j,c));
    assert(j.quantidade_cartas==MAX_CARTAS && !adicionarCarta(&j,c));
    liberarJogador(&j); assert(j.quantidade_cartas==0 && j.nome[0]=='\0');
    liberarJogador(NULL); puts("testarJogador: OK");
}
static void lerDadosCSV(char linhas[34][1024])
{
    FILE *f=fopen("data/cartas.csv","r"); char linha[1024]; assert(f);
    assert(fgets(linha,sizeof linha,f));
    for(int i=0;i<34;i++){assert(fgets(linhas[i],1024,f));}
    fclose(f);
}
static void escreverCSV(const char *path,const char *header,char linhas[34][1024],int duplicar)
{
    FILE *f=fopen(path,"w"); assert(f);
    fputs(header,f);
    if(duplicar) {
        fputs(linhas[0],f); fputs(linhas[0],f);
        for(int i=2;i<34;i++) fputs(linhas[i],f);
    } else for(int i=0;i<34;i++) fputs(linhas[i],f);
    fclose(f);
}
static void testarCSV(void)
{
    Baralho b={0}; char linhas[34][1024]; lerDadosCSV(linhas);
    assert(carregarBaralhoCSV(&b,"data/cartas.csv") && b.quantidade==34);
    int classes[4]={0}, supers=0; int vistos[35]={0};
    for(int i=0;i<34;i++) {
        Carta c=b.cartas[i]; assert(validarCarta(&c));
        classes[c.classe]++; supers+=c.super_trunfo;
        assert(c.id>0 && c.id<=34 && !vistos[c.id]); vistos[c.id]=1;
    }
    assert(classes[0]==5 && classes[1]==6 && classes[2]==9 && classes[3]==14 && supers==1);
    FILE *f=fopen("tests/bom.csv","wb"); assert(f);
    fputs("\xEF\xBB\xBF",f); fputs(CSV_HEADER,f);
    for(int i=0;i<34;i++) { fputs(linhas[i],f); }
    fclose(f);
    assert(carregarBaralhoCSV(&b,"tests/bom.csv") && b.quantidade==34); remove("tests/bom.csv");
    /* Aspas, vírgulas internas e aspas escapadas seguem o CSV. */
    f=fopen("tests/quoted.csv","w"); assert(f); fputs(CSV_HEADER,f);
    fputs("1,\"Test, Corp\",\"Alan \"\"Turing\"\"\",\"Descricao, com virgula\",A,90,70,99,80,super_trunfo\n",f);
    for(int i=1;i<34;i++) { fputs(linhas[i],f); }
    fclose(f);
    assert(carregarBaralhoCSV(&b,"tests/quoted.csv") && b.quantidade==34);
    assert(!strcmp(b.cartas[0].empresa,"Test, Corp") && !strcmp(b.cartas[0].modelo,"Alan \"Turing\""));
    remove("tests/quoted.csv");
    escreverCSV("tests/header.csv","header-invalido\n",linhas,0);
    assert(!carregarBaralhoCSV(&b,"tests/header.csv") && b.quantidade==0); remove("tests/header.csv");
    escreverCSV("tests/duplicate.csv",CSV_HEADER,linhas,1);
    assert(!carregarBaralhoCSV(&b,"tests/duplicate.csv") && b.quantidade==0); remove("tests/duplicate.csv");
    f=fopen("tests/longfield.csv","w"); assert(f); fputs(CSV_HEADER,f);
    char *comma=strchr(linhas[0],','); assert(comma); fputc(linhas[0][0],f); fputc(',',f);
    for(int i=0;i<60;i++) { fputc('Z',f); }
    fputc(',',f); fputs(comma+1,f);
    for(int i=1;i<34;i++) { fputs(linhas[i],f); }
    fclose(f);
    assert(!carregarBaralhoCSV(&b,"tests/longfield.csv") && b.quantidade==0); remove("tests/longfield.csv");
    f=fopen("tests/long.csv","w"); assert(f); fputs(CSV_HEADER,f);
    for(int i=0;i<1500;i++) { fputc('x',f); }
    fputc('\n',f); fclose(f);
    assert(!carregarBaralhoCSV(&b,"tests/long.csv") && b.quantidade==0); remove("tests/long.csv");
    assert(!carregarBaralhoCSV(&b,"tests/missing.csv") && b.quantidade==0);
    f=fopen("tests/invalid.csv","w"); assert(f); fputs("header-invalido\nlinha-invalida\n",f); fclose(f);
    assert(!carregarBaralhoCSV(&b,"tests/invalid.csv") && b.quantidade==0); remove("tests/invalid.csv");
    assert(carregarBaralhoCSV(&b,"data/cartas.csv"));
    embaralharBaralho(&b); assert(b.quantidade==34);
    memset(vistos,0,sizeof vistos);
    for(int i=0;i<34;i++){assert(b.cartas[i].id>0 && b.cartas[i].id<=34 && !vistos[b.cartas[i].id]);vistos[b.cartas[i].id]=1;}
    Jogador js[2]; inicializarJogador(&js[0],1,"J1"); inicializarJogador(&js[1],2,"J2");
    Carta saved=b.cartas[0]; int saved_id=b.cartas[1].id; b.cartas[0].raciocinio=101;
    assert(!distribuirCartas(&b,js,2) && js[0].quantidade_cartas==0 && js[1].quantidade_cartas==0 && b.quantidade==34);
    b.cartas[0]=saved; b.cartas[1].id=b.cartas[0].id;
    assert(!distribuirCartas(&b,js,2) && js[0].quantidade_cartas==0 && js[1].quantidade_cartas==0 && b.quantidade==34);
    b.cartas[1].id=saved_id;
    assert(distribuirCartas(&b,js,2));
    assert(js[0].quantidade_cartas==17 && js[1].quantidade_cartas==17 && b.quantidade==0);
    assert(!distribuirCartas(&b,js,2));
    liberarBaralho(&b); assert(b.quantidade==0);
    puts("testarCSV/Baralho: OK");
}
int main(void)
{
    testarCarta(); testarJogador(); testarCSV();
    puts("TESTES BASE: TODOS PASSARAM"); return 0;
}
