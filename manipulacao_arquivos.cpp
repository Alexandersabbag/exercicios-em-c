/*Busca Aleatória em arquivo
As informações são armazenadas sequencialmente nos arquivos , ou seja , uma 
informação após a outra , e a leitura tambem é sequencial , contudo , há 
a possibilidade de fazer uma busca aleatória no arquivo a partir da informação
de quantos bytes devem ser percorridos aleatoriamente até a posição desejada.
A função fseek() permite o deslocamento do ponteiro do arquivo para uma posição
desejada.

Sintaxe:
fseek(pont do arq , qte de bytes que será deslocado,posição inicial)

posição inicial
0 - inicio do arquivo
1 - posição corrente
2 - final do arquivo

declaração de uma variavel long int - geralmente dá-se o nome de offset 
long int offset;

declara uma var que terá o número de bytes a ser deslocado 
int registro;

offset = (registro - 1)* sizeof(struct);

exemplo: fseek(arquivo, offset, 0);
------------------------------------------------------------------------------------
*/
/*programa para ler o nome de um produto e permitir a consulta 
pelo código do produto. O código deve ser gerado automaticamente*/

//declaração das bibliotecas
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<ctype.h>

typedef struct 
{
	int codigo;
	char nomeprod[31];
}produto;

//protótipo das funções
void cadastrar();
void consultarcod();
int menu();
int sequencia();

//função principal
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

//função cadastrar
void cadastrar()
{
	FILE *parq;
	//declaração das variaveis
	produto produtos;
	char resp;
	
	//abertura do arquivo para gravação em modo binário
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

//função consultar
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