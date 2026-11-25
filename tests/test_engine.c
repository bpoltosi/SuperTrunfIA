#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jogo.h"
#include "util.h"

static Carta makeCard(int id, int value)
{
    Carta c={0}; c.id=id; strcpy(c.empresa,"Teste"); strcpy(c.modelo,"Card");
    strcpy(c.caracteristicas,"Teste engine"); c.classe=CLASSE_D;
    c.raciocinio=value; c.programacao=value; c.matematica=value; c.conhecimento=value;
    return c;
}
static void preparar(Jogo *j, int v0, int v1)
{
    memset(j,0,sizeof *j); j->quantidade_jogadores=2; j->jogo_ativo=1; j->rodada_atual=1;
    inicializarJogador(&j->jogadores[0],1,"P1"); inicializarJogador(&j->jogadores[1],2,"P2");
    for(int i=0;i<17;i++) {
        Carta a=makeCard(i+1, i==0?v0:40+i);
        Carta b=makeCard(i+18, i==0?v1:40+i);
        assert(adicionarCarta(&j->jogadores[0],a)); assert(adicionarCarta(&j->jogadores[1],b));
    }
}
static void testRoundWin(void)
{
    Jogo j; preparar(&j,90,50);
    assert(executarRodada(&j,RACIOCINIO));
    assert(j.jogadores[0].quantidade_cartas==18 && j.jogadores[1].quantidade_cartas==16);
    assert(j.monte_disputa.quantidade==0 && j.jogador_atual==0);
    assert(verificarFimJogo(&j)==0);
    finalizarJogo(&j);
}
static void testTieAndReuse(void)
{
    Jogo j; preparar(&j,50,50);
    j.jogadores[0].cartas[1].programacao=60;
    j.jogadores[1].cartas[1].programacao=80;
    assert(executarRodada(&j,RACIOCINIO));
    assert(j.jogadores[0].quantidade_cartas==16 && j.jogadores[1].quantidade_cartas==16);
    assert(j.monte_disputa.quantidade==2);
    assert(!adicionarCartaDisputa(&j,j.monte_disputa.cartas[0]));
    assert(!entregarMonteDisputa(&j,-1) && j.monte_disputa.quantidade==2);
    int empatados[2]; assert(determinarEmpatados(&j,RACIOCINIO,empatados)==2);
    assert(empatados[0]==0 && empatados[1]==1);
    assert(verificarJogadorDesempate(&j,0) && verificarJogadorDesempate(&j,1));
    assert(executarDesempate(&j,RACIOCINIO));
    assert(j.monte_disputa.quantidade==2);
    assert(j.jogadores[0].quantidade_cartas==16 && j.jogadores[1].quantidade_cartas==16);
    assert(j.estados[0].tem_carta_reutilizada && j.estados[1].tem_carta_reutilizada);
    Carta reused0,reused1; int add0,add1;
    assert(obterCartaConfronto(&j,0,&reused0,&add0) && !add0);
    assert(obterCartaConfronto(&j,1,&reused1,&add1) && !add1);
    assert(reused0.id==2 && reused1.id==19);
    assert(executarDesempate(&j,PROGRAMACAO));
    assert(j.monte_disputa.quantidade==0);
    assert(j.jogadores[0].quantidade_cartas+j.jogadores[1].quantidade_cartas==34);
    assert(j.jogadores[1].quantidade_cartas==19);
    assert(j.jogador_atual==1);
    assert(!verificarJogadorDesempate(&j,0) && !verificarJogadorDesempate(&j,1));
    finalizarJogo(&j);
}
static void testEmpateEmTodosAtributos(void)
{
    Jogo j; preparar(&j,50,50);
    j.jogadores[0].cartas[2].programacao=60;
    j.jogadores[1].cartas[2].programacao=80;
    assert(executarRodada(&j,RACIOCINIO));
    assert(executarDesempate(&j,RACIOCINIO));
    assert(executarDesempate(&j,PROGRAMACAO));
    assert(executarDesempate(&j,MATEMATICA));
    assert(executarDesempate(&j,CONHECIMENTO));
    /* O primeiro par empatado Ã© recolhido sem duplicaÃ§Ã£o, e novas cartas avanÃ§am. */
    assert(j.monte_disputa.quantidade==4);
    assert(j.jogadores[0].quantidade_cartas==15 && j.jogadores[1].quantidade_cartas==15);
    assert(!j.estados[0].tem_carta_reutilizada && !j.estados[1].tem_carta_reutilizada);
    assert(executarDesempate(&j,PROGRAMACAO));
    assert(j.jogadores[0].quantidade_cartas==14 && j.jogadores[1].quantidade_cartas==20);
    assert(j.monte_disputa.quantidade==0);
    finalizarJogo(&j);
}
static void testTieWhenPlayersRunOut(void)
{
    Jogo j={0};
    j.quantidade_jogadores=2; j.jogo_ativo=1;
    inicializarJogador(&j.jogadores[0],1,"P1");
    inicializarJogador(&j.jogadores[1],2,"P2");

    /* Um jogador sem cartas apos o empate perde por impossibilidade de continuar. */
    assert(adicionarCarta(&j.jogadores[0],makeCard(1,50)));
    for(int i=0;i<33;i++) assert(adicionarCarta(&j.jogadores[1],makeCard(i+2,i==0?50:60+(i%30))));
    assert(executarRodada(&j,RACIOCINIO));
    assert(j.jogadores[0].quantidade_cartas==0);
    assert(j.jogadores[1].quantidade_cartas==34);
    assert(j.monte_disputa.quantidade==0);
    assert(verificarFimJogo(&j)==1);
    assert(determinarVencedorJogo(&j)==&j.jogadores[1]);
    finalizarJogo(&j);

    /* Se ambos esgotam as maos empatando, todas as cartas ficam no monte: empate final. */
    memset(&j,0,sizeof j);
    j.quantidade_jogadores=2; j.jogo_ativo=1;
    inicializarJogador(&j.jogadores[0],1,"P1");
    inicializarJogador(&j.jogadores[1],2,"P2");
    assert(adicionarCarta(&j.jogadores[0],makeCard(1,50)));
    assert(adicionarCarta(&j.jogadores[1],makeCard(2,50)));
    for(int i=0;i<32;i++) j.monte_disputa.cartas[i]=makeCard(i+3,70+(i%30));
    j.monte_disputa.quantidade=32;
    j.estados[0].participa_desempate=1; j.estados[1].participa_desempate=1;
    j.estados[0].tem_carta_reutilizada=1; j.estados[1].tem_carta_reutilizada=1;
    j.estados[0].carta_reutilizada=j.jogadores[0].cartas[0];
    j.estados[1].carta_reutilizada=j.jogadores[1].cartas[0];
    j.estados[0].atributos_tentados=7; j.estados[1].atributos_tentados=7;
    assert(executarDesempate(&j,CONHECIMENTO));
    assert(j.jogadores[0].quantidade_cartas==0 && j.jogadores[1].quantidade_cartas==0);
    assert(j.monte_disputa.quantidade==34);
    assert(verificarFimJogo(&j)==1);
    assert(determinarVencedorJogo(&j)==NULL);
    finalizarJogo(&j);
}

