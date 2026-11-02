# Planejamento de versões

Este documento registra a evolução planejada do **SuperTrunfIA** em duas etapas. A separação permite entregar primeiro uma versão acadêmica funcional e aderente ao enunciado do trabalho, sem abandonar a possibilidade de transformar o projeto posteriormente em uma aplicação mais completa.

> **Status:** planejamento futuro. A V2 não faz parte do escopo da entrega acadêmica inicial e só deverá começar depois que a V1 estiver concluída, testada e documentada.

## V1.0.0 — Core

**Objetivo:** entregar o jogo funcional em C, com execução pelo terminal e regras compatíveis com o guia do trabalho.

Escopo previsto:

- Baralho temático de modelos de inteligência artificial, com no mínimo 24 cartas.
- Cartas com atributos identificados por A, B, C e D.
- Carta especial Super Trunfo e regra de funcionamento documentada.
- Embaralhamento e distribuição aleatória das cartas entre dois jogadores.
- Partida automática, sem exigir decisões ou entradas explícitas dos jogadores.
- Comparação dos atributos, definição do vencedor de cada rodada e transferência das cartas.
- Tratamento de empates, incluindo cartas acumuladas na mesa e rodada de desempate.
- Condição de encerramento quando um jogador conquistar todas as cartas.
- Código organizado, testes de casos omissos e documentação das regras.

A prioridade da V1 é **correção, clareza e conformidade com o enunciado**, não recursos visuais ou integração com serviços externos.

## V2.0.0 — Visual & Integration

**Objetivo:** evoluir o núcleo do jogo para uma aplicação com interface visual e possibilidade de integração com outros componentes.

Esta etapa é uma expansão futura, não um requisito para concluir a V1. O escopo poderá incluir:

- Interface visual para acompanhar partidas, cartas, atributos e resultados.
- Frontend e backend com responsabilidades bem definidas.
- API para comunicação entre a interface e o motor do jogo.
- Persistência de cartas, partidas e resultados em banco de dados.
- Histórico de partidas, estatísticas e rankings.
- Possibilidade de novas modalidades e funcionalidades, desde que preservem as regras-base ou documentem claramente as alterações.

A tecnologia e a infraestrutura da V2 serão escolhidas quando essa etapa for iniciada, considerando simplicidade, manutenção e preferência por ferramentas gratuitas ou de baixo custo.

## Estratégia de versionamento

A proposta é manter o projeto em um único repositório GitHub e identificar versões estáveis por tags:

| Referência | Finalidade |
|---|---|
| `v1.0.0` | Primeira versão estável do Core, pronta para entrega |
| `v1.0.x` | Correções pontuais da V1, sem mudança de escopo |
| `v2.0.0-alpha` | Primeiros protótipos da expansão visual e de integração |
| `v2.0.0-beta` | V2 integrada em fase de validação |
| `v2.0.0` | Primeira versão estável da Visual & Integration |

Antes de iniciar a V2, a V1 deverá estar concluída e marcada com a tag `v1.0.0`, preservando uma referência imutável da entrega acadêmica. O desenvolvimento da V2 deverá ocorrer sem substituir ou descaracterizar essa versão.

A organização em diretórios ou branches será definida conforme a arquitetura real da V2. A estrutura sugerida inicialmente é:

```text
SuperTrunfIA/
├── docs/
│   ├── lista-cartas.md
│   ├── planejamento-versoes.md
│   └── arquitetura.md
├── V1-Core/
│   ├── src/
│   ├── include/
│   ├── data/
│   └── README.md
├── V2-Visual-Integration/
│   ├── frontend/
│   ├── backend/
│   ├── api/
│   ├── database/
│   └── README.md
└── README.md
```

Essa estrutura é uma referência, não uma alteração estrutural a ser feita agora.

## Ordem de execução

1. Finalizar a implementação da V1 em C.
2. Testar as regras e os casos omissos do trabalho.
3. Revisar e concluir a documentação da V1.
4. Criar a tag `v1.0.0` para registrar a entrega estável.
5. Planejar a arquitetura da V2 e os contratos entre frontend, API, backend, motor do jogo e banco de dados.
6. Implementar a V2 incrementalmente, validando que a lógica do jogo continua coerente com as regras documentadas.

## Princípio de compatibilidade

Sempre que possível, as regras e os dados das cartas devem ficar independentes da interface. A V2 deverá reutilizar ou reproduzir fielmente o comportamento definido e testado na V1. Se alguma regra mudar, a alteração deverá ser explícita e documentada, em vez de ocorrer como consequência da troca de interface ou tecnologia.
