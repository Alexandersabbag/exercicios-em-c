//Alexandre Monteiro Sabbag de Souza, c�digo: 767518
//bibliotecas
#include<stdlib.h>
#include<stdio.h>
#include<locale.h>
#include<string.h>

//structs
typedef struct no
{
	struct no *esq, *dir;
	int chave;
	char nome[99], rg[99], plano[99], cpf[99];
} TNo; //Tipo N�.

struct hash
{
	TNo *indice;
};
hash h[8];

//prot�tipos de fun��es
void inicializa(TNo **ptr);  //inicializando a �rvore
void iniHash(); //atribui end. de mem�ria para cada posi��o da tabela.
void inserirElemento(TNo **ptr, int chave); //inser��o das informa��es
void imprimirArvore(TNo *ptr); //imprime uma posi��o da tabela hash
void imprimirPesquisa(TNo *ptr, int chave); //pesquisa uma chave espec�fica

//ponteiro
TNo info ; //receber� todas as informa��es da �rvore

//main
int main(int argc, char** argv)
{
	//declara��o das variaveis
	int opc, valorID;

	setlocale(LC_ALL, "Portuguese");
	iniHash();

	do
	{
		//Menu
		system("cls");
		printf("\n\tMenu\n");
		printf("Escolha uma das op��es abaixo:");
		printf("\n1 - Inserir um novo paciente na lista;");
		printf("\n2 - Imprimir uma das listas de pacientes;") ;
		printf("\n3 - Procurar um Paciente;");
		printf("\n4 - Sair.") ;
		printf("\nOp��o : ") ;
		scanf("%i" , &opc) ;

		if(opc < 1 || opc > 4)
		{
			printf("\nOp��o inv�lida.\n") ;
			system ("pause");
		}
		switch(opc)
		{
		case 1:
			printf("Digite o novo ID do paciente: ");
			scanf("%i", &valorID);
			inserirElemento(&h[valorID % 8].indice, valorID); //passando o local do indice e o valor do id.
			break;
		case 2:
			printf("digite a posi��o de leitura da tabela: ");
			scanf("%i" , &posicao);
			imprimirArvore(h[posicao].indice);
			break;
		case 3:
			printf("Digite o id do paciente a ser pesquisado: ");
		   	scanf("%i", &valorID);
			imprimirPesquisa(h[valorID % 8].indice, valorID);
			break;
		}
	}
	while(opc != 4);

	return 0;
}

//fun��es
void iniHash()
{
	for(int i = 0 ; i < 8 ; i++)
		inicializa(&h[i].indice); // passando o endere�o de mem�ria da tabela hash e inicializando as �rvores

}

void inicializa(TNo **ptr)  //salva o end de mem�ria de ptr
{
	*ptr = NULL;
}

void inserirElemento(TNo **ptr, int chave) //end. indice e valor da chave
{

	if(*ptr == NULL)
	{
		(*ptr) = (TNo *) malloc(sizeof(TNo)); //cria o registro,
		(*ptr) -> esq = NULL; //com os ponteiro esq = nulo e
		(*ptr) -> dir = NULL; //ponteiro dir = nulo.

		//pegando os dados
		printf("Nome Completo: ");
		fflush(stdin);
		gets(info.nome);
		printf("RG: ");
		fflush(stdin);
		gets(info.rg);
		printf("Cpf: ");
		fflush(stdin);
		gets(info.cpf);
		printf("Plano de Sa�de: ");
		fflush(stdin);
		gets(info.plano);
		
		//passando os dados para o novo elemento
		(*ptr) -> chave = chave; 
		strcpy((*ptr) -> nome, info.nome);
		strcpy((*ptr) -> rg, info.rg);
		strcpy((*ptr) -> cpf, info.cpf);
		strcpy((*ptr) -> plano, info.plano);
	}
	else // sen�o, caso ponteiro n�o estiver apontando para nulo (apontando para um valor previamente inserido),
	{
		if(chave < (*ptr) -> chave) // se chave inserida atual for menor que a chave previamente inserida,
			inserirElemento(&(*ptr) -> esq, chave); //chamo essa fun��o denovo, por�m ponteiro atualizar� apontando a esquerda do n� pai.
		if(chave > (*ptr) -> chave) // se chave inserida atual for maior que a chave previamente inserida,
			inserirElemento(&(*ptr) -> dir, chave); //chamo esse fun��o denovo, por�m ponteiro atualizar� apontando a direita do n� pai.
	}

}

void imprimirArvore(TNo *ptr)
{
	if(ptr != NULL)
	{
		imprimirArvore(ptr -> esq); //percorre toda a sub-�rvore a esquerda
		printf("-----------------------------------------------------\n");	
		printf("id: %i\n", ptr -> chave);
		printf("Nome: %s\n", ptr -> nome);
		printf("RG: %s\n", ptr -> rg);
		printf("CPF: %s\n", ptr -> cpf);
		printf("Plano de sa�de: %s\n", ptr -> plano);
		printf("-----------------------------------------------------\n");
		imprimirArvore(ptr -> dir); //percorre toda a sub-�rvore a direita
		system("pause");
	}
	
}

void imprimirPesquisa(TNo *ptr, int chave)
{
	while((ptr != NULL) && (ptr -> chave != chave))
	{
		if(chave > ptr -> chave)
			ptr = ptr -> dir;
		else if(chave < ptr -> chave)
			ptr = ptr -> esq;
		if(ptr != NULL)
		{
			printf("id: %i\n", ptr -> chave);
			printf("Nome: %s\n", ptr -> nome);
			printf("RG: %s\n", ptr -> rg);
			printf("CPF: %s\n", ptr -> cpf);
			printf("Plano de sa�de: %s\n", ptr -> plano);
			system("pause");
		}	
		else
		{
			printf("Paciente n�o encontrado.\n");
			system("pause");
		} 	
	}
}