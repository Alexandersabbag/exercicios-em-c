/*Criar uma �rvore bin�ria num�rica a partir de um estrutura de
repeti��o(sem uso de recursividade) usando ponteiros e o conceito
de fila/pilha duplamente encadeada*/


//declara��o das bibliotecas
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<ctype.h>
#include<conio.h>

//declara��o da struct
typedef struct ball
{
	int number;
	ball *l;
	ball *r;
};

//declara��o da c�lula/valor inicial
ball *templ; //temporario esquerda da raiz 
ball *tempr; //temporario direita da raiz
ball *root;
ball *novo;

void insert();  //inser��o
void impress(); //imprimir

//fun��o principal
int main()
{
	//declara��o das vari�veis
	int value;
	char ans;
	//configura��o da lingua
	setlocale(LC_ALL, "Portuguese");

	do
	{
		system("cls");
		printf("\tMenu");
		printf("\n1 - Inserir um valor;");
		printf("\n2 - Imprimir;");
		printf("%i" , &value);

		switch(value)
		{
		case 1 :
			insert();
			break;
		case 2 :
			imprimir()
			break;
		default:
			printf("Valor Inv�lido.");
			break;
		}

		printf("deseja inserir outro valor ? (S/N): ";
			   ans = getche();
	}
		   while(toupper(ans) == 'S');

	printf("\nFechando a aplica��o...\n");
	system("pause");

	return 0;
}

void insert();
{
	int n; //number
	int i = 0; //controle da raiz
	char ans;

	do
	{
		system("cls");
		printf("Digite um n�mero inteiro: ");
		scanf("%i" , &n);
		if(i == 0)
		{
			novo = (ball*)malloc(sizeof(ball));
			novo -> number = n;
			novo -> l = NULL;
			novo -> r = NULL;
			root = novo;
			i++;
		}
		else
		{
			novo = (ball*)malloc(sizeof(ball));
			novo -> number = n;
			novo -> l = NULL;
			novo -> r = NULL;
			
			if(root -> l == NULL || root -> r == NULL)
			{
				if((root -> l == NULL) && (novo -> number < root -> number)){
					root -> l = novo;
					templ = novo;
				}	
				if(temp -> r == NULL && (novo -> number > root -> number)){
					root -> r = novo;
					tempr = novo;
				}		
			}else{
				
			}

		}




		printf("deseja inserir outro valor ? (S/N): ";
			   ans = getche();
	}while(toupper(ans) == 'S');
		   

}



