# Cartas e atributos — SuperTrunfIA

> **Versão revisada — 1º de novembro de 2026.** Esta documentação combina pesquisa em fontes oficiais e avaliações públicas com pontuações de gameplay. As notas de 0 a 100 são uma **escala lúdica normalizada**, não percentuais de acerto nem resultados oficiais de benchmarks. O objetivo é representar diferenças relativas entre modelos, especializações e gerações sem premiar automaticamente uma empresa por sua reputação.

## 1. Estrutura do baralho

- **40 cartas:** 39 modelos de linguagem e 1 carta especial.
- **9 empresas:** OpenAI, Anthropic, Google DeepMind, Meta, xAI, Mistral AI, DeepSeek, Cohere e NVIDIA.
- **4 atributos:** Raciocínio, Programação, Matemática e Conhecimento.
- **Escala:** 0 a 100 pontos por atributo.
- **Carta especial:** Alan Turing — Super Trunfo.

## 2. Definição dos atributos

| Atributo | O que representa | Evidências que mais importam |
|---|---|---|
| **Raciocínio** | Resolver problemas lógicos, abstratos, científicos e dedutivos, inclusive tarefas de várias etapas. | GPQA, Humanity's Last Exam, ARC-AGI, avaliações de raciocínio e agentes. |
| **Programação** | Compreender, escrever, depurar e modificar código, além de resolver tarefas reais de engenharia de software. | SWE-bench/DeepSWE, Terminal-Bench, CursorBench, Codeforces e avaliações de engenharia de software. |
| **Matemática** | Resolver problemas quantitativos, aritméticos, algébricos, matemáticos avançados e demonstrações. | AIME, MATH, FrontierMath, MathArena e RiemannBench. |
| **Conhecimento** | Amplitude, precisão e aplicação de conhecimento geral, científico, acadêmico e profissional. | MMLU/MMLU-Pro, GPQA, SimpleQA, Vals Index e avaliações de conhecimento especializado. |

Os atributos são deliberadamente distintos: uma carta pode ser excelente em matemática sem ser a melhor em programação; um modelo pequeno pode ter desempenho útil em uma tarefa específica sem superar os modelos de fronteira em conhecimento geral.

## 3. Critério de balanceamento

### 3.1 Como as evidências foram usadas

1. **Benchmarks comparáveis têm prioridade.** Quando há resultados públicos para mais de um modelo no mesmo benchmark, eles ajudam a ordenar as cartas.
2. **Não misturar escalas incompatíveis.** Uma nota de 90 em GPQA não é diretamente comparável a 90% no SWE-bench. Cada benchmark informa seu atributo; não se calcula uma média ingênua de percentuais heterogêneos.
3. **Rankings agregados servem como referência, não como verdade absoluta.** O LLMBenchmark.ai publica índices separados para coding, agentic work, reasoning, math e knowledge, com quantidade de modelos e fontes por categoria. Os índices são úteis para comparar tendências, mas a cobertura varia por modelo.
4. **Documentação dos fabricantes contextualiza especializações.** Model cards e páginas oficiais ajudam a identificar o propósito do modelo, tamanho relativo, modalidade e geração.
5. **Idade importa, mas não determina tudo.** Modelos antigos recebem pontuações gerais menores em comparação com as gerações atuais. Ainda podem manter um atributo relativamente forte para sua época ou tamanho.
6. **Eficiência não é sinônimo de capacidade máxima.** Modelos compactos não recebem notas de topo apenas por velocidade, baixo custo ou contexto longo.
7. **Empresa não é atributo.** Cada fabricante tem cartas fortes, intermediárias e históricas. O nome da empresa não concede pontos.

### 3.2 Faixas de gameplay

| Faixa | Pontuação típica por atributo | Interpretação |
|---|---:|---|
| **Lendário** | 96–100 | Fronteira de desempenho em uma ou mais áreas. |
| **Elite** | 91–95 | Desempenho muito alto e competitivo. |
| **Avançado** | 82–90 | Forte, mas com limitações ou especialização mais visível. |
| **Intermediário** | 70–81 | Útil e competente, porém abaixo das gerações de ponta. |
| **Legado** | 50–69 | Geração anterior, com limitações relevantes frente aos modelos atuais. |
| **Histórico/compacto** | 40–69 | Modelo antigo ou pequeno; pode conservar pontos fortes específicos. |

