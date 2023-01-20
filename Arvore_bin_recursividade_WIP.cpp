#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<conio.h>
#include<locale.h>

typedef struct no
{
	struct no *esq, *dir;
	int chave;
} TNo; //Tipo Nó.


void inicializa(TNo **ptr)  //**ptr (declarado implicitamente) armazena o end. de memória de *ptr
{
	*ptr = NULL;
}

//declarando as funções
void insere(TNo **ptr, int chave);
void remover(TNo **ptr, int chave);
void antecessor(TNo *q, TNo **r);
//void sucessor(TNo *q, TNo **r);(OPCIONAL)
void pesquisa(TNo *ptr, int chave);
void imprimir(TNo *ptr);


int main()
{
	int valor, numero;
	char resp;
	
	setlocale(LC_ALL, "Portuguese");

	//declarando o ponteiro
	TNo *ptr;
	inicializa(&ptr); //passando o end de memória de ptr

	do
	{
		system("cls");
		printf("\tMENU");
		printf("\n1- Inserir");
		printf("\n2- Remover");
		printf("\n3- Pesquisar");
		printf("\n4 - Imprimir");
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
				insere(&ptr, numero); //&ptr é para fazer alteração na árvore. Número manda somente a cópia p/ inserção.
				break;
			}
			case 2:
			{
				printf("Insira o valor que deseja ser deletado: ");
				scanf("%i", &numero);
				remover(&ptr, numero);
				break;
			}
			case 3:
			{
				printf("Insira o valor que deseja ser pesquisado: ");
				scanf("%i", &numero);
				pesquisa(ptr, numero); //manda cópias das variaveis e não altera-las.	
				break;
			}
			case 4:
				imprimir(ptr);
				break;
			/*
			Futuras Features
			*/
			default: printf("valor inserido inválido");
		}
		printf("\nDeseja sair do programa(S/N)?");
		resp = getche();
	}
	while(toupper(resp) != 'S');

	return 0;
}

void insere(TNo **ptr, int chave) //ptr começa na raiz
{
	if(*ptr == NULL) //na 1a iteração, ptr começa como nulo (OLHAR FUNÇÃO inicializa).Se poteiro for nulo, crio um novo nodo
	{
		(*ptr) = (TNo *) malloc(sizeof(TNo)); //cria o registro,
		(*ptr) -> esq = NULL; //com os ponteiro esq = nulo e
		(*ptr) -> dir = NULL; //ponteiro dir = nulo.
		(*ptr) -> chave = chave; //variavel recebe a chave inserida pelo user
	}
	else // senão, caso ponteiro não estiver apontando para nulo (apontando para um valor previamente inserido),
	{
		if(chave < (*ptr) -> chave) // se chave inserida atual for menor que a chave previamente inserida,
			insere(&(*ptr) -> esq, chave); //chamo essa função denovo, porém ponteiro atualizará apontando a esquerda do nó pai.
		if(chave > (*ptr) -> chave) // se chave inserida atual for maior que a chave previamente inserida, 
			insere(&(*ptr) -> dir, chave); //chamo esse função denovo, porém ponteiro atualizará apontando a direita do nó pai.
	}
	
	printf("Valor Inserido!");
	system("pause");
}

void remover(TNo **ptr, int chave){ //ptr começa na raiz
	if((*ptr) == NULL) //se o valor em que ponteiro estar for NULO
		printf("A chave %i não está na árvore!" , chave); //árvore n existe ou o valor inserido não encontrado.
	else if(chave < (*ptr)-> chave) //se a chave pedida for menor que a chave no qual ponteiro aponta na árvore,
		remover(&(*ptr) -> esq, chave); //chama a função denovo, porém ponteiro atualizará à esquerda do nó pai.
	else if(chave > (*ptr) -> chave) //senão se a chave pedida for maior que chave no qual ponteiro aponta na árvore,
		remover(&(*ptr) -> dir, chave); //chama a função denovo, porém ponteiro atualizará à direita do nó pai.
	else  // caso o valor pedido não for menor, nem maior a chave pedida, é igual, chave pedida = chave encontrada.
	{
		TNo *aux = *ptr; //aux recebe end de ptr
		if((*ptr) -> dir == NULL) //se dir de ptr for igual a nulo,
		{
			(*ptr) = (*ptr) -> esq; //ptr é atualizado à esquerda do nó pai
			free(aux); //exclui aux que recebeu ptr.
		}
		else if((*ptr) -> esq == NULL) //se esq de ptr for igual a nulo,
		{
			(*ptr) = (*ptr) -> dir; //ptr é atualizado à direita do nó pai
			free(aux); //exclui aux q recebeu ptr.
		}
		else // se esq ou dir não forem nulos, será preciso pegar o valor antecessor ou sucessor a raiz.
			antecessor((*ptr), &(*ptr) -> esq);	//será o valor mais próximo a raiz, na sub arvore esq a raiz, o valor mais a direita da sub árvore.
      // ou sucessor((*ptr), &(*ptr) -> dir);     será o valor mais próximo a raiz, na sub arvore dir a raiz, o valor mais a esquerda da sub árvore.
	}
}

void antecessor(TNo *q, TNo **r) //q seria o ptr que tem a celula c nós filhos na dir e esq e r será o ptr q percorrerá até achar o antecessor.
{ 
	if((*r) -> dir != NULL) // se dir de r não for nulo, 
		antecessor (q, &(*r) -> dir); //chamo essa função denovo atualizando r a direita do nó pai,
	else // caso dir de r for nulo, achei o nó folha;
	{
		q -> chave = (*r) -> chave; //q recebe a chave de r,
		q = (*r); // q aponta p/ r,
		(*r) = (*r) -> esq; // r atualiza e aponta p/ esq da célula, 
		free(q); //exclui q.
	}
}


//LEMBRANDO QUE AS FUNÇÕES SUCESSOR E ANTECESSOR ESTÃO CORRETAS P/ SEREM USADAS NA HORA DA SUBSTITUIÇÃO DO NODO
void sucessor(TNo *q, TNo **r) //q seria o ptr que tem a celula c nós filhos na dir e esq e r será o ptr q percorrerá até achar o sucessor.
{
	if((*r) -> esq != NULL) // se esq de r não for nulo, 
		sucessor(q, &(*r) -> esq); //chamo essa função denovo atualizando r a esquerda do nó pai,
	else // caso dir de r for nulo, achei o nó folha;
	{
		q -> chave = (*r) -> chave; //q recebe a chave de r,
		q = (*r); // q aponta p/ r,
		(*r) = (*r) -> dir; // r atualiza e aponta p/ dir da célula, 
		free(q); //exclui q.
    }	
}

void pesquisa(TNo *ptr, int chave)
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

void imprimir(TNo *ptr)
{
	if(ptr != NULL)
	{
		imprimir(ptr -> esq); //percorre toda a sub-árvore a esquerda
		printf(" %i ", ptr -> chave);
		imprimir(ptr -> dir); //percorre toda a sub-árvore a direita
	}
}


