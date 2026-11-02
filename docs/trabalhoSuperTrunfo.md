Trabalho Avaliativo - Super Trunfo!
Desenvolver um programa para simular um jogo de Super Trunfo entre dois
jogadores. Para isso, considere as seguintes regras:
1. Sabe-se que existem vários temas para o jogo. Escolher um dos existentes e
descrevê-lo em um arquivo .txt que deve ser enviado junto com o código do
programa. Alternativamente, o desenvolvedor pode criar um tema, desde que
siga as premissas do jogo, considerando:
a. A existência da carta coringa (Super trunfo);
b. Para cada carta, conter pelo menos três características daquele item;
c. Marcação com letras A, B, C e D.
2. O baralho deve ter pelo menos 24 cartas. Sugestão: Inserir manualmente as
cartas para facilitar testes do software
3. As cartas devem ser distribuídas aleatoriamente aos jogadores
(embaralhadas). Um monte com metade do baralho para cada jogador;
4. Na sua vez de jogar, os jogadores só podem utilizar a carta da frente do seu
monte;
5. O jogador que iniciar deve escolher uma característica da carta e “ler em voz
alta”. Essa característica é comparada com a da carta do adversário. Aquele
que tiver melhor pontuação, leva as duas cartas, que devem ser colocadas no
final do monte;
6. O jogador que vencer a rodada tem direito de escolher a característica da
próxima carta;
7. Em caso de empate, as cartas envolvidas devem ser colocadas na “mesa” e o
desempate é feito com as próximas cartas. Quem ganhar, leva todas as
cartas envolvidas;
8. A carta marcada com “Super trunfo” ganha a rodada automaticamente, sem
necessidade de escolha de características (marcação com seta na imagem
abaixo). A “Super trunfo” só não ganha automáticamente contra cartas de
classe A, fazendo que tenha necessidade de comparação de uma
característica escolhida pelo mão;
9. A regra para definição da carta Super trunfo deve ser definida pelo
desenvolvedor e descrita no arquivo .txt;
10.O jogo termina quando um dos jogadores ficar com todas as cartas;
11. Todo jogo deve acontecer de forma automática, ou seja, sem entradas
explícitas do usuário. Utilize funções como system("pause") e system("clear")
para facilitar o entendimento do que acontece.
12.Sugestão: utilize uma biblioteca para desenvolver as funções do jogo;
Casos omissos devem ser tratados pelo desenvolvedor. Não há necessidade de
utilizar bibliotecas gráficas, somente o terminal basta.