As faixas são referências para construir o baralho, não classificações oficiais dos fabricantes. Uma carta pode ter, por exemplo, Matemática em faixa Elite e Conhecimento em faixa Avançado.

## 4. Cartas e pontuações revisadas

As características abaixo descrevem o papel da carta no jogo. As notas são propostas de gameplay calibradas com as evidências disponíveis em 1º de novembro de 2026.

### OpenAI — 5 cartas

| Modelo | Características | Raciocínio | Programação | Matemática | Conhecimento |
|---|---|---:|---:|---:|---:|
| GPT-6 Astra | Modelo de fronteira para raciocínio complexo, ciência, programação e trabalho profissional. | 98 | 96 | 98 | 97 |
| GPT-6.1 Sol | Desempenho próximo ao topo, com equilíbrio entre raciocínio, programação e eficiência. | 96 | 97 | 96 | 96 |
| GPT-6.1 Terra | Forte em raciocínio visual, uso de computador e tarefas técnicas; destaque relativo em matemática. | 94 | 92 | 97 | 94 |
| GPT-6 Luna | Modelo econômico e rápido para tarefas focadas e de alto volume. | 88 | 86 | 85 | 89 |
| GPT-3.5 Turbo | Modelo histórico de chat e geração de código; claramente superado pelas gerações recentes. | 60 | 57 | 54 | 68 |

**Justificativa de balanceamento:** Astra, Sol e Terra ocupam o topo, mas com perfis diferentes. Luna fica abaixo dos modelos de fronteira por ser voltado à eficiência. GPT-3.5 Turbo é uma carta histórica: a própria OpenAI recomenda modelos posteriores em seu lugar e registra seu encerramento na API em outubro de 2026.

### Anthropic — 5 cartas

| Modelo | Características | Raciocínio | Programação | Matemática | Conhecimento |
|---|---|---:|---:|---:|---:|
| Claude Opus 5.5 | Modelo de ponta, especialmente forte em programação agentiva e trabalho complexo. | 98 | 99 | 96 | 96 |
| Claude Sonnet 5.5 | Alto desempenho em programação e tarefas profissionais, com perfil equilibrado. | 95 | 98 | 92 | 94 |
| Claude Fable 5.1 | Forte em tarefas agentivas, raciocínio e matemática avançada. | 96 | 96 | 97 | 92 |
| Claude Mythos 5.1 | Modelo avançado de raciocínio e capacidades complexas. | 97 | 96 | 97 | 94 |
| Claude 2 | Geração histórica de linguagem, anterior à família Claude 3 e às gerações atuais. | 66 | 58 | 57 | 72 |

**Justificativa de balanceamento:** Opus e Sonnet recebem vantagem relativa em programação; Fable e Mythos têm perfil forte em raciocínio. Claude 2 cria uma diferença geracional real e impede que todas as cartas da Anthropic fiquem no topo.

### Google DeepMind — 5 cartas

| Modelo | Características | Raciocínio | Programação | Matemática | Conhecimento |
|---|---|---:|---:|---:|---:|
| Gemini 4 Argon | Modelo de fronteira multimodal, forte em raciocínio, conhecimento e tarefas complexas. | 98 | 96 | 97 | 98 |
| Gemini 3.8 Flash | Modelo rápido, com capacidades avançadas em engenharia de software e fluxos agentivos. | 94 | 94 | 91 | 94 |
| Gemini 3.7 Flash | Geração Flash anterior, equilibrando velocidade e capacidade geral. | 91 | 90 | 88 | 92 |
| Gemini 3.1 Pro | Modelo de alto desempenho geral, com boa capacidade de raciocínio e matemática. | 94 | 92 | 95 | 95 |
| PaLM 2 | Geração histórica, com competências relevantes em linguagem, conhecimento e matemática para sua época. | 69 | 65 | 70 | 78 |

**Justificativa de balanceamento:** Argon concentra as maiores notas. Os modelos Flash ficam abaixo dos modelos de fronteira, mas mantêm boas pontuações. PaLM 2 representa uma geração anterior à família Gemini.

### Meta — 5 cartas

