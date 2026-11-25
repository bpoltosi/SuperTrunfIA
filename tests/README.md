# Testes e compilação — V1

Execute os comandos na raiz do repositório, com GCC/MinGW e Clang instalados.

## Build completo (GCC)

```powershell
gcc -std=c11 -Wall -Wextra -Wpedantic -Werror -Iincludes src\*.c -o build.exe
.\build.exe
```

## Testes de cartas, jogadores e CSV

```powershell
gcc -std=c11 -Wall -Wextra -Wpedantic -Werror -Iincludes tests\test_phase1.c src\carta.c src\jogador.c src\baralho.c -o tests\test_phase1.exe
.\tests\test_phase1.exe
```

## Testes do motor e simulações completas

```powershell
gcc -std=c11 -Wall -Wextra -Wpedantic -Werror -Iincludes tests\test_engine.c src\jogo.c src\carta.c src\jogador.c src\baralho.c src\interface.c src\util.c -o tests\test_engine.exe
.\tests\test_engine.exe
```

O teste do motor cobre transferência em vitória, empate, reutilização de cartas de desempate, troca de atributo e empate em todos os quatro atributos (as cartas empatadas são recolhidas uma única vez e o desempate avança para novas cartas), além de cinco partidas completas com seeds distintas.

## Smoke test automatizado da interface

O script compila o aplicativo, inicia uma partida com a primeira rodada manual, ativa simulação após a pausa e verifica saída do campeão com 34 cartas e retorno ao menu:

```powershell
.\tests\smoke.ps1
```

## Smoke test manual da interface

1. Compile e execute o build completo.
2. Escolha iniciar e informe dois nomes.
3. Faça o sorteio par/ímpar e selecione um atributo manualmente na primeira rodada.
4. Nos pontos de pausa, Enter continua manualmente; P/p ativa simulação até o campeão.
5. Confirme que o jogo apresenta o campeão com 34 cartas.

## Sanitizers

AddressSanitizer e UndefinedBehaviorSanitizer não estão disponíveis nos runtimes MinGW instalados neste computador. Tente em ambiente Linux/WSL com GCC ou Clang habilitados para sanitizers.

Os testes base também verificam BOM UTF-8, cabeçalho/schema, aspas e escape de aspas, vírgulas internas, IDs duplicados, linha CSV acima do buffer, campos de texto acima do tamanho das estruturas, arquivo ausente e distribuição atômica com cartas/IDs inválidos. Falhas de CSV emitem diagnóstico em stderr com linha e campo/validação.


## Validação adicional das issues UX

- Na pausa de rodada, testar Enter e confirmar que o terminal limpa antes da próxima rodada manual.
- Em outra partida, testar P/p e confirmar que o terminal limpa antes da mensagem de ativação da simulação.
- Confirmar que o sorteio inicial exibe o nome cadastrado do Jogador 1.
- Na simulação automática, observar variação dos atributos escolhidos; o smoke test também verifica variedade.
- Confirmar espaçamento maior entre blocos e linhas da interface, sem prejudicar prompts.


## Regressao das issues #52-#54

- `test_engine.c` cobre as quatro combinacoes de escolha/resultado do sorteio (`1=PAR`, `2=IMPAR`) e rejeita valores invalidos.
- `smoke.ps1` verifica que o jogador responsavel e anunciado antes da escolha do atributo, que a proxima rodada reapresenta essa informacao apos Enter e que o fluxo de simulacao tambem volta a exibi-la depois da limpeza do terminal.
- `src/main.c` configura locale e code page UTF-8 no Windows; a mensagem de desempate usa o caractere Unicode U+2014 em fonte UTF-8.
