# Interface de terminal e fluxo interativo — V1

Este documento registra as decisões para a experiência de terminal da versão **V1 Core** do SuperTrunfIA. A interface prioriza clareza, simplicidade e acompanhamento gradual da partida; não é uma GUI.

## Princípios de apresentação

- Terminal textual, simples e legível.
- Não exigir cores, animações ou recursos específicos do terminal.
- Os dois jogadores usam o mesmo terminal; não há necessidade de ocultar as cartas entre eles.
- Exibir cartas com nome, empresa, classe e os quatro atributos: Raciocínio, Programação, Matemática e Conhecimento.
- Exibir o número de cartas de cada jogador para que o progresso fique claro.
- Separar apresentação/entrada da lógica de jogo, centralizando os prints e prompts no módulo de interface.

## Fases da partida

### 1. Preparação e sorteio inicial

Como ainda não há vencedor de rodada anterior, um sorteio de **par ou ímpar** define o jogador que terá o direito de escolher o primeiro atributo. A interface apresenta a escolha de par ou ímpar, o resultado aleatório e quem inicia a escolha.

### 2. Escolha do atributo

O jogador que tem o direito de escolher seleciona uma das quatro opções:
1. Raciocínio
2. Programação
3. Matemática
4. Conhecimento

Na primeira rodada, o direito vem do sorteio par ou ímpar. Nas rodadas principais posteriores, o vencedor da rodada anterior escolhe o atributo.

### 3. Combate/revelação

Após o atributo ser escolhido, o jogo revela as cartas do topo dos montes dos dois jogadores. A apresentação inclui, no mínimo:
- Número da rodada.
- Atributo disputado.
- Nome/modelo e empresa de cada carta.
- Classe de cada carta.
- Pontuação dos quatro atributos.
- Quantidade de cartas de cada jogador antes ou durante o confronto.

O resultado da comparação pode ser exibido em uma etapa própria, de forma objetiva.

### 4. Desempate

Se o combate principal empatar, inicia-se o desempate sem abrir uma nova rodada principal.

- O **mesmo jogador que escolheu o atributo do combate principal** escolhe o atributo do primeiro desempate e dos desempates seguintes.
- A escolha pode ser diferente do atributo que causou o empate; não há obrigação de repetir o atributo anterior.
- As cartas de desempate seguem as regras já definidas para reutilização: cartas reveladas para desempate não são adicionadas novamente ao monte de disputa.
- Se houver novo empate, repete-se a fase de escolha de atributo e combate entre os jogadores ainda empatados, mantendo o direito de escolha com o jogador original.

### 5. Resultado da rodada

Depois de determinado o vencedor, a interface mostra claramente quem venceu a rodada e informa as quantidades atualizadas de cartas dos dois jogadores. O monte de disputa é transferido integralmente de acordo com as regras vigentes.

O vencedor da rodada passa a ter o direito de escolher o atributo da próxima rodada principal.

### 6. Repetição do ciclo

O fluxo padrão segue de forma cíclica:

**Escolha do atributo → Combate → Desempate (se necessário) → Resultado/contagem → Próxima escolha**

A escolha de atributo só acontece no começo de uma rodada principal ou durante um desempate, não entre os passos internos de uma disputa já em andamento.

### 7. Encerramento

Quando um jogador possuir todas as 34 cartas, o ciclo é interrompido. A interface mostra a mensagem de fim de jogo, o campeão, a quantidade final de cartas por jogador e, se disponível, o total de rodadas disputadas.

## Controles de avanço

Nos pontos de pausa da interface, o jogador pode usar:

- **Início obrigatório em modo manual:** toda partida começa com entradas e decisões dos jogadores; não existe inicialização direta em simulação.
- **Enter:** avançar para a próxima etapa do fluxo normal, mantendo a partida interativa.
- **P ou p:** nos pontos de pausa durante a partida, ativar o modo de simulação automática, que automatiza as escolhas de atributo e executa as rodadas restantes até que um jogador vença.

O comando de simulação é uma mudança de ritmo, não uma segunda implementação do jogo. O modo automático deve reutilizar as funções do motor, incluindo comparação, Super Trunfo, empate/desempate, transferência do monte e verificação de vitória. As escolhas de atributo que seriam feitas pelos jogadores são selecionadas automaticamente (aleatoriamente) para fins de simulação.