| Modelo | Características | Raciocínio | Programação | Matemática | Conhecimento |
|---|---|---:|---:|---:|---:|
| Muse Spark | Modelo multimodal de raciocínio, com uso de ferramentas e orquestração de agentes. | 93 | 86 | 90 | 94 |
| Llama 4 Maverick | Modelo aberto multimodal de uso geral, com boa capacidade geral. | 88 | 85 | 82 | 88 |
| Llama 4 Scout | Modelo aberto com contexto extenso e foco em eficiência. | 84 | 80 | 78 | 84 |
| Llama 3.3 70B Instruct | Modelo aberto de geração anterior, competente em instruções e tarefas gerais. | 83 | 82 | 79 | 86 |
| Llama 2 7B | Modelo compacto histórico; importante para a difusão de modelos abertos, mas limitado frente às gerações atuais. | 57 | 54 | 51 | 65 |

**Justificativa de balanceamento:** Muse Spark é a carta de maior capacidade da empresa. Maverick e Scout não recebem pontuações equivalentes aos modelos de fronteira fechados. Llama 2 7B funciona como carta histórica e compacta.

### xAI — 5 cartas

| Modelo | Características | Raciocínio | Programação | Matemática | Conhecimento |
|---|---|---:|---:|---:|---:|
| Grok 4.7 | Modelo avançado para programação, conhecimento e tarefas profissionais de longa duração. | 95 | 96 | 89 | 91 |
| Grok 4.6 | Geração de alto desempenho, com melhorias em agentes e tarefas visuais. | 94 | 94 | 88 | 91 |
| Grok 4.5 | Modelo avançado de uso geral, programação e trabalho agentivo. | 93 | 92 | 87 | 90 |
| Grok 3 | Geração anterior, com capacidade geral e raciocínio competitivo para sua época. | 88 | 88 | 89 | 88 |
| Grok-1 | Primeiro modelo da família Grok, histórico e de capacidade significativamente inferior às gerações atuais. | 66 | 62 | 61 | 72 |

**Justificativa de balanceamento:** Grok 4.7 recebe destaque em programação, mas não domina automaticamente matemática e conhecimento. Grok 3 fica em faixa avançada/intermediária e Grok-1 cria uma carta histórica de baixa pontuação.

### Mistral AI — 4 cartas

| Modelo | Características | Raciocínio | Programação | Matemática | Conhecimento |
|---|---|---:|---:|---:|---:|
| Mistral Large 4 | Modelo multimodal aberto de uso geral, voltado a raciocínio, programação e agentes. | 93 | 93 | 91 | 91 |
| Mistral Small 4 | Modelo eficiente que combina instruções, raciocínio e programação. | 89 | 90 | 87 | 88 |
| Ministral 3 14B | Modelo compacto multimodal, com foco em eficiência e capacidades gerais. | 83 | 83 | 80 | 84 |
| Mistral 7B | Modelo aberto histórico de 7,3 bilhões de parâmetros; teve desempenho relevante para seu tamanho, inclusive em código e raciocínio. | 67 | 69 | 62 | 70 |

**Justificativa de balanceamento:** a família atual é representada por Large, Small e Ministral. Mistral 7B substitui uma carta redundante e evidencia a evolução da empresa. Sua nota de Programação fica ligeiramente acima de Raciocínio e Matemática, refletindo seu desempenho relativo em avaliações divulgadas no lançamento.

### DeepSeek — 4 cartas

| Modelo | Características | Raciocínio | Programação | Matemática | Conhecimento |
|---|---|---:|---:|---:|---:|
| DeepSeek V4.1 Flash | Modelo eficiente com raciocínio, programação, compreensão visual e forte desempenho em avaliações técnicas. | 94 | 97 | 95 | 88 |
| DeepSeek V4-Pro | Modelo de alto desempenho da família V4, voltado a tarefas complexas e agentes. | 96 | 96 | 97 | 91 |
| DeepSeek R1 | Modelo de raciocínio com destaque histórico em matemática e resolução de problemas. | 96 | 91 | 99 | 88 |
| DeepSeek V3.2 | Modelo geral com capacidades de programação, raciocínio e uso de ferramentas. | 91 | 93 | 94 | 89 |

**Justificativa de balanceamento:** DeepSeek mantém perfil especializado em matemática e programação. R1 é uma geração anterior, mas conserva uma nota excepcional em Matemática; não deve ser rebaixado artificialmente apenas por ser mais antigo.

### Cohere — 3 cartas

| Modelo | Características | Raciocínio | Programação | Matemática | Conhecimento |
|---|---|---:|---:|---:|---:|
| Command A+ | Modelo empresarial avançado, com raciocínio, agentes, visão e tradução. | 90 | 88 | 82 | 94 |
| Command A | Modelo empresarial de uso geral, forte em ferramentas, RAG e tarefas multilíngues. | 87 | 84 | 79 | 92 |
| Command R | Modelo anterior, voltado a linguagem, recuperação aumentada por geração (RAG) e aplicações empresariais. | 79 | 75 | 70 | 86 |

