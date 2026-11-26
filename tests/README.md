# Testes automatizados — refatoracoes

Execute na raiz do repositorio, em Windows com GCC/MinGW e PowerShell:

```powershell
.\tests\smoke.ps1
```

O script executa:

- Build completo com C11 e `-Wall -Wextra -Wpedantic -Werror`.
- Testes de comparacao comum e precedencia do Super Trunfo, inclusive contra classes A, B, C e D.
- Testes de integridade das zonas, IDs duplicados, cartas invalidas e empate tecnico.
- Testes de transferencia integral e garantia de ausencia de mutacao parcial em falha.
- Testes de obtencao de cartas reutilizadas no desempate.
- Testes do CSV oficial, BOM UTF-8, campos entre aspas, virgulas em campos, falha de validacao sem publicacao parcial e arquivo ausente.
- Smoke test da interface: sorteio com nome do jogador, primeira rodada manual, ativacao por P e simulacao ate o encerramento.

Os executaveis e arquivos temporarios sao removidos ao final do script.

AddressSanitizer e UndefinedBehaviorSanitizer nao puderam ser executados neste ambiente MinGW: as bibliotecas de runtime `libasan` e `libubsan` nao estao instaladas. A validacao complementar deve ser executada em GCC/Clang com esses runtimes disponiveis, por exemplo em Linux ou WSL.
