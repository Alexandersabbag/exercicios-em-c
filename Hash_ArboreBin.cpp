#include<stdlib.h>
#include<stdio.h>
#include<locale.h>

typedef struct no
{
	struct no *esq, *dir;
	int chave;
} TNo; //Tipo N�.

struct hash
{
	TNo *indice;
};
hash h[8];

void inicializa(TNo **ptr);  //inicializando a �rvore
void iniHash(); //atribui end. de mem�ria para cada posi��o da tabela.
void inserirElemento(TNo **ptr, int chave); //inser��o da chave
void imprimirArvore(TNo *ptr); //imprime uma posi��o da tabela hash
void pesquisaValor(TNo *ptr, int chave); //pesquisa uma chave espec�fica

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Portuguese");
	#define max 34
	int i, vet[max], posicao, chave;

	void iniHash();

	//fazendo a inser��o de chaves
	for(i = 0 ; i < max; i++ )
	{
		scanf("%i", &vet[i]);
	}

	//atribuindo a inser��o diretamente
	for(i = 0 ; i < max; i++ )
	{
		posicao = vet[i] % 8;
		inserirElemento(&h[posicao].indice, vet[i]); //passando a posi��o do end de mem�ria da tabela, junto com a chave
	}

	/* printf("digite a posi��o de leitura da tabela: ");
	scanf("%i" , &posicao);
	imprimirArvore(h[posicao].indice); */
	
	printf("Digite a chave a ser pesquisada: ");
	scanf("%i", &chave);
	posicao = chave % 8;
	pesquisaValor(h[posicao].indice, chave);
	return 0;
}

void iniHash()
{
	for(int i = 0 ; i < 8 ; i++)
		inicializa(&h[i].indice); // passando o endere�o de mem�ria da tabela hash e inicializando as �rvores

}

void inicializa(TNo **ptr)  //salva o end de mem�ria de ptr
{
	*ptr = NULL;
}

void inserirElemento(TNo **ptr, int chave)
{

	if(*ptr == NULL)
	{
		(*ptr) = (TNo *) malloc(sizeof(TNo)); //cria o registro,
		(*ptr) -> esq = NULL; //com os ponteiro esq = nulo e
		(*ptr) -> dir = NULL; //ponteiro dir = nulo.
		(*ptr) -> chave = chave; //variavel recebe a chave inserida pelo user
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
		printf("%i ", ptr -> chave);
		imprimirArvore(ptr -> dir); //percorre toda a sub-�rvore a direita
	}
}

void pesquisaValor(TNo *ptr, int chave)
{
	while((ptr != NULL) && (ptr -> chave != chave))
	{
		if(chave > ptr -> chave)
			ptr = ptr -> dir;
		else if(chave < ptr -> chave)
			ptr = ptr -> esq;
		if(ptr != NULL)
			printf("A chave %i est� na �rvore.", chave);
		else printf("A chave %i n�o est� na �rvore.", chave);
	}
	
}