**Justificativa de balanceamento:** Cohere tem foco mais empresarial, recuperação de informação e ferramentas. Por isso, Conhecimento é relativamente alto, enquanto Matemática e Programação ficam mais moderadas. Command R representa a geração anterior à linha Command A.

### NVIDIA — 3 cartas

| Modelo | Características | Raciocínio | Programação | Matemática | Conhecimento |
|---|---|---:|---:|---:|---:|
| Nemotron 3 Ultra | Modelo de grande escala, voltado a raciocínio avançado e aplicações complexas com agentes. | 93 | 95 | 92 | 88 |
| Nemotron 3 Super | Modelo de raciocínio de alta precisão para aplicações multiagente. | 90 | 92 | 89 | 86 |
| Nemotron 2 Nano | Modelo compacto de geração anterior, priorizando eficiência e execução de tarefas direcionadas. | 76 | 78 | 72 | 80 |

**Justificativa de balanceamento:** Ultra e Super são modelos de maior capacidade. Nemotron 2 Nano entra como carta de geração anterior; sua nota não deve ser confundida com a do Nemotron 3 Nano, que pertence a uma família mais recente.

### Carta especial — Alan Turing

Alan Turing representa o pioneirismo da computação, a lógica matemática e os fundamentos teóricos da inteligência artificial. Seus atributos são simbólicos e históricos; não são resultados de benchmarks de LLMs.

| Atributo | Pontuação | Justificativa temática |
|---|---:|---|
| Raciocínio | 100 | Contribuições fundamentais à lógica e à computabilidade. |
| Programação | 75 | Pioneirismo conceitual em computação; não é comparação direta com modelos modernos de programação. |
| Matemática | 100 | Contribuições relevantes à matemática e à lógica formal. |
| Conhecimento | 95 | Amplitude intelectual e contribuição científica histórica. |

**Regra especial:** Alan Turing é a carta Super Trunfo. Sua interação com as classes e as exceções de vitória deve seguir as regras gerais do jogo, documentadas separadamente.

## 5. Resumo da distribuição

| Empresa / carta | Quantidade |
|---|---:|
| OpenAI | 5 |
| Anthropic | 5 |
| Google DeepMind | 5 |
| Meta | 5 |
| xAI | 5 |
| Mistral AI | 4 |
| DeepSeek | 4 |
| Cohere | 3 |
| NVIDIA | 3 |
| **Modelos de linguagem** | **39** |
| Alan Turing — especial | 1 |
| **Total** | **40** |

A distribuição preserva a quantidade de cartas por empresa, mas amplia a diversidade temporal. As empresas com cinco cartas passam a ter pelo menos uma representação histórica ou de geração anterior; as demais também incluem gerações anteriores ou modelos compactos.

## 6. Verificação de coerência e balanceamento

### 6.1 Princípios aplicados

- **Nenhuma empresa domina todas as categorias.** As cartas de topo se alternam entre fabricantes e especializações.
- **Cartas antigas são realmente mais fracas no conjunto geral.** GPT-3.5 Turbo, Claude 2, PaLM 2, Llama 2 7B, Grok-1 e Mistral 7B têm notas substancialmente inferiores às gerações atuais.
- **Modelos compactos não são penalizados cegamente.** Podem manter notas úteis em áreas específicas, mas não recebem 90+ em todos os atributos sem evidência.
- **Especialização gera assimetria.** DeepSeek R1 é particularmente forte em Matemática; Command A+ é relativamente forte em Conhecimento; Grok 4.7 é particularmente forte em Programação.
- **A carta Super Trunfo é excepcional por regra temática.** Alan Turing não deve entrar nos rankings estatísticos de LLMs.

### 6.2 Pontos que merecem teste em partidas

1. Verificar se os atributos de Matemática e Programação são escolhidos com frequência excessiva por concentrarem cartas especializadas.
2. Testar se as cartas históricas ainda conseguem vencer disputas quando enfrentam modelos da mesma faixa.
3. Observar se a diferença entre 90 e 95 é perceptível no jogo ou se deve ser ampliada.
4. Verificar se Alan Turing está excessivamente forte ou se sua regra especial cria contrajogo suficiente.
5. Ajustar pontuações somente após partidas de teste, mantendo registro do motivo da alteração.

