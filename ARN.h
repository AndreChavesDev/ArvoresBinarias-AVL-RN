#include <stdio.h>
#include <stdlib.h>
#define TAMMAX 100

typedef struct No {
	int id;
	struct No* pai;
	struct No* esquerda;
	struct No* direita;
	int corNo;
} No;

No* CrianovoNo(int id) {
	No* novoNo = (No*)malloc(sizeof(No));
	novoNo->id = id;
	novoNo->pai = NULL;
	novoNo->esquerda = NULL;
	novoNo->direita = NULL;
	novoNo->corNo = 1;
	return novoNo;
}

void esquerdaMover(No** no, No* x) {
	No* y = x->direita;
	x->direita = y->esquerda;
	if (y->esquerda != NULL)
		y->esquerda->pai = x;
	y->pai = x->pai;
	if (x->pai == NULL)
		*no = y;
	else if (x == x->pai->esquerda)
		x->pai->esquerda = y;
	else
		x->pai->direita = y;
	y->esquerda = x;
	x->pai = y;
}

void direitaMover(No** no, No* y) {
	No* x = y->esquerda;
	y->esquerda = x->direita;
	if (x->direita != NULL)
		x->direita->pai = y;
	x->pai = y->pai;
	if (y->pai == NULL)
		*no = x;
	else if (y == y->pai->esquerda)
		y->pai->esquerda = x;
	else
		y->pai->direita = x;
	x->direita = y;
	y->pai = x;
}


void InciciaNoNulo(No **no) {
	(*no) = NULL;
}

void excluirNo(No **no, int id) {
	if ((*no) != NULL) {
		if ((*no)->id > id) {
			excluirNo(&(*no)->esquerda, id);
		} else if ((*no)->id < id) {
			excluirNo(&(*no)->direita, id);
		} else {
			// Nó encontrado
			if ((*no)->esquerda == NULL && (*no)->direita == NULL) { // Nó sem filhos
				if ((*no)->pai != NULL) {
					if ((*no)->pai->esquerda == (*no)) {
						(*no)->pai->esquerda = NULL;
					} else {
						(*no)->pai->direita = NULL;
					}
				} else {
					free(*no);
					*no = NULL;
					return;
				}
				free(*no);
			} else if ((*no)->esquerda != NULL && (*no)->direita != NULL) { // Nó com dois filhos
				No *sucessor = (*no)->direita;
				while (sucessor->esquerda != NULL) {
					sucessor = sucessor->esquerda;
				}
				(*no)->id = sucessor->id;
				excluirNo(&(*no)->direita, sucessor->id);
			} else { // Nó com um filho
				No *filho = ((*no)->esquerda != NULL) ? (*no)->esquerda : (*no)->direita;
				if ((*no)->pai != NULL) {
					if ((*no)->pai->esquerda == (*no)) {
						(*no)->pai->esquerda = filho;
					} else {
						(*no)->pai->direita = filho;
					}
					filho->pai = (*no)->pai;
				} else {
					filho->pai = NULL;
					*no = filho;
				}
				free(*no);
			}
		}
	}
}

void Balanciamento(No** no, No* novoNo) {
	No* pai = NULL;
	No* vodoNo = NULL;

	while ((novoNo != *no) && (novoNo->corNo == 1) && (novoNo->pai->corNo == 1)) {
		pai = novoNo->pai;
		vodoNo = pai->pai;

		if (pai == vodoNo->esquerda) {
			No* filho = vodoNo->direita;

			if (filho != NULL && filho->corNo == 1) {
				vodoNo->corNo = 1;
				pai->corNo = 0;
				filho->corNo = 0;
				novoNo = vodoNo;
			} else {
				if (novoNo == pai->direita) {
					esquerdaMover(no, pai);
					novoNo = pai;
					pai = novoNo->pai;
				}
				direitaMover(no, vodoNo);
				int temp = pai->corNo;
				pai->corNo = vodoNo->corNo;
				vodoNo->corNo = temp;
				novoNo = pai;
			}
		} else {
			No* filho = vodoNo->esquerda;
			if ((filho != NULL) && (filho->corNo == 1)) {
				vodoNo->corNo = 1;
				pai->corNo = 0;
				filho->corNo = 0;
				novoNo = vodoNo;
			} else {
				if (novoNo == pai->esquerda) {
					direitaMover(no, pai);
					novoNo = pai;
					pai = novoNo->pai;
				}
				esquerdaMover(no, vodoNo);
				int temp = pai->corNo;
				pai->corNo = vodoNo->corNo;
				vodoNo->corNo = temp;
				novoNo = pai;
			}
		}
	}
	(*no)->corNo = 0;
}

void inserir(No** no, int id) {

	No* novoNo = CrianovoNo(id);
	No* current = *no;
	No* pai = NULL;

	while (current != NULL) {
		pai = current;
		if (novoNo->id < current->id)
			current = current->esquerda;
		else
			current = current->direita;
	}
	novoNo->pai = pai;
	if (pai == NULL)
		*no = novoNo;
	else if (novoNo->id < pai->id)
		pai->esquerda = novoNo;
	else
		pai->direita = novoNo;
	Balanciamento(no, novoNo);
}


