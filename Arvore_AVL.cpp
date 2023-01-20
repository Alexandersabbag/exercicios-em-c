#include<stdlib.h>
#include<stdio.h>

typedef struct no{
	struct no *esq, *dir;
	int chave;
}TNo;

void inicializa(TNo **ptr){
	*ptr = null;
}

int main()
{
	int valor, numero;
	char resp;
	
	setlocale(LC_ALL, "Portuguese");

	//declarando o ponteiro
	TNo *ptr;
	inicializa(&ptr);

	do
	{
		system("cls");
		printf("\tMENU");
		printf("\n1- inserir");
		/*
		Futuras Features
		*/
		printf("\nEscolha uma opção: ");
		scanf("%i", &valor);
		switch(valor)
		{
			case 1:
			{
				printf("Insira um valor: ");
				scanf("%i", &numero);
				insere(&ptr, numero);
			}
			/*
			futuras features
			*/
			break;
			default: printf("valor inserido inválido");
		}
		printf("\nDeseja sair do programa(S/N)?");
		resp = getche();
	}
	while(toupper(resp) != 'S');

	return 0;
}

void insere(TNo **ptr, int chave)
{
	if(*ptr == NULL)
	{
		(*ptr) = (TNo *) malloc(sizeof(TNo));
		(*ptr) -> esq = NULL;
		(*ptr) -> dir = NULL;
		(*ptr) -> chave = chave;
	}
	else
	{
		if(chave < (*ptr) -> chave)
			insere(&(*ptr) -> esq, chave);
		if(chave > (*ptr) -> chave)
			insere(&(*ptr) -> dir, chave);
	}
}
