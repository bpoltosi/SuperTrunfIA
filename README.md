# SuperTrunfIA

Jogo de **Super Trunfo desenvolvido em C**, com cartas temáticas de modelos de inteligência artificial. A versão atual (V1 — Core) funciona no terminal, suporta dois jogadores e carrega os dados das cartas de um arquivo CSV.

O projeto prioriza regras explícitas, estruturas estáticas, separação entre motor e interface e validação dos estados da partida.

## Visão geral

- **34 cartas:** 33 modelos de IA e Alan Turing como carta especial Super Trunfo.
- **4 atributos:** Raciocínio, Programação, Matemática e Conhecimento, com valores de 0 a 100.
- **Classes:** A, B, C e D, registradas individualmente em cada carta.
- **Dois jogadores:** 17 cartas iniciais para cada participante.
- **Desempates:** as cartas da disputa ficam em um monte da mesa até a resolução.
- **Modos de execução:** toda partida começa manualmente; durante as pausas, Enter mantém o avanço manual e P/p ativa a simulação até o fim.

As pontuações são parâmetros definidos para o jogo e **não representam benchmarks oficiais** dos modelos.

## Requisitos

- GCC com suporte a C11 (MinGW no Windows também é compatível) ou Clang.
- Windows/PowerShell ou terminal equivalente.
- Não são necessárias bibliotecas externas.

## Compilar e executar

Execute os comandos a partir da raiz do repositório.

### Windows (PowerShell)

```powershell
gcc -std=c11 -Wall -Wextra -Wpedantic -Werror -Iincludes src\*.c -o build.exe
.\build.exe
```

### Linux / macOS

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -Werror -Iincludes src/*.c -o build
./build
```

O menu oferece as opções:

- `1`: iniciar uma partida;
- `2`: consultar um resumo das regras;
- `0`: encerrar o programa.

A primeira rodada sempre exige interação manual, incluindo o sorteio inicial e a escolha do atributo. Depois da primeira rodada, Enter continua no modo manual e P/p inicia a simulação automática.

## Regras essenciais

1. O baralho contém 34 cartas e é distribuído igualmente entre os dois jogadores.
2. O jogador definido pelo sorteio inicial escolhe o atributo da primeira rodada.
3. Nas rodadas principais seguintes, o vencedor da rodada anterior escolhe o próximo atributo.
4. A maior pontuação no atributo escolhido vence a disputa.
5. A carta Super Trunfo vence cartas das classes B, C e D. Contra uma carta da classe A, a comparação é feita pelo atributo escolhido.
6. Em caso de empate, as cartas vão para o monte de disputa e os jogadores empatados escolhem novos atributos para desempatar. O jogador que escolheu o atributo da rodada principal mantém o direito de escolha durante aquele desempate.
7. O vencedor recebe o monte de disputa. A partida termina quando um jogador reúne as 34 cartas; também existe tratamento para empate técnico quando todas as cartas ficam no monte.

## Dados das cartas

Os dados ficam em `data/cartas.csv`. O cabeçalho e a ordem das colunas são:

```csv
id,empresa,modelo,caracteristicas,classe,raciocinio,programacao,matematica,conhecimento,tipo_carta
```

O carregamento valida o formato, os campos, os valores numéricos, os IDs e a composição do baralho. O arquivo deve conter exatamente 34 cartas válidas e uma carta `super_trunfo`, da classe A.

## Organização do código

```text
SuperTrunfIA/
├── data/
│   └── cartas.csv
├── includes/
│   ├── baralho.h
│   ├── carta.h
│   ├── interface.h
│   ├── jogador.h
│   ├── jogo.h
│   └── util.h
├── src/
│   ├── baralho.c
│   ├── carta.c
│   ├── interface.c
│   ├── jogador.c
│   ├── jogo.c
│   ├── main.c
│   └── util.c
└── README.md
```

Responsabilidades principais:

- `carta.c`: validação, atributos e comparação de cartas;
- `jogador.c`: operações sobre as mãos dos jogadores;
- `baralho.c`: leitura do CSV, embaralhamento e distribuição;
- `jogo.c`: estado da partida, rodadas, desempates e transferência do monte;
- `interface.c`: mensagens e apresentação no terminal;
- `util.c`: leitura de dados, sorteio e utilitários de terminal;
- `main.c`: configuração do terminal e coordenação do fluxo da partida.

Os cabeçalhos em `includes/` definem os tipos e as interfaces públicas das funções.

## Testes e validação

A branch principal atualmente contém os fontes, cabeçalhos e dados do jogo, mas não mantém um diretório de testes automatizados. Para validar uma alteração, no mínimo:

1. Compile com as opções estritas apresentadas acima.
2. Inicie uma partida e conclua a primeira rodada manualmente.
3. Verifique o avanço manual com Enter e a ativação da simulação com P/p.
4. Exercite uma disputa comum e uma situação de empate/desempate.
5. Confira a contagem de cartas e o encerramento da partida.

Quando testes automatizados forem adicionados novamente ao repositório, seus comandos e sua cobertura deverão ser documentados nesta seção.

## Diretrizes de desenvolvimento

- Preservar a separação entre regras do jogo, interface e utilitários.
- Respeitar os contratos e limites definidos nos cabeçalhos em `includes/`.
- Preferir estruturas estáticas e validar entradas, índices, capacidades e integridade das cartas antes de alterar o estado.
- Não alterar regras ou decisões do jogo como efeito colateral de uma refatoração sintática.
- Desenvolver em branches de trabalho e integrar por Pull Request. **Não realizar commits diretamente na `main`.**

## Estado e próximos passos

A V1 Core reúne o fluxo de partida, sorteio inicial, escolha de atributos, comparação com Super Trunfo, desempates, monte de disputa, transferência de cartas, simulação opcional e condição de encerramento.

As próximas melhorias de legibilidade e simplificação sintática foram registradas nas Issues **#62 a #66**. A V2 — Visual & Integration — é uma etapa futura e não deve alterar o escopo da V1 antes de sua estabilização e validação.