static void testLifecycleFim(void)
{
    Jogo j={0};
    assert(verificarFimJogo(&j)==-1);
    j.quantidade_jogadores=2;
    inicializarJogador(&j.jogadores[0],1,"P1");
    inicializarJogador(&j.jogadores[1],2,"P2");
    for(int i=0;i<17;i++) {
        assert(adicionarCarta(&j.jogadores[0],makeCard(i+1,50)));
        assert(adicionarCarta(&j.jogadores[1],makeCard(i+18,60)));
    }
    assert(verificarFimJogo(&j)==0);
    for(int i=0;i<17;i++)
        assert(adicionarCarta(&j.jogadores[0],j.jogadores[1].cartas[i]));
    j.jogadores[1].quantidade_cartas=0;
    assert(verificarFimJogo(&j)==1 && determinarVencedorJogo(&j)==&j.jogadores[0]);
    assert(!inicializarJogo(NULL,2) && !inicializarJogo(&j,1));
    assert(inicializarJogo(&j,2));
    assert(j.jogo_ativo && j.jogadores[0].quantidade_cartas==17);
    finalizarJogo(&j); finalizarJogo(&j); finalizarJogo(NULL);
    assert(!j.jogo_ativo && j.quantidade_jogadores==0);
}
static void testDesempateValidation(void)
{
    Jogo j;
    preparar(&j,70,50);
    int invalidos[2]={0,2};
    atualizarParticipantesDesempate(&j,invalidos,2);
    assert(!verificarJogadorDesempate(&j,0) && !verificarJogadorDesempate(&j,1));

    int repetidos[2]={0,0};
    atualizarParticipantesDesempate(&j,repetidos,2);
    assert(!verificarJogadorDesempate(&j,0) && !verificarJogadorDesempate(&j,1));

    int validos[2]={0,1};
    atualizarParticipantesDesempate(&j,validos,2);
    assert(verificarJogadorDesempate(&j,0) && verificarJogadorDesempate(&j,1));

    j.estados[0].tem_carta_reutilizada=1;
    j.estados[0].carta_reutilizada=makeCard(999,50);
    Carta carta; int adicionar;
    assert(!obterCartaConfronto(&j,0,&carta,&adicionar));
    finalizarJogo(&j);
}

