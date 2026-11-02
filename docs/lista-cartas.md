# Cartas e atributos — SuperTrunfIA

> **Proposta aprovada de balanceamento — 2 de novembro de 2026.** Esta versão reduz a força numérica geral das cartas e reorganiza o baralho em quatro classes. As pontuações são valores de gameplay, não percentuais de acerto nem resultados oficiais de benchmarks.

## 1. Estrutura do baralho

- **34 cartas no total:** 33 modelos de IA e 1 carta especial.
- **9 empresas representadas:** OpenAI, Anthropic, Google DeepMind, Meta, xAI, Mistral AI, DeepSeek, Cohere e NVIDIA.
- **4 atributos:** Raciocínio, Programação, Matemática e Conhecimento.
- **Escala:** 0 a 100 pontos por atributo.
- **Carta especial:** Alan Turing — Super Trunfo.

## 2. Classes de força

A classe de cada carta é determinada pela média aritmética simples dos quatro atributos. As faixas são inclusivas no limite inferior e exclusivas no limite superior, exceto a classe D.

| Classe | Média dos atributos | Quantidade | Interpretação |
|---|---:|---:|---|
| **A** | 88 a 92 | 4 | Elite: cartas mais fortes do baralho |
| **B** | 80 a menos de 88 | 6 | Avançada: cartas fortes, com limitações |
| **C** | 70 a menos de 80 | 10 | Intermediária: força moderada e vantagens situacionais |
| **D** | Abaixo de 70 | 14 | Básica: cartas mais fracas ou de gerações anteriores |
| **Total** | | **34** | |

A média serve para classificar a carta, mas não elimina a importância das especializações. Uma carta pode ter vantagem em um atributo específico mesmo estando em uma classe inferior.

## 3. Definição dos atributos

| Atributo | O que representa |
|---|---|
| **Raciocínio** | Resolver problemas lógicos, abstratos, científicos e dedutivos, inclusive tarefas de várias etapas. |
| **Programação** | Compreender, escrever, depurar e modificar código e resolver tarefas de engenharia de software. |
| **Matemática** | Resolver problemas quantitativos, aritméticos, algébricos e matemáticos avançados. |
| **Conhecimento** | Amplitude, precisão e aplicação de conhecimento geral, científico, acadêmico e profissional. |

## 4. Cartas e pontuações aprovadas

As médias abaixo são calculadas a partir dos quatro atributos. Os IDs seguem a ordem das classes e são os identificadores utilizados no CSV.

### Classe A — Elite (4 cartas)

| ID | Empresa | Modelo | Raciocínio | Programação | Matemática | Conhecimento | Média |
|---:|---|---|---:|---:|---:|---:|---:|
| 1 | OpenAI | GPT-6 Astra | 92 | 90 | 91 | 90 | 90,8 |
| 2 | Anthropic | Claude Opus 5.5 | 91 | 92 | 89 | 89 | 90,3 |
| 3 | Google DeepMind | Gemini 4 Argon | 91 | 89 | 90 | 92 | 90,5 |
| 4 | DeepSeek | DeepSeek V4-Pro | 89 | 90 | 91 | 88 | 89,5 |

### Classe B — Avançada (6 cartas)

| ID | Empresa | Modelo | Raciocínio | Programação | Matemática | Conhecimento | Média |
|---:|---|---|---:|---:|---:|---:|---:|
| 5 | OpenAI | GPT-6.1 Sol | 87 | 86 | 86 | 87 | 86,5 |
| 6 | Anthropic | Claude Sonnet 5.5 | 86 | 88 | 83 | 85 | 85,5 |
| 7 | Google DeepMind | Gemini 3.1 Pro | 86 | 84 | 87 | 87 | 86,0 |
| 8 | xAI | Grok 4.7 | 85 | 86 | 80 | 83 | 83,5 |
| 9 | DeepSeek | DeepSeek R1 | 86 | 82 | 89 | 80 | 84,3 |
| 10 | Mistral AI | Mistral Large 4 | 84 | 85 | 83 | 83 | 83,8 |

### Classe C — Intermediária (10 cartas)

| ID | Empresa | Modelo | Raciocínio | Programação | Matemática | Conhecimento | Média |
|---:|---|---|---:|---:|---:|---:|---:|
| 11 | OpenAI | GPT-6.1 Terra | 79 | 77 | 80 | 78 | 78,5 |
| 12 | Anthropic | Claude Fable 5.1 | 80 | 79 | 81 | 76 | 79,0 |
| 13 | Anthropic | Claude Mythos 5.1 | 79 | 78 | 80 | 77 | 78,5 |
| 14 | Google DeepMind | Gemini 3.8 Flash | 79 | 80 | 76 | 78 | 78,3 |
| 15 | Google DeepMind | Gemini 3.7 Flash | 76 | 75 | 73 | 77 | 75,3 |
| 16 | Meta | Muse Spark | 78 | 70 | 75 | 79 | 75,5 |
| 17 | Meta | Llama 4 Maverick | 75 | 73 | 70 | 75 | 73,3 |
| 18 | xAI | Grok 4.6 | 80 | 79 | 74 | 77 | 77,5 |
| 19 | Mistral AI | Mistral Small 4 | 75 | 76 | 73 | 74 | 74,5 |
| 20 | Especial | Alan Turing | 78 | 55 | 78 | 72 | 70,8 |

