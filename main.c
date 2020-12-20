/********************************************************************
*	Nome do Programa: BlackJack										*
*	Nome do Ficheiro: main.c										*
*	Autores: Ana Margarida Maduro 67495; Francisco Filipe 66613		*
* 	Projecto Lab1 - TIC												*
*	Descrição: Ficheiro principal do jogo							*
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "functions.h"

#define STARTING_MONEY 5000
static const char LOG_FILE[] = "logs.txt";

int main()	{
	srand(time(NULL));
	int input, checkInput;	
	
	// LIMPA ECRA E ESCREVE O HEAD
	// PERGUNTA PELA OPCAO
	clearScreen();
	head();

	printf("Bem-Vindos ao Blackjack\n\n");
	printf("1. Jogar\n");
	printf("2. Carregar resultados\n");
	printf("3. Regras\n");
	printf("4. Creditos\n");
	printf("5. Sair\n");
	
	do {
		printf("Escolha > ");
		scanf("%d", &input);
	} while ((input < 1) || (input > 4) );
	
	switch ( input ) {
	case 1:
		playgame();
		break;
	case 2:          
		loadgame();
		break;
	case 3:        
		howto();
		break;
	case 4:        
		creditos();
		break;
	case 5:
		printf( "Obrigado por jogar!\n" );
		break;
	}

	return 0;
}


int playgame() {
	
	// DECLARACAO DE VARS
	int inputPlayers, vrPLayers, numPlayers;
	int i, j;
	int bet;
	int card, numCards;
	int numDecks;
	int input, again;
	int deck[] = {0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 16};
				// 0, A, 2, 3, 4, 5, 6, 7, 8, 9, MONKEYS

		
	// LIMPA ECRA E ESCREVE O HEAD
	clearScreen();
	head();
	printf("Let's play! \n\n");
	
	
	// PREGUNTA O NUM DE JOGADORES REAIS
	// PERGUNTA ENQUANTO O NUMERO FOR SUPERIOR A 5
	do {
		printf ("Quantos jogadores reais (Maximo 5 jogadores) > ");
		scanf("%d", &inputPlayers);
	} while ((inputPlayers < 1) || (inputPlayers > 5 ));
	

	// CALCULA O NUMERO DE JOGADORES VIRTUAIS
	if (inputPlayers < 5) {
		vrPLayers = getRand(1,6 - inputPlayers);	
	} else {
		vrPLayers = 0;
	}
	numPlayers = inputPlayers + vrPLayers + 1; // O +1 É O DEALER
	
	
	printf("Reais: %d\n", inputPlayers);
	printf("Virtuais: %d\n", vrPLayers);
	printf("Total: %d\n\n", numPlayers);
	
	
	// CRIA UM ARRAY MULTIDIMENSIONAL INICIALIZADO COM ZEROS
	// 		NO PRIMEIRO ARRAY GUARDA O INDEX DOS PLAYERS
	// 		NO SEGUNDO GUARDA AS APOSTAS
	//		NO TERCEIRO OS PONTOS DOS PLAYERS
	//		NO QUARTO O MONEY TOTAL
	int playersArray[4][numPlayers];
	for (i = 0; i < 4; i++) {
		for (j = 0; j < numPlayers; j++) {
			playersArray[i][j] = 0;
		}
	}
	
	
	// PERGUNTA OS NOMES AOS JOGADORES REAIS
	char namesArray[inputPlayers][20];	
	for(i = 0; i < inputPlayers; i++) {
		printf("Player %d introduza o seu nome > ", i);
		scanf("%s", namesArray[i]);
	}

	
	// INTRODUZ OS PLAYERS NO PRIMEIRO ARRAY
	for (i = 0; i < numPlayers; i++) {
		playersArray[0][i] = i;
	}
	
	printf("Todos os jogadores comeam com %d", STARTING_MONEY);
	//INTRODUZ AS APOSTAS NO SEGUNDO ARRAY
	for (i = 0; i < numPlayers - 1; i++) {
		if (i < inputPlayers) {
			do {
				printf("\nPlayer %s\n", namesArray[i]);
				printf("Aposta (Min: 100; Max: 5000)> ");
				scanf("%d", &bet);			
			} while ((bet < 100) || (bet > 5000));
		} else {
			bet = getRand(1, 1000);
		}
		playersArray[1][i] = bet;
		printf("\n");
	}

	//QUANTOS BARALHOS?
	numDecks = getRand(1, 8);
	//printf("Vamos jogar com %d baralho(s)", numDecks);
	for(i = 0; i < 10; i++) {
		deck[i] = deck[i] * numDecks;
	}
	
	//DAR CARTAS - Dá duas cartas a cada player, dealer included
	for (j = 0; j < 2; j++) {
		for (i = 0; i < numPlayers; i++) {
			card = getRand(1, 10);
			playersArray[2][i] += card;
			deck[card]--;
		}
	}
	
	// COLOCA STARTING_MONEY NA POSICAO DO MONEY TOTAL
	for (j = 0; j < numPlayers - 1; j++) {
		playersArray[3][j] = STARTING_MONEY;
	}	
	
	// ROUNDAS INDIVIDUAIS
		// INPPUT PLAYERS
	for (i = 0; i < inputPlayers; i++) {

		clearScreen();
		// PERGUNTA PELA OPCAO	
		printf("O que pretende fazer?\n\n");
		printf("1. Comprar\n");
		printf("2. Parar\n");
		printf("3. Dobro\n");
		printf("4. Desistir\n\n");		

		printf("Player %s\n", namesArray[i]);
		printf("Aposta de %d\n", playersArray[1][i]);
		printf("Tem %d pontos agora\n", playersArray[2][i]);
		do {
			printf("Escolha > ");
			scanf("%d", &input);
		} while ((input < 1) || (input > 4));
	
		numCards = 0;
		// DA CARTA
		card = getRand(1, 10);
		playersArray[2][i] += card;
		deck[card]--;
		numCards++;				
		
		switch (input) {
			case 1:
					do {
						// DA NOVAMENTE CARTA
						card = getRand(1, 10);
						playersArray[2][i] += card;
						deck[card]--;
						numCards++;	
						printf("Tem %d pontos agora\n", playersArray[2][i]);
						
						if (playersArray[2][i] > 21) {
							printf("REBENTOU!!\n");
							playersArray[2][i] = 0;
							break;
						} else {
							do {
								printf("Outra (1) > ");
								scanf("%d", &again);
							} while (again < 1);

						}											
					} while ((again == 1) && (playersArray[2][i] <= 21));
					break;
		
			case 2:
					printf("Parou\n");
					break;
					
			case 3:
					if (numCards == 1) {
						
						// DUPLICA O VALOR DA APOSTA
						printf("Duplicar a aposta\n");
						playersArray[1][i] *= 2;
						printf("Aposta de %d\n", playersArray[1][i]);
						
						//DA NOVAMENTE CARTA
						card = getRand(1, 10);
						playersArray[2][i] += card;
						deck[card]--;
						numCards++;				
						printf("Tem %d pontos agora\n", playersArray[2][i]);
						if (playersArray[2][i] > 21) {
							printf("REBENTOU!!\n");
							playersArray[2][i] = 0;
							break;
						}											
					}
					break;
					
			case 4:
					//RECEBE METADE DO VALOR APOSTADO
					playersArray[1][i] = playersArray[1][i] / 2;
					break;
					
			default:
					printf("Nada");
		}
		printf("Proximo Player...");
		sleep(4);
	}
	
	//VR PLAYERS
	for (i = inputPlayers; i < numPlayers; i++) {
		printf("\n\nPlayer %d\n", i);
		
		do {
			printf("Dar cartas\n");
			sleep(1);
			card = getRand(1, 10);
			playersArray[2][i] += card;
			deck[card]--;
			printf("Tem %d pontos agora\n", playersArray[2][i]);
			
			if (playersArray[2][i] > 21) {
				printf("REBENTOU!!\n");
				playersArray[2][i] = 0;
				break;
			}
		} while (playersArray[2][i] < 17);
		
		printf("Proximo Player...");
		sleep(2);
	}
	
	printf("\n\n");
	//CALCULA QUEM GANHOU
	for (i = 0; i < numPlayers - 1; i++) {
		if (playersArray[2][i] > playersArray[2][numPlayers - 1 ]) {
			printf("Player %d GANHOU com %d pontos, Dealer tem %d pontos", playersArray[0][i], playersArray[2][i], playersArray[2][numPlayers - 1]);
			playersArray[3][i] += playersArray[1][i];
		}
		else {
			printf("Player %d PERDEU com %d pontos, Dealer tem %d pontos", playersArray[0][i], playersArray[2][i], playersArray[2][numPlayers - 1]);
			playersArray[3][i] -= playersArray[1][i];
		}
		printf("\n");
	}
	
	//ESCREVE O MAINARRAY NA CONSOLA
//	printf("\n");
//	for (i = 0; i < 4; i++) {
//		for (j = 0; j < numPlayers; j++) {
//			printf("%d - ", playersArray[i][j]);
//		}
//		printf("\n");
//	}
//	
	FILE *fp;
	fp = fopen(LOG_FILE, "w+");
	
	for (i = 0; i < inputPlayers; i++)	 {
		char pts[10];
		char money[10];
		sprintf(pts, "%d", playersArray[2][i]);
		sprintf(money, "%d", playersArray[3][i]);
		
		
		fputs("1", fp);
		fputs(":", fp);
		
		fputs(namesArray[i], fp);
		fputs(";", fp);
		
		fputs(pts, fp);
		fputs(";", fp);
		fputs(money, fp);

		fputs("\n", fp);		
	}
	
	fclose(fp);


	// JOGAR NOVAMENTE
	printf("\n");
	sleep(2);
	printf("Jogar novamente? (1 - sim) > ");
	scanf("%d", &again);
	
	if (again == 1) {
		loadgame();
	}
	else {
		printf( "Obrigado por jogar!\n" );
		return 0;
	}
}

int loadgame() {
	
	int numGame;
	
	char buf[1000];
    FILE* f = fopen(LOG_FILE, "r");
    

	if (f == NULL) { 
		printf("Nao existe registo de jogo\n");
		printf("Vamos comecar de novo!...\n");
		sleep(3);
		main();
	} else {
		
		while (fgets(buf,1000, f) != NULL)
			printf("%s",buf);
		
		//main();
	}

    fclose(f);
	return 0;
}

int howto() {
	int input;
	clearScreen();
	head();
	
	printf("O Blackjack consiste num jogo de cartas onde:\n");
	printf("\t-O maximo de pontos que um jogador pode fazer e 21;\n");
	printf("\t-Cada carta de 2 a 10 vale o valor representado;\n");
	printf("\t-O Rei, Valete e Dama valem 10 pontos cada;\n");
	printf("\t-O jogador começa com 5000 de banca, e tem de cumprir uma aposta minima de 100 em cada jogada;\n\n");
	printf("\tBoa sorte!\n\n");
	
	printf("1. Jogar\n");
	printf("2. Sair\n");
	do {
		printf("Escolha > ");
		scanf("%d", &input);
	} while ((input < 1) || (input > 2) );
	
	switch ( input ) {
	case 1:
		playgame();
		break;
	case 2:          
		printf( "Obrigado por jogar!\n" );
		break;
	}
		
	return 0;
}

int creditos() {
	clearScreen();
	head();
	
	printf("*********************************************************************\n");
	printf("*   Nome do Programa: BlackJack                                     *\n");
	printf("*   Nome do Ficheiro: main.c                                        *\n");
	printf("*   Autores: Ana Margarida Maduro 67495; Francisco Filipe 66613     *\n");
	printf("*   Projecto Lab1 - TIC                                             *\n");
	printf("*********************************************************************");
	
	return 0;	
	
}









