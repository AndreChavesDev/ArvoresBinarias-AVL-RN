#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "AVL.h"
#include "ARN.h"

// Autores:
// Andre Luiz Chaves Cruz 
// Joao Pedro Morais De Souza

void limpa();

void menuPrincipal() {
	int op = 1;
	while(op != 0) {

		printf("\nEstamos no MENU PRINCIPAL:\n\n");
		printf("[0] - Sair \n");
		printf("[1] - AVL \n");
		printf("[2] - ARN\n\n");

		printf("Escolha uma das arvores:\n> ");
		scanf("%d", &op);
		switch(op) {

			case 0:
				limpa();
				printf("\nVoce saiu!!! \n");
				break;

			case 1:
				system("cls");
				int op;
				printf("\nAVL...\n");

				menuAVL();
				menuPrincipal();
				break;

			case 2:
				system("cls");
				printf("\nARN...\n");

				menuRN();
				system("cls");
				menuPrincipal();
				break;

			default:
				system("cls");
				printf("\nINSIRA UMA OPCAO VALIDA!!! \n\n");
				menuPrincipal();
				break;
		}
		menuPrincipal();
	}
	printf("\n-----------------------------------------------------\n|     O programa foi finalizado com sucesso!        |\n-----------------------------------------------------\n");
}

//Auxiliares
void limpa() {
	system("cls");
	fflush(stdout);
	fflush(stdin);
}


void main() {
	menuPrincipal();

	printf("\n\nAutores:\n - Andre Luiz Chaves Cruz (AVL); \n - Joao Pedro Moraes de Souza (ARN);");
}

