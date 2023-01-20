/*Busca Aleat�ria em arquivo
As informa��es s�o armazenadas sequencialmente nos arquivos , ou seja , uma 
informa��o ap�s a outra , e a leitura tambem � sequencial , contudo , h� 
a possibilidade de fazer uma busca aleat�ria no arquivo a partir da informa��o
de quantos bytes devem ser percorridos aleatoriamente at� a posi��o desejada.
A fun��o fseek() permite o deslocamento do ponteiro do arquivo para uma posi��o
desejada.

Sintaxe:
fseek(pont do arq , qte de bytes que ser� deslocado,posi��o inicial)

posi��o inicial
0 - inicio do arquivo
1 - posi��o corrente
2 - final do arquivo

declara��o de uma variavel long int - geralmente d�-se o nome de offset 
long int offset;

declara uma var que ter� o n�mero de bytes a ser deslocado 
int registro;

offset = (registro - 1)* sizeof(struct);

exemplo: fseek(arquivo, offset, 0);
------------------------------------------------------------------------------------
*/
/*programa para ler o nome de um produto e permitir a consulta 
pelo c�digo do produto. O c�digo deve ser gerado automaticamente*/

//declara��o das bibliotecas
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<ctype.h>

typedef struct 
{
	int codigo;
	char nomeprod[31];
}produto;

//prot�tipo das fun��es
void cadastrar();
void consultarcod();
int menu();
int sequencia();

//fun��o principal
int main(int argc, char** argv)
{
	int resp;
	
	do
	{
		   resp = menu();
		   switch(resp)
		   {
		   	case 1: 
		   		cadastrar();
		   		break;
		   	case 2: 
		   		consultarcod();
		   		break;
		   	case 0: exit(0);

			default:
			{
				printf("\nOpcao invalida\n");
				system("pause");
			}	   
		   }	
	}while(resp != 0);
	return 0;
}

int menu()
{
	int opc;
	
	system("cls");
	printf("1 - cadastrar\n2 - consultar\n0 - Sair\nescolha uma das opc: ");
	scanf("%i", &opc);
	
	return opc;
}

int sequencia()
{
	FILE *arq;
	int seq = 1;
	
	if((arq = fopen("sequencia.txt" , "r")) == NULL)
	{
		arq = fopen("sequencia.txt" , "w");
		fprintf(arq, "%i", seq);
	}
	else
	{
		while((fscanf(arq, "%i", &seq))!= EOF)
		seq++;
		fclose(arq);
		arq = fopen("sequencia.txt" , "w");
		fprintf(arq, "%i", seq);	
	}

	fclose(arq);
	
	return seq;
}

//fun��o cadastrar
void cadastrar()
{
	FILE *parq;
	//declara��o das variaveis
	produto produtos;
	char resp;
	
	//abertura do arquivo para grava��o em modo bin�rio
	parq = fopen("bdprod.txt" , "ab");
	
	do
	{
		printf("Codigo do produto: %i\n", produtos.codigo = sequencia());
		printf("Informe o nome do produto: ");
		fflush(stdin);
		scanf("%30[^\n]", produtos.nomeprod);
	
		//gravar em arquivo 
		fwrite(&produtos, sizeof(produtos),1, parq);
		printf("Outro <S/N>: ");
		resp = getche();
		system("cls");
		
	}while(toupper(resp)=='S');
	
	fclose(parq);
}

//fun��o consultar
void consultarcod()
{
	FILE *arq;
	
	long int offset;
	int numreg;
	char resp;
	
	produto produtos ;
	
	if((arq = fopen("bdprod.txt", "rb")) == NULL)
	{
		printf("\nNao ha produtos cadastrados.\n");
	}
	else
	{
		do
		{
			system("cls");
			printf("Informe o codigo do produto");
			scanf("%i" , &numreg);
			
			//calcular o deslocamento
			offset = (numreg - 1)*sizeof(produtos);
			
			//efetuar deslocamento
			if(fseek(arq, offset, 0) != 0)
			{
				printf("\nNao eh possivel mover o ponteiro.\n");
			}
			else
			{
				fread(&produtos, sizeof(produtos), 1, arq);	
				printf("\nCodigo: %i", produtos.codigo);
				printf("\nNome: %s\n", produtos.nomeprod);
				system("pause");
			}
			
			printf("\nOutra consulta ? <S/N>: ");
			resp = getche();
		
		}while(toupper(resp) == 'S');
		fclose(arq);
	}
}