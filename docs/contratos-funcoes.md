# Contratos das funções

Os cabeçalhos em includes/ são a referência normativa dos contratos públicos.

## Convenção geral

- Funções de operação que retornam int usam 1 para sucesso e 0 para falha, salvo exceções documentadas.
- Funções de comparação podem usar valores específicos para distinguir erro de resultado.
- Ponteiros de entrada nulos devem ser tratados conforme o contrato da função.
- Funções void não comunicam sucesso; devem ignorar entradas inválidas sem causar acesso inválido.

## Cartas

| Função | Retorno |
|---|---|
| obterPontuacao | Pontuação (0–100); -1 para atributo inválido. |
| compararCartas | 1 primeira vence; -1 segunda vence; 0 empate; -2 atributo inválido. |
| verificarSuperTrunfo | 1 se especial; 0 caso contrário. |
| obterClasseCarta | Classe A–D; CLASSE_INVALIDA para ponteiro nulo. |
| validarCarta | 1 se campos válidos; 0 caso contrário. |

## Jogadores

| Função | Retorno |
|---|---|
| inicializarJogador | void; inicializa, usando nome vazio se nome nulo. |
| adicionarCarta | 1 adicionou; 0 ponteiro nulo ou limite atingido. |
| removerCarta | 1 removeu; 0 índice/ponteiro inválido. |
| obterCartaTopo | 1 copiou; 0 vazio ou argumentos inválidos. |
| retirarCartaTopo | 1 copiou e removeu; 0 em falha. |
| liberarJogador | void; esvazia logicamente o jogador. |

## Baralho

| Função | Retorno |
|---|---|
| carregarBaralhoCSV | 1 carregou 34 cartas válidas e uma Super Trunfo classe A; 0 em falha. |
| embaralharBaralho | void; embaralha sem alterar quantidade. |
| distribuirCartas | 1 distribuiu igualmente entre dois jogadores vazios; 0 em falha. |
| liberarBaralho | void; zera quantidade. |

## Jogo

| Função | Retorno |
|---|---|
| inicializarJogo | 1 inicializou; 0 em falha. |
| executarRodada / executarDesempate | 1 etapa resolvida; 0 em falha/estado inválido. |
| determinarEmpatados | Quantidade de empatados; -1 estado/argumentos inválidos. |
| adicionarCartaDisputa | 1 adicionou; 0 em falha. |
| entregarMonteDisputa | 1 transferiu integralmente; 0 sem transferência parcial. |
| obterCartaConfronto | 1 obteve; 0 em falha. Carta reutilizada não deve entrar duas vezes no monte. |
| verificarJogadorDesempate | 1 participa; 0 caso contrário. |
| verificarFimJogo | 1 terminou; 0 continua; -1 estado inválido. |
| determinarVencedorJogo | Ponteiro do vencedor ou NULL. |

Funções do motor ainda não implementadas devem respeitar esses contratos ao serem concluídas. Um stub não deve sinalizar sucesso fictício.

## Complementos do motor implementado

- `executarRodada`: compara as cartas do topo, recolhe ambas ao monte de disputa, remove-as das mãos e, se houver vencedor, transfere o monte. Se empatar, registra os dois participantes e deixa a disputa para `executarDesempate`.
- `executarDesempate`: reutiliza cartas enquanto houver empate. Depois de tentar todos os quatro atributos sem resolução, recolhe esse par uma única vez e revela um novo par.
- `verificarFimJogo`: valida a conservação das cartas considerando mãos e monte de disputa, e reconhece vencedor quando uma mão contém as 34 cartas.
- `entregarMonteDisputa`: embaralha a ordem do monte antes da transferência integral ao vencedor.

## Loader e distribuição — garantias de validação

`carregarBaralhoCSV` valida cabeçalho/schema, encoding BOM inicial, CSV delimitado/aspas/escape, tamanho da linha e dos campos, conversões numéricas completas, IDs únicos e composição. O destino fica com quantidade zero em falha e recebe o array temporário apenas no sucesso. `distribuirCartas` valida cartas e IDs duplicados antes de mutar; prepara cópias dos jogadores e publica ambas as mãos (17/17) somente após sucesso, consumindo o baralho no final.
