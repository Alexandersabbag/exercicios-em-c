#include<stdlib.h>
#include<stdio.h>
#include<locale.h>

typedef struct no
{
	struct no *esq, *dir;
	int chave;
} TNo; //Tipo Nó.

struct hash
{
	TNo *indice;
};
hash h[8];

void inicializa(TNo **ptr);  //inicializando a árvore
void iniHash(); //atribui end. de memória para cada posição da tabela.
void inserirElemento(TNo **ptr, int chave); //inserção da chave
void imprimirArvore(TNo *ptr); //imprime uma posição da tabela hash
void pesquisaValor(TNo *ptr, int chave); //pesquisa uma chave específica

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Portuguese");
	#define max 34
	int i, vet[max], posicao, chave;

	void iniHash();

	//fazendo a inserção de chaves
	for(i = 0 ; i < max; i++ )
	{
		scanf("%i", &vet[i]);
	}

	//atribuindo a inserção diretamente
	for(i = 0 ; i < max; i++ )
	{
		posicao = vet[i] % 8;
		inserirElemento(&h[posicao].indice, vet[i]); //passando a posição do end de memória da tabela, junto com a chave
	}

	/* printf("digite a posição de leitura da tabela: ");
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
		inicializa(&h[i].indice); // passando o endereço de memória da tabela hash e inicializando as árvores

}

void inicializa(TNo **ptr)  //salva o end de memória de ptr
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
		printf("%i ", ptr -> chave);
		imprimirArvore(ptr -> dir); //percorre toda a sub-árvore a direita
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
			printf("A chave %i está na árvore.", chave);
		else printf("A chave %i não está na árvore.", chave);
	}
	
}