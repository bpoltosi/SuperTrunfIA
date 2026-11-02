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
