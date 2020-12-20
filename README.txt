*********************************************************************
*	Nome do Programa: BlackJack										*
*	Autores: Ana Margarida Maduro 67495; Francisco Filipe 66613		*
* 	Projecto Lab1 - TIC												*
*	Descrição: Utilizaçao do jogo									*
*********************************************************************

O programa começa com dar as boas vindas ao jogador, de seguida apresenta algumas opções de funcionaliades:
	1. Jogar; 2. Carregar resultados; 3. Regras; 4. Creditos; 5.Sair
	
Caso o jogador decida jogar é chamda a função playgame(), consiste em todo o jogo.
Começa por perguntar quantos jogadores reais jogaram, no maximo 5.

Tendo em conta que no maximo podem jogar 5 jogadores reais mais o dealer, é gerado automaticamente
o numero de jogadores virtuais que iram estar presentes. Segundo este calculo "numPlayers = inputPlayers + vrPLayers + 1; // O +1 É O DEALER"
Pede os nomes dos jogadores reais.

CRIA UM ARRAY MULTIDIMENSIONAL INICIALIZADO COM ZEROS
	NO PRIMEIRO ARRAY GUARDA O INDEX DOS PLAYERS
	NO SEGUNDO GUARDA AS APOSTAS
	NO TERCEIRO OS PONTOS DOS PLAYERS
	NO QUARTO O MONEY TOTAL

De seguida, para todos os jogadores reais, pede a sua aposta, minimo 100, maximo o montante de dinheiro (para começar 5000)
Para os jogadores virtuais gera valores aleatorios entre, 1 e 1000

Para todos os jogadores reais, inicia a rounda, perguntando se quer comprar, parar, dobrar ou desistir.
O jogador continua a jogar até parar ou superar 21 pontos.

Quando a rounda dos jogadores reais terminar, o programa joga automaticamente.
Indo buscar aleatoriamente cartas aos baralhos (num de baralhos gerado automaticamente) e indo fazendo a verificação dos pontos.

Quando termina a jogada, faz o calculo para quem ganhou ou dealer
Escreve no ficheiro "logs.txt"

Pergunta que quer voltar a jogar

Regras do jogo:
	O Blackjack consiste num jogo de cartas onde:
	O maximo de pontos que um jogador pode fazer e 21
	Cada carta de 2 a 10 vale o valor representado
	O Rei, Valete e Dama valem 10 pontos cada
	O jogador começa com 5000 de banca, e tem de cumprir uma aposta minima de 100 em cada jogada