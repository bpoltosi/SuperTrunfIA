# SuperTrunfIA

Jogo de **Super Trunfo desenvolvido em C**, com cartas temáticas de modelos de inteligência artificial. A versão atual (V1 — Core) funciona no terminal, suporta dois jogadores e carrega os dados das cartas de um arquivo CSV.

O projeto prioriza regras explícitas, estruturas estáticas, separação entre motor e interface e validação dos estados da partida.

## Visão geral

- **34 cartas:** 33 modelos de IA e Alan Turing como carta especial Super Trunfo.
- **4 atributos:** Raciocínio, Programação, Matemática e Conhecimento, com valores de 0 a 100.
- **Classes:** A, B, C e D, registradas individualmente em cada carta.
- **Dois jogadores:** 17 cartas iniciais para cada participante.
- **Desempates:** as cartas da disputa ficam em um monte da mesa até a resolução.
- **Modos de execução:** toda partida começa manualmente; durante as pausas, é possível continuar com Enter ou ativar a simulação com P/p.

As pontuações são parâmetros definidos para o jogo e **não representam benchmarks oficiais** dos modelos.

## Regras e documentação

Consulte os documentos para conhecer as regras completas e os contratos técnicos:

- [Regras do jogo](docs/regras.md)
- [Lista e composição das cartas](docs/lista-cartas.md)
- [Contratos das funções](docs/contratos-funcoes.md)
- [Fluxo e interface de terminal](docs/interface-terminal-v1.md)
- [Planejamento das versões V1 e V2](docs/planejamento-versoes.md)
- [Compilação, testes e validações](tests/README.md)

Os cabeçalhos em `includes/` são a referência dos contratos públicos das funções.

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

A primeira rodada sempre exige interação manual, incluindo o sorteio inicial e a escolha do atributo. Depois da primeira rodada, Enter mantém o avanço manual e P/p inicia a simulação automática até o fim da partida.

## Executar os testes

Os testes devem ser compilados a partir da raiz do repositório. Os comandos abaixo usam GCC/MinGW no PowerShell.

### Cartas, jogadores e CSV

```powershell
gcc -std=c11 -Wall -Wextra -Wpedantic -Werror -Iincludes tests\test_phase1.c src\carta.c src\jogador.c src\baralho.c -o tests\test_phase1.exe
.\tests\test_phase1.exe
```

### Motor, rodadas e desempates

```powershell
gcc -std=c11 -Wall -Wextra -Wpedantic -Werror -Iincludes tests\test_engine.c src\jogo.c src\carta.c src\jogador.c src\baralho.c src\interface.c src\util.c -o tests\test_engine.exe
.\tests\test_engine.exe
```

### Interface

```powershell
gcc -std=c11 -Wall -Wextra -Wpedantic -Werror -Iincludes tests\test_interface.c src\interface.c src\util.c -o tests\test_interface.exe
.\tests\test_interface.exe
```

### Smoke test integrado

```powershell
.\tests\smoke.ps1
```

O [guia de testes](tests/README.md) descreve a cobertura, os cenários manuais e as limitações conhecidas de sanitizers. A análise estática e os testes funcionais são validações complementares; nenhum deles substitui a execução dos demais.

## Organização do repositório

```text
SuperTrunfIA/
├── data/
│   └── cartas.csv          # Dados das 34 cartas
├── docs/                   # Regras, cartas, contratos e decisões
├── includes/               # Tipos e interfaces públicas (.h)
├── src/                    # Implementação em C
├── tests/                  # Testes automatizados e smoke test
└── README.md
```

Responsabilidades principais:

- `carta.c`: validação, atributos e comparação de cartas;
- `jogador.c`: operações sobre as mãos dos jogadores;
- `baralho.c`: leitura do CSV, embaralhamento e distribuição;
- `jogo.c`: estado da partida, rodadas, desempates e transferência do monte;
- `interface.c`: mensagens, apresentação e entradas da interface;
- `util.c`: leitura de dados, sorteio e utilitários de terminal;
- `main.c`: configuração do terminal e coordenação do fluxo da partida.

## Diretrizes de desenvolvimento

- Preservar a separação entre regras do jogo, interface e utilitários.
- Manter os contratos documentados nos cabeçalhos e em [docs/contratos-funcoes.md](docs/contratos-funcoes.md).
- Preferir estruturas estáticas e respeitar os limites definidos em `includes/`.
- Validar entradas, índices, capacidades e integridade das cartas antes de alterar o estado.
- Não alterar regras ou decisões já registradas em `docs/` sem documentar a mudança.
- Desenvolver em branches de trabalho e integrar por Pull Request. **Não realizar commits diretamente na `main`.**

## Estado e próximos passos

A V1 Core reúne o fluxo de partida, sorteio inicial, escolha de atributos, comparação com Super Trunfo, desempates, monte de disputa, transferência de cartas, simulação opcional e condição de encerramento.

A V2 — Visual & Integration — é uma etapa futura. Seu planejamento está registrado em [docs/planejamento-versoes.md](docs/planejamento-versoes.md) e não deve alterar o escopo da V1 antes de sua estabilização e validação.