static void testStateIntegrity(void)
{
    Jogo j;
    preparar(&j,80,40);
    assert(verificarFimJogo(&j)==0);
    j.estados[0].participa_desempate=2;
    assert(verificarFimJogo(&j)==-1);
    j.estados[0].participa_desempate=0;
    j.estados[0].tem_carta_reutilizada=2;
    assert(verificarFimJogo(&j)==-1);
    j.estados[0].tem_carta_reutilizada=0;
    assert(verificarFimJogo(&j)==0);
    j.estados[0].tem_carta_reutilizada=1;
    j.estados[0].participa_desempate=1;
    j.estados[0].carta_reutilizada=j.jogadores[0].cartas[0];
    assert(verificarFimJogo(&j)==-1);
    memset(&j.estados[0],0,sizeof j.estados[0]);
    assert(verificarFimJogo(&j)==0);
    j.jogo_ativo=2;
    assert(verificarFimJogo(&j)==-1);
    j.jogo_ativo=1;

    int id_original=j.jogadores[1].cartas[0].id;
    j.jogadores[1].cartas[0].id=j.jogadores[0].cartas[0].id;
    assert(verificarFimJogo(&j)==-1);
    j.jogadores[1].cartas[0].id=id_original;
    assert(verificarFimJogo(&j)==0);

    char modelo_original[sizeof j.jogadores[0].cartas[0].modelo];
    memcpy(modelo_original,j.jogadores[0].cartas[0].modelo,sizeof modelo_original);
    memset(j.jogadores[0].cartas[0].modelo,'X',sizeof j.jogadores[0].cartas[0].modelo);
    assert(verificarFimJogo(&j)==-1);
    memcpy(j.jogadores[0].cartas[0].modelo,modelo_original,sizeof modelo_original);
    assert(verificarFimJogo(&j)==0);

    j.monte_disputa.cartas[0]=j.jogadores[0].cartas[0];
    j.monte_disputa.quantidade=1;
    --j.jogadores[0].quantidade_cartas;
    assert(verificarFimJogo(&j)==-1);
    finalizarJogo(&j);
}