No* Busca(No* no, int id) {
	if (no == NULL || no->id == id)
		return no;
	if (id < no->id)
		return Busca(no->esquerda, id);
	return Busca(no->direita, id);
}

void PreOrder(No* no) {
	if (no == NULL)
		return;

	printf("%d ", no->id);
	PreOrder(no->esquerda);
	PreOrder(no->direita);
}

void PosOrder(No* no) {
	if (no == NULL)
		return;

	PosOrder(no->esquerda);
	PosOrder(no->direita);
	printf("%d ", no->id);
}

void InOrder(No* no) {
	if (no == NULL)
		return;

	InOrder(no->esquerda);
	printf("%d ", no->id);
	InOrder(no->direita);
}

void imprimeArvore(No* no, int nivel) {
	if (no == NULL) {
		return;
	}

	int i;
	imprimeArvore(no->direita, nivel + 1);

	for (i = 0; i < nivel; i++) {
		printf("    ");
	}

	if (no->corNo == 0) {
		printf("(%d)\n", no->id);

	} else {
		printf("[%d]\n", no->id);
	}

	imprimeArvore(no->esquerda, nivel + 1);
}

int printMenu() {
	int num;
	printf("\n1 - Inserir No na Arvore");
	printf("\n2 - Imprimir Arvore Rubro-Negra (in-order, pre-order, pos-order)");
	printf("\n3 - Buscar No na Arvore");
	printf("\n4 - Remover No da Arvore");
	printf("\n5 - Imprimir Arvore Rubro-Negra em Formato de Arvore");
	printf("\n0 - Sair\n> ");
	scanf("%d", &num);
	return num;
}

void menuRN() {
	system("cls");
	No* no = NULL;
	int valor, opcao = 1, BuscaValor = 0;
	int* vet = NULL;
	int num = 0, aux1;

	do {
		opcao = printMenu();
		switch (opcao) {
			case 1:
				//aqui estamos inserindo
				printf("Digite um valor para inserir na árvore (0 para sair): ");
				scanf("%d", &valor);

				while (valor != 0) {
					inserir(&no, valor);
					vet = realloc(vet, (num + 1) * sizeof(int));
					vet[num] = valor;
					num++;

					printf("Digite um valor para inserir na árvore (0 para sair): ");
					scanf("%d", &valor);
				}

				printf("\n");
				system("pause");
				system("cls");

				break;
			case 2:

				//aqui estamos imprimindo
				printf("\n[1] Arvore Rubro-Negra (in-order)");
				printf("\n[2] Arvore Rubro-Negra (pre-order)");
				printf("\n[3] Arvore Rubro-Negra (pos-order)");
				printf("\n[4] Arvore Rubro-Negra (in-order, pre-order, pos-order)\n> ");
				fflush(stdin);
				scanf("%d", &aux1);
				if(aux1 == 1) {
					printf("Arvore Rubro-Negra (visualizacao em arvore):\n");
					imprimeArvore(no, 0);
					printf("\n");
					InOrder(no);
				} else if(aux1 == 2) {
					printf("Arvore Rubro-Negra (visualizacao em arvore):\n");
					imprimeArvore(no, 0);
					printf("\n");
					PreOrder(no);
				} else if(aux1 == 3) {
					printf("Arvore Rubro-Negra (visualizacao em arvore):\n");
					imprimeArvore(no, 0);
					printf("\n");
					PosOrder(no);
				} else if(aux1 = 4) {
					printf("Arvore Rubro-Negra (visualizacao em arvore):\n");
					imprimeArvore(no, 0);
					printf("\n");
					printf("\nIn-order:\n");
					InOrder(no);
					printf("\nPre-order:\n");
					PreOrder(no);
					printf("\nPos-order:\n");
					PosOrder(no);
				} else {
					printf("\nOpcao invalida.");
				}

				printf("\n");
				system("pause");
				system("cls");

				break;
			case 3:

				//aqui estamos Buscandoo
				printf("Arvore Rubro-Negra (visualizacao em arvore):\n");
				imprimeArvore(no, 0);
				printf("\n");
				printf("Digite o valor a ser buscado: ");
				scanf("%d", &BuscaValor);
				No* result = Busca(no, BuscaValor);

				if (result != NULL) {
					printf("Valor %d encontrado na arvore.\n", BuscaValor);
				} else {
					printf("Valor %d nao encontrado na arvore.\n", BuscaValor);
				}

				printf("\n");
				system("pause");
				system("cls");

				break;
			case 4:

				//aqui estamos Removendo
				imprimeArvore(no, 0);
				int ValorExcluir;
				printf("Digite o valor a ser removido: ");
				scanf("%d", &ValorExcluir);
				excluirNo(&no, ValorExcluir);

				printf("\n");
				system("pause");
				system("cls");

				break;
			case 5:
				//aqui estamos Imprimindo em formato de arvore
				printf("Arvore Rubro-Negra (visualizacao em arvore):\n");
				imprimeArvore(no, 0);
				printf("\n");
				system("pause");
				system("cls");

				break;
			case 0:
				printf("Saindo...\n");
				break;
			default:
				printf("Opção inválida. Tente novamente.\n");
		}
		//getch();// pausa
		//system("cls");
	} while(opcao!=0);
}