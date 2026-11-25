# Cartas e atributos — SuperTrunfIA

## Estrutura aprovada

O baralho contém **34 cartas**: 33 modelos de IA e uma carta especial, Alan Turing. Cada carta tem quatro atributos (Raciocínio, Programação, Matemática e Conhecimento), com valores de 0 a 100, e uma classe explícita A, B, C ou D.

A classe é armazenada como atributo próprio no CSV. Ela não é inferida nem recalculada pela média dos atributos durante a partida.

| Classe | Cartas | Modelos | Composição |
|---|---:|---:|---|
| A | 5 | 4 | 4 modelos + Alan Turing |
| B | 6 | 6 | 6 modelos |
| C | 9 | 9 | 9 modelos |
| D | 14 | 14 | 14 modelos |
| **Total** | **34** | **33** | **33 modelos + 1 especial** |

## Alan Turing — Super Trunfo

Alan Turing permanece com seus atributos atuais: **Raciocínio 90, Programação 70, Matemática 99 e Conhecimento 80**. Raciocínio e Matemática são seus dois atributos muito fortes; Programação e Conhecimento são medianos. Ele pertence explicitamente à Classe A, apesar de sua média não atingir a faixa numérica usual dessa classe.

Turing é uma carta especial e **não é contado como modelo de IA** nem na quantidade de modelos por empresa.

## Lista do baralho

| ID | Classe | Empresa | Modelo / carta | Raciocinio | Programacao | Matematica | Conhecimento |
|---:|:---:|---|---|---:|---:|---:|---:|
| 1 | A | Especial | Alan Turing - Super Trunfo | 90 | 70 | 99 | 80 |
| 2 | A | OpenAI | GPT-6 Astra | 100 | 100 | 100 | 100 |
| 3 | A | Anthropic | Claude Opus 5.5 | 100 | 100 | 100 | 100 |
| 4 | A | Google DeepMind | Gemini 4 Argon | 100 | 100 | 100 | 100 |
| 5 | A | DeepSeek | DeepSeek V4-Pro | 100 | 100 | 100 | 100 |
| 6 | B | OpenAI | GPT-6.1 Sol | 100 | 100 | 100 | 100 |
| 7 | B | Anthropic | Claude Sonnet 5.5 | 100 | 100 | 100 | 100 |
| 8 | B | Google DeepMind | Gemini 3.1 Pro | 100 | 100 | 100 | 100 |
| 9 | B | xAI | Grok 4.7 | 97 | 98 | 94 | 96 |
| 10 | B | DeepSeek | DeepSeek R1 | 99 | 97 | 100 | 96 |
| 11 | B | Mistral AI | Mistral Large 4 | 97 | 98 | 96 | 96 |
| 12 | C | OpenAI | GPT-6.1 Terra | 84 | 83 | 84 | 84 |
| 13 | C | Anthropic | Claude Fable 5.1 | 86 | 85 | 86 | 84 |
| 14 | C | Anthropic | Claude Mythos 5.1 | 84 | 84 | 84 | 83 |
| 15 | C | Google DeepMind | Gemini 3.8 Flash | 84 | 84 | 82 | 83 |
| 16 | C | Google DeepMind | Gemini 3.7 Flash | 76 | 76 | 74 | 76 |
| 17 | C | Meta | Muse Spark | 78 | 74 | 76 | 78 |
| 18 | C | Meta | Llama 4 Maverick | 72 | 70 | 69 | 72 |
| 19 | C | xAI | Grok 4.6 | 82 | 82 | 80 | 81 |
| 20 | C | Mistral AI | Mistral Small 4 | 74 | 74 | 73 | 74 |
| 21 | D | OpenAI | GPT-6 Luna | 56 | 54 | 54 | 56 |
| 22 | D | Meta | Llama 4 Scout | 46 | 44 | 44 | 46 |
| 23 | D | Meta | Llama 3.3 70B Instruct | 51 | 50 | 49 | 52 |
| 24 | D | xAI | Grok 4.5 | 53 | 52 | 50 | 52 |
| 25 | D | xAI | Grok 3 | 48 | 47 | 48 | 48 |
| 26 | D | Mistral AI | Ministral 3 14B | 42 | 42 | 42 | 44 |
| 27 | D | Mistral AI | Mistral 7B | 26 | 27 | 24 | 28 |
| 28 | D | DeepSeek | DeepSeek V4.1 Flash | 58 | 58 | 57 | 56 |
| 29 | D | DeepSeek | DeepSeek V3.2 | 54 | 55 | 54 | 54 |
| 30 | D | Cohere | Command A+ | 48 | 48 | 44 | 50 |
| 31 | D | Cohere | Command A | 42 | 42 | 40 | 44 |
| 32 | D | NVIDIA | Nemotron 3 Ultra | 55 | 56 | 54 | 53 |
| 33 | D | NVIDIA | Nemotron 3 Super | 48 | 48 | 47 | 46 |
| 34 | D | NVIDIA | Nemotron 2 Nano | 27 | 28 | 26 | 30 |

## Definição dos atributos

- **Raciocínio:** resolução de problemas lógicos, abstratos, científicos e dedutivos.
- **Programação:** compreensão, escrita, depuração e modificação de código.
- **Matemática:** resolução de problemas quantitativos, algébricos e matemáticos.
- **Conhecimento:** amplitude, precisão e aplicação de conhecimento geral, científico e profissional.

## Regra da carta especial

Super Trunfo vence automaticamente cartas das classes B, C e D. Contra uma carta da classe A, compara-se o atributo escolhido normalmente. O motor consulta o campo de classe gravado na carta.

## Fonte dos valores

As pontuacoes sao parametros de balanceamento do jogo, nao percentuais de acerto nem resultados oficiais de benchmarks. A calibracao da V1 foi revisada com 2.000 partidas simuladas, preservando a ordem tematica das classes e a carta especial. As pontuacoes de Alan Turing sao simbolicas e tematicas, nao uma comparacao tecnica com LLMs.

## Histórico

- **2 de novembro de 2026:** distribuição aprovada atualizada para A=5, B=6, C=9 e D=14. Alan Turing passou explicitamente para A, sem alteração dos seus quatro atributos e sem ser contabilizado como modelo.

- **25 de novembro de 2026:** atributos recalibrados apos benchmark reproduzivel de 2.000 partidas; media ajustada por carta = 78 + 2,5 * (media original - 78), com metade dos desvios originais preservada. Alan Turing permanece em 90/70/99/80 e a composicao A=5, B=6, C=9, D=14 foi mantida.