A simulação é uma mudança de ritmo, não uma segunda implementação do jogo. A tecla P/p não deve simular apenas prints ou resultados fictícios: todas as etapas e mudanças no estado dos jogadores devem ocorrer efetivamente no motor.

## Prints de referência (wireframes)

### Sorteio de quem começa
```text
============================================
              SUPERTRUNFIA
============================================

Definição de quem escolhe o primeiro atributo
Jogador 1: escolha PAR ou ÍMPAR
[1] PAR
[2] ÍMPAR

Escolha: 2

Resultado do sorteio: 7 (ÍMPAR)
Jogador 1 venceu o sorteio e escolhe o atributo.

============================================
```

### Escolha de atributo
```text
============================================
RODADA 1 | Jogador 1 escolhe
============================================
[1] Raciocínio
[2] Programação
[3] Matemática
[4] Conhecimento
Escolha:
============================================
```

### Combate
```text
============================================
COMBATE | RODADA 1 | ATRIBUTO: MATEMÁTICA
============================================
JOGADOR 1                         JOGADOR 2
Cartas: 17                        Cartas: 17
Modelo: Carta A                    Modelo: Carta B
Empresa: Empresa A                 Empresa: Empresa B
Classe: A                          Classe: B
Raciocínio: 90                     Raciocínio: 85
Programação: 80                    Programação: 91
Matemática: 95                     Matemática: 88
Conhecimento: 82                   Conhecimento: 89
============================================
```

### Resultado e controle
```text
============================================
RESULTADO DA RODADA 1: JOGADOR 1 VENCE
============================================
Cartas do Jogador 1: 19
Cartas do Jogador 2: 15

[ENTER] Continuar manual | [P] Ativar simulação até o fim
============================================
```

Os valores e nomes nos exemplos são ilustrativos, não dados do CSV.

## Sugestão de responsabilidades do módulo de interface

Os nomes abaixo são propostas para organizar a implementação; os contratos finais devem ser conferidos e definidos nos headers antes de codificar.

| Função sugerida | Responsabilidade |
|---|---|
| `exibirInicioJogo()` | Apresentar o jogo e preparar a partida |
| `exibirEscolhaParImpar()` | Solicitar a opção do sorteio inicial |
| `exibirResultadoSorteio()` | Apresentar o resultado e o jogador que começa |
| `exibirEscolhaAtributo()` | Exibir opções e coletar atributo |
| `exibirCombate()` | Mostrar cartas e atributos |
| `exibirEscolhaDesempate()` | Coletar novo atributo para desempate |
| `exibirResultadoDesempate()` | Apresentar resultado do desempate |
| `exibirResultadoRodada()` | Apresentar vencedor da rodada |
| `exibirContagemCartas()` | Mostrar contagem dos montes dos jogadores |
| `aguardarEnter()` | Pausar para avanço manual |
| `verificarModoSimulacao()` | Ler Enter ou P/p nos pontos de pausa |
| `executarSimulacao()` | Orquestrar avanço automático usando o mesmo motor |
| `exibirFimJogo()` | Apresentar campeão e resultado final |

As funções listadas são diretrizes de interface. A implementação poderá ajustar nomes e assinaturas para respeitar os headers e a arquitetura existente, sem alterar as regras aqui definidas.

## Implementação concluída — comportamento da primeira rodada

A primeira rodada é obrigatoriamente manual: o usuário participa do sorteio par/ímpar e escolhe o atributo. A opção P/p de simulação é oferecida apenas na pausa após a resolução dessa primeira rodada, garantindo que a partida não comece em modo automático. Se ativada, a simulação segue até o fim pelo mesmo motor de jogo.


## Correcoes de interface e compatibilidade (issues #52-#54)

- O sorteio inicial utiliza a mesma codificacao da entrada: `1 = PAR` e `2 = IMPAR`. A comparacao entre escolha e resultado determina diretamente o vencedor; valores fora desse dominio sao invalidos.
- Antes de solicitar um atributo, a interface identifica o jogador responsavel pela rodada. A mensagem e reapresentada depois da limpeza do terminal, inclusive ao iniciar a simulacao; no desempate, o jogador que escolheu o atributo da rodada que empatou continua responsavel pelas escolhas seguintes.
- Os fontes sao mantidos em UTF-8. No Windows, o programa configura locale e entrada/saida do console para UTF-8; em outros sistemas, respeita o locale do ambiente. Mensagens com travessao e acentos devem ser verificadas em terminal UTF-8.
