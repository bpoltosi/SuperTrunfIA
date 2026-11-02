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

| ID | Classe | Empresa | Modelo / carta | Raciocínio | Programação | Matemática | Conhecimento |
|---:|:---:|---|---|---:|---:|---:|---:|
| 1 | A | Especial | Alan Turing — Super Trunfo | 90 | 70 | 99 | 80 |
| 2 | A | OpenAI | GPT-6 Astra | 92 | 90 | 91 | 90 |
| 3 | A | Anthropic | Claude Opus 5.5 | 91 | 92 | 89 | 89 |
| 4 | A | Google DeepMind | Gemini 4 Argon | 91 | 89 | 90 | 92 |
| 5 | A | DeepSeek | DeepSeek V4-Pro | 89 | 90 | 91 | 88 |
| 6 | B | OpenAI | GPT-6.1 Sol | 87 | 86 | 86 | 87 |
| 7 | B | Anthropic | Claude Sonnet 5.5 | 86 | 88 | 83 | 85 |
| 8 | B | Google DeepMind | Gemini 3.1 Pro | 86 | 84 | 87 | 87 |
| 9 | B | xAI | Grok 4.7 | 85 | 86 | 80 | 83 |
| 10 | B | DeepSeek | DeepSeek R1 | 86 | 82 | 89 | 80 |
| 11 | B | Mistral AI | Mistral Large 4 | 84 | 85 | 83 | 83 |
| 12 | C | OpenAI | GPT-6.1 Terra | 79 | 77 | 80 | 78 |
| 13 | C | Anthropic | Claude Fable 5.1 | 80 | 79 | 81 | 76 |
| 14 | C | Anthropic | Claude Mythos 5.1 | 79 | 78 | 80 | 77 |
| 15 | C | Google DeepMind | Gemini 3.8 Flash | 79 | 80 | 76 | 78 |
| 16 | C | Google DeepMind | Gemini 3.7 Flash | 76 | 75 | 73 | 77 |
| 17 | C | Meta | Muse Spark | 78 | 70 | 75 | 79 |
| 18 | C | Meta | Llama 4 Maverick | 75 | 73 | 70 | 75 |
| 19 | C | xAI | Grok 4.6 | 80 | 79 | 74 | 77 |
| 20 | C | Mistral AI | Mistral Small 4 | 75 | 76 | 73 | 74 |
| 21 | D | OpenAI | GPT-6 Luna | 68 | 66 | 65 | 69 |
| 22 | D | Meta | Llama 4 Scout | 65 | 62 | 60 | 65 |
| 23 | D | Meta | Llama 3.3 70B Instruct | 66 | 65 | 62 | 68 |
| 24 | D | xAI | Grok 4.5 | 68 | 67 | 62 | 66 |
| 25 | D | xAI | Grok 3 | 64 | 63 | 64 | 65 |
| 26 | D | Mistral AI | Ministral 3 14B | 62 | 62 | 60 | 64 |
| 27 | D | Mistral AI | Mistral 7B | 55 | 57 | 52 | 58 |
| 28 | D | DeepSeek | DeepSeek V4.1 Flash | 69 | 69 | 68 | 65 |
| 29 | D | DeepSeek | DeepSeek V3.2 | 67 | 68 | 67 | 65 |
| 30 | D | Cohere | Command A+ | 66 | 64 | 58 | 68 |
| 31 | D | Cohere | Command A | 63 | 61 | 57 | 66 |
| 32 | D | NVIDIA | Nemotron 3 Ultra | 68 | 69 | 66 | 64 |
| 33 | D | NVIDIA | Nemotron 3 Super | 65 | 66 | 63 | 62 |
| 34 | D | NVIDIA | Nemotron 2 Nano | 55 | 57 | 52 | 60 |

## Definição dos atributos

- **Raciocínio:** resolução de problemas lógicos, abstratos, científicos e dedutivos.
- **Programação:** compreensão, escrita, depuração e modificação de código.
- **Matemática:** resolução de problemas quantitativos, algébricos e matemáticos.
- **Conhecimento:** amplitude, precisão e aplicação de conhecimento geral, científico e profissional.

## Regra da carta especial

Super Trunfo vence automaticamente cartas das classes B, C e D. Contra uma carta da classe A, compara-se o atributo escolhido normalmente. O motor consulta o campo de classe gravado na carta.

## Fonte dos valores

As pontuações são parâmetros de balanceamento do jogo, não percentuais de acerto nem resultados oficiais de benchmarks. As reduções foram feitas para ajustar a força relativa das cartas. As pontuações de Alan Turing são simbólicas e temáticas, não uma comparação técnica com LLMs.

## Histórico

- **2 de novembro de 2026:** distribuição aprovada atualizada para A=5, B=6, C=9 e D=14. Alan Turing passou explicitamente para A, sem alteração dos seus quatro atributos e sem ser contabilizado como modelo.
