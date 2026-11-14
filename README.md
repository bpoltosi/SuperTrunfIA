# SuperTrunfIA

Projeto acadêmico de um jogo inspirado em **Super Trunfo**, com cartas temáticas de modelos de inteligência artificial. O repositório reúne a modelagem das cartas, as regras do jogo, os contratos das funções e uma implementação modular em C em desenvolvimento.

## Tema e cartas

O baralho definido no projeto contém **34 cartas**: 33 modelos de IA e uma carta especial, Alan Turing. Cada carta possui quatro atributos:

- Raciocínio
- Programação
- Matemática
- Conhecimento

As cartas são organizadas nas classes A, B, C e D. Alan Turing representa a carta especial Super Trunfo e possui regras próprias de comparação.

> **Importante:** as pontuações são parâmetros fictícios de balanceamento do jogo. Não representam benchmarks oficiais, avaliações técnicas verificadas ou rankings de modelos.

Consulte [docs/lista-cartas.md](docs/lista-cartas.md) para a composição do baralho e [data/cartas.csv](data/cartas.csv) para os dados utilizados pelo projeto.

## Regras documentadas

As regras atuais especificam:

- Comparação dos atributos escolhidos.
- Regra especial da carta Super Trunfo em relação às classes.
- Distribuição do baralho entre dois jogadores.
- Tratamento de empates e acúmulo de cartas no monte de disputa.
- Rodadas de desempate e reutilização das cartas reveladas.
- Condições de encerramento e definição do vencedor.

A especificação completa está em [docs/regras.md](docs/regras.md). Os contratos de retorno e comportamento das funções estão em [docs/contratos-funcoes.md](docs/contratos-funcoes.md) e nos cabeçalhos de `includes/`.

## Organização do repositório

| Diretório/arquivo | Responsabilidade |
|---|---|
| `includes/` | Cabeçalhos e contratos das estruturas e funções |
| `src/` | Implementação modular em C: cartas, baralho, jogadores, jogo, interface e utilitários |
| `data/cartas.csv` | Baralho carregado pelo programa |
| `docs/` | Regras, contratos, lista de cartas, enunciado acadêmico e planejamento de versões |

## Tecnologias

- Linguagem C.
- Arquivos CSV para os dados das cartas.
- Git e GitHub para versionamento e documentação.

## Estado atual

O projeto está **em desenvolvimento**. A modelagem das cartas, os dados do baralho, as regras e os contratos das funções estão documentados, e há módulos C iniciados para implementar essas responsabilidades.

A inicialização em `src/main.c` ainda contém etapas em aberto (menu, configuração dos jogadores, execução das rodadas e apresentação do resultado). Portanto, **o jogo completo ainda não deve ser considerado executável ou validado de ponta a ponta**. Os contratos em `includes/` e `docs/contratos-funcoes.md` orientam a implementação dos módulos.

## Planejamento

O roadmap separa a entrega do núcleo acadêmico em C (V1) de uma possível expansão futura com interface visual e integrações (V2). A V2 é uma proposta, não uma funcionalidade existente.

Consulte [docs/planejamento-versoes.md](docs/planejamento-versoes.md) para o escopo e a ordem planejada de evolução.