Alan Turing permanece como carta especial. Seus valores são simbólicos e temáticos, não uma comparação técnica com LLMs. A carta mantém destaque relativo em Raciocínio e Matemática, mas sua força geral foi reduzida para se encaixar na Classe C.

### Classe D — Básica (14 cartas)

| ID | Empresa | Modelo | Raciocínio | Programação | Matemática | Conhecimento | Média |
|---:|---|---|---:|---:|---:|---:|---:|
| 21 | OpenAI | GPT-6 Luna | 68 | 66 | 65 | 69 | 67,0 |
| 22 | Meta | Llama 4 Scout | 65 | 62 | 60 | 65 | 63,0 |
| 23 | Meta | Llama 3.3 70B Instruct | 66 | 65 | 62 | 68 | 65,3 |
| 24 | xAI | Grok 4.5 | 68 | 67 | 62 | 66 | 65,8 |
| 25 | xAI | Grok 3 | 64 | 63 | 64 | 65 | 64,0 |
| 26 | Mistral AI | Ministral 3 14B | 62 | 62 | 60 | 64 | 62,0 |
| 27 | Mistral AI | Mistral 7B | 55 | 57 | 52 | 58 | 55,5 |
| 28 | DeepSeek | DeepSeek V4.1 Flash | 69 | 69 | 68 | 65 | 67,8 |
| 29 | DeepSeek | DeepSeek V3.2 | 67 | 68 | 67 | 65 | 66,8 |
| 30 | Cohere | Command A+ | 66 | 64 | 58 | 68 | 64,0 |
| 31 | Cohere | Command A | 63 | 61 | 57 | 66 | 61,8 |
| 32 | NVIDIA | Nemotron 3 Ultra | 68 | 69 | 66 | 64 | 66,8 |
| 33 | NVIDIA | Nemotron 3 Super | 65 | 66 | 63 | 62 | 64,0 |
| 34 | NVIDIA | Nemotron 2 Nano | 55 | 57 | 52 | 60 | 56,0 |

## 5. Modelos removidos

Seis cartas foram removidas para chegar à composição aprovada de 34:

| Empresa | Modelo | Motivo de seleção |
|---|---|---|
| OpenAI | GPT-3.5 Turbo | Carta histórica e redundante no conjunto final. |
| Anthropic | Claude 2 | Geração histórica, substituída por cartas mais representativas da família. |
| Google DeepMind | PaLM 2 | Geração anterior à família Gemini. |
| Meta | Llama 2 7B | Modelo histórico, com sobreposição de papel com outras cartas de legado. |
| xAI | Grok-1 | Primeira geração, com baixa relevância competitiva no conjunto. |
| Cohere | Command R | Sobreposição com Command A e Command A+. |

A seleção preserva as nove empresas, mas não exige uma quantidade idêntica de cartas por fabricante.

## 6. Distribuição final

| Empresa / carta | Quantidade |
|---|---:|
| OpenAI | 4 |
| Anthropic | 4 |
| Google DeepMind | 4 |
| Meta | 4 |
| xAI | 4 |
| Mistral AI | 4 |
| DeepSeek | 4 |
| Cohere | 2 |
| NVIDIA | 3 |
| **Modelos de IA** | **33** |
| Alan Turing — especial | 1 |
| **Total** | **34** |

| Classe | Cartas | Participação |
|---|---:|---:|
| A | 4 | 11,8% |
| B | 6 | 17,6% |
| C | 10 | 29,4% |
| D | 14 | 41,2% |
| **Total** | **34** | **100%** |

## 7. Regras de balanceamento desta versão

1. A classe é calculada pela média simples dos quatro atributos.
2. Nenhum atributo foi aumentado em relação à versão anterior do CSV; as pontuações foram mantidas ou reduzidas.
3. As reduções são ajustes de gameplay e não devem ser interpretadas como novas medições de capacidade real.
4. Especializações foram preservadas quando possível: DeepSeek R1 mantém destaque em Matemática; Alan Turing mantém destaque temático em Raciocínio e Matemática.
5. A classe não substitui a comparação individual dos atributos durante uma rodada.
6. A regra de vitória da carta Super Trunfo deve ser aplicada pelo motor do jogo, separadamente dos valores e das classes.

## 8. Testes recomendados

- Simular confrontos entre cartas de classes diferentes para verificar se as classes produzem diferenças perceptíveis.
- Verificar a frequência de vitória por atributo e por empresa.
- Observar se alguma carta da Classe D vence com frequência desproporcional por especialização.
- Testar a regra especial de Alan Turing separadamente.
- Ajustar valores somente após partidas de teste, registrando o motivo de cada mudança.

## 9. Limitações

As pontuações são parâmetros de balanceamento de um jogo. Não existe um benchmark único que meça exatamente os quatro atributos aqui definidos, e resultados de avaliações diferentes não são diretamente intercambiáveis. Nomes, versões e descrições dos modelos devem ser validados antes de uma edição que pretenda representar rigorosamente o estado real do mercado.

## 10. Histórico

- **Versão anterior:** 40 cartas (39 modelos e Alan Turing), com pontuações provisórias.
- **2 de novembro de 2026 — balanceamento aprovado:** baralho reduzido para 34 cartas (33 modelos e Alan Turing), seis modelos removidos, quatro classes definidas e atributos reduzidos para criar uma distribuição de força mais baixa.
