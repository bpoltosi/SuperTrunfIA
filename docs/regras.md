# Regras do SuperTrunfIA

## Baralho e classes

O baralho contém **34 cartas**: 33 modelos de IA e a carta especial Alan Turing. Cada carta possui quatro atributos (Raciocínio, Programação, Matemática e Conhecimento), pontuados de 0 a 100, e uma classe explícita (A, B, C ou D).

A classe é um campo próprio da carta, armazenado no CSV e carregado pelo programa. Ela **não é recalculada pela média dos atributos durante a partida**. Isso permite manter a classificação especial de Alan Turing sem alterar suas pontuações.

| Classe | Cartas | Composição |
|---|---:|---|
| A | 5 | 4 modelos + Alan Turing |
| B | 6 | 6 modelos |
| C | 9 | 9 modelos |
| D | 14 | 14 modelos |
| **Total** | **34** | **33 modelos + 1 especial** |

## Alan Turing — Super Trunfo

Alan Turing é uma carta especial, não é contado como modelo de IA nem entra na contagem de modelos por empresa. Seus atributos permanecem **Raciocínio 90, Programação 70, Matemática 99 e Conhecimento 80**. Raciocínio e Matemática são seus dois atributos muito fortes; Programação e Conhecimento permanecem medianos para o balanceamento.

Sua classe é explicitamente A, mesmo que a média aritmética dos atributos seja inferior à faixa numérica usual da classe. O campo de classe prevalece sobre qualquer cálculo de média.

## Comparação e Super Trunfo

- Em uma rodada comum, compara-se o atributo escolhido entre as cartas do topo.
- A maior pontuação vence; valores iguais resultam em empate.
- A carta Super Trunfo vence automaticamente cartas das classes B, C e D.
- Contra uma carta da classe A, não há vitória automática: compara-se o atributo escolhido normalmente.
- A classe consultada é o campo registrado na carta, nunca uma classificação inferida da média.
- Super Trunfo contra outra carta da classe A também exige comparação do atributo escolhido.

## Empates e desempates

- As cartas envolvidas no empate vão para o monte de disputa.
- Os jogadores empatados revelam as próximas cartas para a rodada de desempate.
- As cartas reveladas para desempate são reutilizadas no confronto, sem serem adicionadas novamente ao monte.
- Quem vencer o desempate recebe as cartas acumuladas.
- Em novo empate, o processo continua entre os jogadores ainda empatados.

## Formato do CSV

A ordem das colunas é:

id,empresa,modelo,caracteristicas,classe,raciocinio,programacao,matematica,conhecimento,tipo_carta

- classe: somente A, B, C ou D.
- tipo_carta: modelo ou super_trunfo.
- Deve existir exatamente uma carta super_trunfo, obrigatoriamente da classe A.
- IDs devem ser positivos e únicos.
- Atributos devem ser inteiros entre 0 e 100.
- O carregamento exige exatamente 34 cartas válidas.

## Contratos de retorno

- Operações comuns que retornam int usam 1 para sucesso e 0 para falha, salvo exceções abaixo.
- compararCartas: 1 primeira vence; -1 segunda vence; 0 empate; -2 atributo inválido.
- obterPontuacao: pontuação de 0 a 100; -1 atributo inválido.
- determinarEmpatados: quantidade de empatados; -1 argumentos/estado inválidos.
- verificarFimJogo: 1 terminou; 0 continua; -1 estado inválido.
- determinarVencedorJogo: ponteiro do vencedor ou NULL se ainda não determinado.

Os cabeçalhos em includes/ são a referência normativa dos contratos das funções.

## Fluxo interativo da V1 no terminal

- A V1 terá apresentação textual simples, sem interface gráfica ou animações, com cartas exibidas por nome e atributos.
- Antes da primeira rodada, um sorteio de par ou ímpar define qual jogador escolhe o primeiro atributo.
- Nas rodadas principais seguintes, quem venceu a rodada anterior escolhe o atributo da rodada atual.
- Em um empate, o jogador que escolheu o atributo do confronto principal também escolhe o atributo de cada desempate. Ele pode escolher um atributo diferente do que causou o empate.
- O ciclo de partida é: escolha de atributo → combate/revelação → desempates, se houver → resultado e atualização dos montes → próxima escolha.
- A interface informa a quantidade de cartas de cada jogador, especialmente no começo e no resultado das rodadas.
- **Toda partida começa em modo manual**, sem opção de iniciar diretamente em simulação.
- Durante a partida, nos pontos de pausa previstos, Enter avança mantendo o modo manual; P/p ativa a simulação automática até o fim da partida.
- A simulação automatiza as escolhas de atributos de forma aleatória e reutiliza o mesmo motor e as mesmas regras, sem criar uma lógica de jogo paralela.
- A partida termina quando um jogador conquista todas as cartas; o terminal exibe o campeão e a contagem final.
- A separação entre lógica do jogo e impressão deve ser preservada: apresentação e entrada de terminal ficam encapsuladas no módulo de interface, evitando prints espalhados no motor.

A especificação de etapas, prints e comportamento de entrada está detalhada em [interface-terminal-v1.md](interface-terminal-v1.md).

## Implementação da V1 — detalhes operacionais

- As cartas de cada rodada principal são removidas das mãos e adicionadas uma vez ao monte de disputa, inclusive quando há empate.
- Durante o desempate, a carta revelada permanece temporariamente na mão e é reutilizada em novos empates; só é recolhida ao monte quando o desempate é resolvido.
- Se os quatro atributos forem testados e continuarem empatados, o par de cartas reutilizadas é recolhido uma vez ao monte e novas cartas são reveladas para continuar o desempate, evitando bloqueio infinito.
- Antes de entregar o monte ao vencedor, sua ordem é embaralhada. Isso evita ciclos determinísticos na sequência de cartas; a transferência continua integral e conserva todas as 34 cartas.
- O modo automático usa o mesmo motor que o manual e escolhe atributos aleatoriamente. A primeira rodada exige entrada manual; a simulação só pode ser ativada na pausa depois dela.

## Validação do arquivo de cartas

O loader exige o cabeçalho e a ordem de campos documentados. Aceita BOM UTF-8 inicial, CRLF/LF, campos entre aspas, vírgulas dentro de campos e aspas escapadas (`""`). Rejeita cabeçalho/schema divergente, linhas vazias, linhas acima do buffer, campos acima dos limites das estruturas, valores inválidos, IDs repetidos, contagem e composição incorretas. A carga usa array temporário estático e só publica o baralho completo quando todas as validações passam. Erros são reportados em stderr com linha e validação/campo.

## Desempate sem cartas disponiveis

- Se um empate deixar exatamente um jogador sem cartas para revelar, o adversario recebe imediatamente todo o monte de disputa e vence por impossibilidade de continuacao do oponente.
- Se ambos ficarem sem cartas ao mesmo tempo e as 34 cartas estiverem no monte de disputa, a partida termina em empate tecnico. Nenhum vencedor e inventado e nenhuma carta e descartada.
- Essas condicoes tambem se aplicam quando o par de cartas de desempate empata nos quatro atributos e precisa ser recolhido para revelar um novo par.
