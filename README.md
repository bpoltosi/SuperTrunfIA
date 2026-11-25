# SuperTrunfIA

Jogo de Super Trunfo em C com cartas temáticas de modelos de inteligência artificial. A V1 (Core) é um jogo de terminal para dois jogadores, com dados carregados de CSV e sem alocação dinâmica de memória.

## Cartas e regras

O baralho possui 34 cartas (33 modelos e Alan Turing como Super Trunfo), quatro atributos de 0 a 100 e classes A, B, C e D. As pontuações são parâmetros de balanceamento do jogo, não benchmarks oficiais.

- [Lista e dados de cartas](docs/lista-cartas.md) / [CSV](data/cartas.csv)
- [Regras completas](docs/regras.md)
- [Contratos das funções](docs/contratos-funcoes.md)
- [Interface terminal V1](docs/interface-terminal-v1.md)
- [Roadmap V1/V2](docs/planejamento-versoes.md)

## Requisitos

- GCC (MinGW no Windows) ou Clang
- Terminal/PowerShell
- Nenhuma biblioteca externa

## Compilar e executar

Execute na raiz do repositório:

```powershell
gcc -std=c11 -Wall -Wextra -Wpedantic -Werror -Iincludes src\*.c -o build.exe
.\build.exe
```

Menu: 1 inicia uma partida, 2 mostra as regras, 0 encerra. A primeira rodada é manual; depois da primeira rodada, Enter continua manual e P/p ativa simulação até a partida terminar.

## Testes

Os comandos de testes e o checklist manual estão em [tests/README.md](tests/README.md). Há testes automatizados para cartas, jogadores, CSV, desempates, transferência e cinco partidas simuladas completas.

```powershell
gcc -std=c11 -Wall -Wextra -Wpedantic -Werror -Iincludes tests\test_phase1.c src\carta.c src\jogador.c src\baralho.c -o tests\test_phase1.exe
.\tests\test_phase1.exe

gcc -std=c11 -Wall -Wextra -Wpedantic -Werror -Iincludes tests\test_engine.c src\jogo.c src\carta.c src\jogador.c src\baralho.c src\interface.c src\util.c -o tests\test_engine.exe
.\tests\test_engine.exe
```

## Estrutura

- `includes/`: tipos, contratos e cabeçalhos
- `src/`: cartas, jogadores, baralho, motor, interface e utilitários
- `data/`: CSV de cartas
- `tests/`: testes automatizados e instruções
- `docs/`: regras, arquitetura e planejamento

## Estado

V1 Core está implementada: menu, entrada dos nomes, sorteio inicial, primeira rodada manual, modo de simulação opcional, rodadas, desempates, monte de disputa, transferência, condição de vitória e limpeza de estado. Testes automatizados e compilação estrita devem ser executados antes de considerar a versão release. Sanitizers dependem de runtimes compatíveis instalados.

## Versionamento

Desenvolvimento da V1 ocorre em branch de trabalho; não fazer commits diretos na `main`. A V2 Visual & Integration é futura e só deve começar após estabilizar e validar a V1.
