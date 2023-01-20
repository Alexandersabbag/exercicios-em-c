#include<stdlib.h>
#include<stdio.h>
#include<locale.h>

typedef struct dados {
	int numero;
	dados *prox;
	dados *ant;
};

dados *fim;
dados *ref;
dados *aux;
dados *inicio = (dados *)malloc(sizeof (dados));

void bubble_sort() ;

int main(int argc, char** argv)
{
	int num , opc ;
	
	inicio = fim ;
	inicio -> ant = NULL ;
	inicio -> prox = NULL ;
	
	do
	{
		fim -> prox = (dados *)malloc(sizeof(dados)) ;
		fim -> prox -> ant = fim;
		fim -> prox -> prox = NULL ;
		fim = fim -> prox  ;

		printf("\nDigite um número inteiro: ");
		scanf("%i" , &num) ;
		fim -> numero = num ;
		printf("\nDigite 0 (zero) para sair da inserção e mostrar os valores ordenados: ");
		scanf("%i" , &opc);
	}
	while(opc != 0);
	
	bubble_sort() ;

	return 0;
}


