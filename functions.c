/********************************************************************
*	Nome do Programa: BlackJack										*
*	Nome do Ficheiro: functions.c									*
*	Autores: Ana Margarida Maduro 67495; Francisco Filipe 66613		*
* 	Projecto Lab1 - TIC												*
*	Descrição: Ficheiro auxiliar; contém funções usadas em main.c	*
********************************************************************/

#include <stdio.h>
#include <time.h>

// LIMPA A CONSOLA
void clearScreen() {
	system("cls");	
}


// ESCREVE NA CONSOLA O HEADER DO JOGO
void head() {
	printf("*******************************\n");
	printf("********** BLACKJACK **********\n");
	printf("*******************************\n");
	printf("\n");
}


// RETORNA UM VALOR ALEATORIO ENTRE MIN E MAX
int getRand(int min, int max) {
	int randNum;
	
	randNum = (rand() % (max-min)) + min;
	
	return randNum;
}


void printArray(int arr[], int start, int len) {
	/* Recursion base condition */
	if(start >= len)
		return;
	
	/* Prints the current array element */
	printf("%d - ", arr[start]);
	
	/* Recursively call printArray to print next element in the array */
	printArray(arr, start + 1, len); 
}