static void testTransferAtomicFail(void)
{
    Jogo j={0}; j.quantidade_jogadores=2; j.jogo_ativo=1;
    inicializarJogador(&j.jogadores[0],1,"P1"); inicializarJogador(&j.jogadores[1],2,"P2");
    Carta a=makeCard(1,50), b=makeCard(2,60), c=makeCard(3,70);
    assert(adicionarCarta(&j.jogadores[0],a) && adicionarCarta(&j.jogadores[0],b));
    j.monte_disputa.cartas[0]=c; j.monte_disputa.cartas[1]=c; j.monte_disputa.quantidade=2;
    assert(!entregarMonteDisputa(&j,0));
    assert(j.jogadores[0].quantidade_cartas==2 && j.monte_disputa.quantidade==2);
    assert(!entregarMonteDisputa(&j,9));
    finalizarJogo(&j);

    preparar(&j,80,40);
    j.monte_disputa.cartas[0]=j.jogadores[1].cartas[0];
    j.monte_disputa.quantidade=1;
    --j.jogadores[0].quantidade_cartas;
    int quantidade0=j.jogadores[0].quantidade_cartas;
    int quantidade1=j.jogadores[1].quantidade_cartas;
    assert(!entregarMonteDisputa(&j,0));
    assert(j.jogadores[0].quantidade_cartas==quantidade0);
    assert(j.jogadores[1].quantidade_cartas==quantidade1);
    assert(j.monte_disputa.quantidade==1);
    finalizarJogo(&j);
}
static void executarSimulacaoTeste(unsigned seed)
{
    Jogo j; srand(seed); assert(inicializarJogo(&j,2));
    assert(j.jogo_ativo && j.jogadores[0].quantidade_cartas==17 && j.jogadores[1].quantidade_cartas==17);
    int guard=0;
    while(verificarFimJogo(&j)==0 && guard++<20000) {
        Atributo a=(Atributo)(rand()%QUANTIDADE_ATRIBUTOS);
        int resultado; Carta c0,c1;
        assert(obterCartaTopo(&j.jogadores[0],&c0)); assert(obterCartaTopo(&j.jogadores[1],&c1));
        resultado=compararCartasComSuperTrunfo(c0,c1,a);
        assert(executarRodada(&j,a));
        if(resultado==0) {
            int ties=0;
            while(verificarJogadorDesempate(&j,0) && verificarJogadorDesempate(&j,1) && ties++<100) {
                Atributo t=(Atributo)(rand()%QUANTIDADE_ATRIBUTOS);
                Carta a0,a1; int x,y;
                assert(obterCartaConfronto(&j,0,&a0,&x)); assert(obterCartaConfronto(&j,1,&a1,&y));
                int r=compararCartasComSuperTrunfo(a0,a1,t);
                assert(executarDesempate(&j,t));
                if(r!=0) break;
            }
            assert(ties<100);
        }
        assert(j.jogadores[0].quantidade_cartas+j.jogadores[1].quantidade_cartas+
               j.monte_disputa.quantidade==MAX_CARTAS);
    }
    assert(verificarFimJogo(&j)==1);
    assert(determinarVencedorJogo(&j)!=NULL);
    assert(guard<20000);
    finalizarJogo(&j);
}
static void testSorteioParImpar(void)
{
    assert(determinarVencedorSorteio(1, 1) == 0);
    assert(determinarVencedorSorteio(1, 2) == 1);
    assert(determinarVencedorSorteio(2, 2) == 0);
    assert(determinarVencedorSorteio(2, 1) == 1);
    assert(determinarVencedorSorteio(0, 1) == -1);
    assert(determinarVencedorSorteio(1, 3) == -1);
}

int main(void)
{
    testSorteioParImpar(); testLifecycleFim(); testRoundWin(); testTieAndReuse(); testEmpateEmTodosAtributos(); testTieWhenPlayersRunOut(); testStateIntegrity(); testDesempateValidation(); testTransferAtomicFail();
    for(unsigned seed=1;seed<=5;seed++) executarSimulacaoTeste(seed);
    puts("TESTES DO MOTOR: TODOS PASSARAM (5 partidas simuladas)");
    return 0;
}
