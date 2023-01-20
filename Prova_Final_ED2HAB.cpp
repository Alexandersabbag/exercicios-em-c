//Alexandre Monteiro Sabbag de Souza, código: 767518
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
} TNo; //Tipo Nó.

struct hash
{
	TNo *indice;
};
hash h[8];

//protótipos de funções
void inicializa(TNo **ptr);  //inicializando a árvore
void iniHash(); //atribui end. de memória para cada posição da tabela.
void inserirElemento(TNo **ptr, int chave); //inserção das informações
void imprimirArvore(TNo *ptr); //imprime uma posição da tabela hash
void imprimirPesquisa(TNo *ptr, int chave); //pesquisa uma chave específica

//ponteiro
TNo info ; //receberá todas as informações da árvore

//main
int main(int argc, char** argv)
{
	//declaração das variaveis
	int opc, valorID;

	setlocale(LC_ALL, "Portuguese");
	iniHash();

	do
	{
		//Menu
		system("cls");
		printf("\n\tMenu\n");
		printf("Escolha uma das opções abaixo:");
		printf("\n1 - Inserir um novo paciente na lista;");
		printf("\n2 - Imprimir uma das listas de pacientes;") ;
		printf("\n3 - Procurar um Paciente;");
		printf("\n4 - Sair.") ;
		printf("\nOpção : ") ;
		scanf("%i" , &opc) ;

		if(opc < 1 || opc > 4)
		{
			printf("\nOpção inválida.\n") ;
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
			printf("digite a posição de leitura da tabela: ");
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

//funções
void iniHash()
{
	for(int i = 0 ; i < 8 ; i++)
		inicializa(&h[i].indice); // passando o endereço de memória da tabela hash e inicializando as árvores

}

void inicializa(TNo **ptr)  //salva o end de memória de ptr
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
		printf("Plano de Saúde: ");
		fflush(stdin);
		gets(info.plano);
		
		//passando os dados para o novo elemento
		(*ptr) -> chave = chave; 
		strcpy((*ptr) -> nome, info.nome);
		strcpy((*ptr) -> rg, info.rg);
		strcpy((*ptr) -> cpf, info.cpf);
		strcpy((*ptr) -> plano, info.plano);
	}
	else // senão, caso ponteiro não estiver apontando para nulo (apontando para um valor previamente inserido),
	{
		if(chave < (*ptr) -> chave) // se chave inserida atual for menor que a chave previamente inserida,
			inserirElemento(&(*ptr) -> esq, chave); //chamo essa função denovo, porém ponteiro atualizará apontando a esquerda do nó pai.
		if(chave > (*ptr) -> chave) // se chave inserida atual for maior que a chave previamente inserida,
			inserirElemento(&(*ptr) -> dir, chave); //chamo esse função denovo, porém ponteiro atualizará apontando a direita do nó pai.
	}

}

void imprimirArvore(TNo *ptr)
{
	if(ptr != NULL)
	{
		imprimirArvore(ptr -> esq); //percorre toda a sub-árvore a esquerda
		printf("-----------------------------------------------------\n");	
		printf("id: %i\n", ptr -> chave);
		printf("Nome: %s\n", ptr -> nome);
		printf("RG: %s\n", ptr -> rg);
		printf("CPF: %s\n", ptr -> cpf);
		printf("Plano de saúde: %s\n", ptr -> plano);
		printf("-----------------------------------------------------\n");
		imprimirArvore(ptr -> dir); //percorre toda a sub-árvore a direita
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
			printf("Plano de saúde: %s\n", ptr -> plano);
			system("pause");
		}	
		else
		{
			printf("Paciente não encontrado.\n");
			system("pause");
		} 	
	}
}