## 7. Fontes e referências

### Rankings e metodologia de benchmarks

- [LLMBenchmark.ai — Rankings de coding, agentic work, reasoning, math e knowledge](https://llmbenchmark.ai/rankings) — índices agregados, cobertura por categoria e metodologia.
- [LLMBenchmark.ai — Benchmarks acompanhados](https://llmbenchmark.ai/benchmarks) — catálogo de avaliações públicas e respectivas áreas.
- [Artificial Analysis — Intelligence Index](https://artificialanalysis.ai/leaderboards/models) — referência complementar para inteligência geral e avaliações comparáveis.

### OpenAI

- [GPT-6 Astra — apresentação e benchmarks](https://openai.com/pt-BR/index/gpt-6-astra/)
- [GPT-6.1 Terra — capacidades e avaliações](https://openai.com/index/introducing-gpt-6-1-terra/)
- [Modelos da API OpenAI](https://developers.openai.com/api/docs/models)
- [GPT-3.5 Turbo — ficha do modelo e encerramento](https://developers.openai.com/api/docs/models/gpt-3.5-turbo)

### Anthropic

- [System cards oficiais dos modelos Claude](https://www.anthropic.com/system-cards)
- [Claude Sonnet 5.5 — anúncio e avaliações](https://www.anthropic.com/claude-sonnet-5-5)

### Google DeepMind

- [Model cards oficiais](https://deepmind.google/models/model-cards/)
- [Gemini 4 Argon — model card e benchmarks](https://deepmind.google/models/model-cards/gemini-4-argon/)
- [Gemini 3.8 Flash — model card](https://deepmind.google/models/model-cards/gemini-3-8-flash/)
- [Modelos disponíveis na Gemini API](https://ai.google.dev/gemini-api/docs/models)

### Meta

- [Muse Spark — anúncio oficial](https://ai.meta.com/blog/introducing-model-meta-superintelligence-labs/)
- [Repositório oficial Meta Llama Models — gerações e datas](https://github.com/meta-llama/llama-models)

### xAI

- [Grok 4.7 — anúncio oficial e comparações](https://x.ai/news/grok-4-7)
- [Notícias e lançamentos oficiais da xAI](https://x.ai/news)

### Mistral AI

- [Catálogo oficial de modelos Mistral](https://docs.mistral.ai/models)
- [Mistral 7B — anúncio e benchmarks originais](https://mistral.ai/news/announcing-mistral-7b/)

### DeepSeek

- [DeepSeek Transparency Center — modelos, datas e model cards](https://www.deepseek.com/en/transparency/)
- [DeepSeek API — changelog e benchmarks do V4.1 Flash/V4-Pro/V3.2](https://api-docs.deepseek.com/updates/)

### Cohere

- [Catálogo oficial de modelos Cohere](https://docs.cohere.com/v1/docs/models)

### NVIDIA

- [Nemotron 3 — anúncio oficial da família](https://nvidianews.nvidia.com/news/nvidia-debuts-nemotron-3-family-of-open-models)
- [Nemotron 3 Ultra — ficha técnica](https://research.nvidia.com/labs/nemotron/Nemotron-3-Ultra/)

## 8. Limitações e próximos ajustes

1. Não existe um benchmark único que meça exatamente os quatro atributos deste jogo. As notas sintetizam evidências distintas e julgamento de balanceamento.
2. Os resultados podem variar conforme versão, esforço de raciocínio, ferramentas, prompt, conjunto de teste e avaliador.
3. Alguns fabricantes publicam avaliações próprias; esses números devem ser lidos com atenção às condições e não comparados diretamente com resultados independentes.
4. Para modelos históricos, a cobertura em rankings atuais é limitada. Suas notas são estimativas de gameplay ancoradas em documentação e avaliações disponíveis da época, não medições contemporâneas padronizadas.
5. Antes de uma edição futura, conferir novamente versões e disponibilidade dos modelos. Modelos podem ser renomeados, substituídos ou descontinuados.

## 9. Histórico

- **Versão inicial:** lista de 39 modelos e Alan Turing, com pontuações provisórias de gameplay.
- **Versão revisada — 1º de novembro de 2026:** revisão de nomes e gerações, inclusão de cartas históricas/anteriores, rebalanceamento assimétrico dos quatro atributos e inclusão de referências para validação técnica.
