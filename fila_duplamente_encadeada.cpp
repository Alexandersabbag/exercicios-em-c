
//-----------------------------------------------------------------------------------------------------------------------------------
//questão 5
#include<stdio.h>
#include<stdlib.h>

typedef struct dados
{
	int cod ;
	char nome[30] ;
	dados *prox ;
	dados *ant ;
};


int resp ;

dados *inicio = (dados *) malloc(sizeof(dados)) ;  //ponteiro inicio aponta para um endereço de struct sem valores(header)
dados *fim = inicio ;                              //ponteiro fim recebe inicio.
dados novo;
dados *aux ;

int main(int argc, char** argv)
{
	inicio -> ant = inicio -> prox = NULL;        //ant e prox da minha header apontando para nulo

	do
	{
		printf("\nMENU\n");
		printf("\n1 - Inserir");
		printf("\n2 - Listar");
		printf("\n3 - Sair\n");
		printf("OPCAO: ");
		scanf("%i", &resp);
		switch(resp)
		{
		case 1:
		{
			novo.cod = 0 ;
			novo.nome[0] = '\0';
			novo.ant = NULL ;
			novo.prox = NULL ;
			printf("\nInsira o código : ");
			scanf("%i" , &novo.cod);
			printf("\nInsira o nome");
			fflush(stdin);
			gets(novo.nome);
			//linkando as celulas com os apontadores
			fim -> prox = (dados *) malloc(sizeof(dados)) ;
			fim -> prox -> ant = fim ;
			fim = fim -> prox ;
			//inserindo na celula atual os valores que estao em novo.
			fim -> cod = novo.cod ;
			fim -> nome = novo.nome ;
			fim -> prox = NULL;
			break ;
		}
		case 2:
		{
			dados *aux = inicio -> prox;
			while(aux != NULL)
			{
				printf("Código: %i", aux -> cod) ;
				printf("Nome: %s", aux -> nome) ;

				aux = aux -> prox;
			}
		}
		}
	}
	while(resp != 3);
	return 0;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
//questão 6
#include<stdio.h>
#include<stdlib.h>

typedef struct dados
{
	int cod ;
	char nome[30] ;
	dados *prox ;
	dados *ant ;
};


int resp ;

dados *inicio = (dados *) malloc(sizeof(dados)) ;  //ponteiro inicio aponta para um endereço de struct sem valores(header)
dados *fim = inicio ;                              //ponteiro fim recebe inicio.
dados novo;
dados *aux ;

int main(int argc, char** argv)
{
	inicio -> ant = inicio -> prox = NULL;        //ant e prox da minha header apontando para nulo

	do
	{
		printf("\nMENU\n");
		printf("\n1 - Inserir");
		printf("\n2 - Listar");
		printf("\n3 - Sair\n");
		printf("OPCAO: ");
		scanf("%i", &resp);
		switch(resp)
		{
		case 1:
		{
			novo.cod = 0 ;
			novo.nome[0] = '\0';
			novo.ant = NULL ;
			novo.prox = NULL ;
			printf("\nInsira o código : ");
			scanf("%i" , &novo.cod);
			printf("\nInsira o nome");
			fflush(stdin);
			gets(novo.nome);
			//linkando as celulas com os apontadores
			fim -> prox = (dados *) malloc(sizeof(dados)) ;
			fim -> prox -> ant = fim ;
			fim = fim -> prox ;
			//inserindo na celula atual os valores que estao em novo.
			fim -> cod = novo.cod ;
			fim -> nome = novo.nome ;
			fim -> prox = NULL;
			fim -> prox = inicio ;  //linkando o fim no inicio 
			inicio -> ant = fim ;	//linkando o inicio fim.
			break ;
		}
		case 2:
		{
			dados *aux = inicio -> prox;
			while(aux != NULL)
			{
				printf("Código: %i", aux -> cod) ;
				printf("Nome: %s", aux -> nome) ;

				aux = aux -> prox;
			}
		}
		}
	}
	while(resp != 3);
	return 0;
}
