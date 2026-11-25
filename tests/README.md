# Testes automatizados da Fase 1

Execute a partir da raiz do repositorio com GCC (MinGW):

```powershell
gcc -std=c11 -Wall -Wextra -Wpedantic -Werror -Iincludes tests\test_phase1.c src\carta.c src\jogador.c src\baralho.c -o tests\test_phase1.exe
.\tests\test_phase1.exe
gcc -std=c11 -Wall -Wextra -Wpedantic -Werror -Iincludes src\*.c -o build.exe
```

A suíte cobre validação/comparação de cartas, Super Trunfo, operações e limites de jogadores, carregamento CSV, composição de classes, embaralhamento, distribuição e falha de CSV inválido. Ela deve ser executada com o diretório de trabalho na raiz, pois o CSV usa caminho relativo.

Sanitizers AddressSanitizer/UndefinedBehaviorSanitizer não estão disponíveis na instalação MinGW deste computador (faltam as bibliotecas de runtime `asan` e `ubsan`).