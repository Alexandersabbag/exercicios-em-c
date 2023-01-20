#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<conio.h>
#include<locale.h>

typedef struct no
{
	struct no *esq, *dir;
	int chave;
} TNo; //Tipo N�.


void inicializa(TNo **ptr)  //**ptr (declarado implicitamente) armazena o end. de mem�ria de *ptr
{
	*ptr = NULL;
}

//declarando as fun��es
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
	inicializa(&ptr); //passando o end de mem�ria de ptr

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
		printf("\nEscolha uma op��o: ");
		scanf("%i", &valor);
		switch(valor)
		{
			case 1:
			{
				printf("Insira um valor: ");
				scanf("%i", &numero);
				insere(&ptr, numero); //&ptr � para fazer altera��o na �rvore. N�mero manda somente a c�pia p/ inser��o.
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
				pesquisa(ptr, numero); //manda c�pias das variaveis e n�o altera-las.	
				break;
			}
			case 4:
				imprimir(ptr);
				break;
			/*
			Futuras Features
			*/
			default: printf("valor inserido inv�lido");
		}
		printf("\nDeseja sair do programa(S/N)?");
		resp = getche();
	}
	while(toupper(resp) != 'S');

	return 0;
}

void insere(TNo **ptr, int chave) //ptr come�a na raiz
{
	if(*ptr == NULL) //na 1a itera��o, ptr come�a como nulo (OLHAR FUN��O inicializa).Se poteiro for nulo, crio um novo nodo
	{
		(*ptr) = (TNo *) malloc(sizeof(TNo)); //cria o registro,
		(*ptr) -> esq = NULL; //com os ponteiro esq = nulo e
		(*ptr) -> dir = NULL; //ponteiro dir = nulo.
		(*ptr) -> chave = chave; //variavel recebe a chave inserida pelo user
	}
	else // sen�o, caso ponteiro n�o estiver apontando para nulo (apontando para um valor previamente inserido),
	{
		if(chave < (*ptr) -> chave) // se chave inserida atual for menor que a chave previamente inserida,
			insere(&(*ptr) -> esq, chave); //chamo essa fun��o denovo, por�m ponteiro atualizar� apontando a esquerda do n� pai.
		if(chave > (*ptr) -> chave) // se chave inserida atual for maior que a chave previamente inserida, 
			insere(&(*ptr) -> dir, chave); //chamo esse fun��o denovo, por�m ponteiro atualizar� apontando a direita do n� pai.
	}
	
	printf("Valor Inserido!");
	system("pause");
}

void remover(TNo **ptr, int chave){ //ptr come�a na raiz
	if((*ptr) == NULL) //se o valor em que ponteiro estar for NULO
		printf("A chave %i n�o est� na �rvore!" , chave); //�rvore n existe ou o valor inserido n�o encontrado.
	else if(chave < (*ptr)-> chave) //se a chave pedida for menor que a chave no qual ponteiro aponta na �rvore,
		remover(&(*ptr) -> esq, chave); //chama a fun��o denovo, por�m ponteiro atualizar� � esquerda do n� pai.
	else if(chave > (*ptr) -> chave) //sen�o se a chave pedida for maior que chave no qual ponteiro aponta na �rvore,
		remover(&(*ptr) -> dir, chave); //chama a fun��o denovo, por�m ponteiro atualizar� � direita do n� pai.
	else  // caso o valor pedido n�o for menor, nem maior a chave pedida, � igual, chave pedida = chave encontrada.
	{
		TNo *aux = *ptr; //aux recebe end de ptr
		if((*ptr) -> dir == NULL) //se dir de ptr for igual a nulo,
		{
			(*ptr) = (*ptr) -> esq; //ptr � atualizado � esquerda do n� pai
			free(aux); //exclui aux que recebeu ptr.
		}
		else if((*ptr) -> esq == NULL) //se esq de ptr for igual a nulo,
		{
			(*ptr) = (*ptr) -> dir; //ptr � atualizado � direita do n� pai
			free(aux); //exclui aux q recebeu ptr.
		}
		else // se esq ou dir n�o forem nulos, ser� preciso pegar o valor antecessor ou sucessor a raiz.
			antecessor((*ptr), &(*ptr) -> esq);	//ser� o valor mais pr�ximo a raiz, na sub arvore esq a raiz, o valor mais a direita da sub �rvore.
      // ou sucessor((*ptr), &(*ptr) -> dir);     ser� o valor mais pr�ximo a raiz, na sub arvore dir a raiz, o valor mais a esquerda da sub �rvore.
	}
}

void antecessor(TNo *q, TNo **r) //q seria o ptr que tem a celula c n�s filhos na dir e esq e r ser� o ptr q percorrer� at� achar o antecessor.
{ 
	if((*r) -> dir != NULL) // se dir de r n�o for nulo, 
		antecessor (q, &(*r) -> dir); //chamo essa fun��o denovo atualizando r a direita do n� pai,
	else // caso dir de r for nulo, achei o n� folha;
	{
		q -> chave = (*r) -> chave; //q recebe a chave de r,
		q = (*r); // q aponta p/ r,
		(*r) = (*r) -> esq; // r atualiza e aponta p/ esq da c�lula, 
		free(q); //exclui q.
	}
}


//LEMBRANDO QUE AS FUN��ES SUCESSOR E ANTECESSOR EST�O CORRETAS P/ SEREM USADAS NA HORA DA SUBSTITUI��O DO NODO
void sucessor(TNo *q, TNo **r) //q seria o ptr que tem a celula c n�s filhos na dir e esq e r ser� o ptr q percorrer� at� achar o sucessor.
{
	if((*r) -> esq != NULL) // se esq de r n�o for nulo, 
		sucessor(q, &(*r) -> esq); //chamo essa fun��o denovo atualizando r a esquerda do n� pai,
	else // caso dir de r for nulo, achei o n� folha;
	{
		q -> chave = (*r) -> chave; //q recebe a chave de r,
		q = (*r); // q aponta p/ r,
		(*r) = (*r) -> dir; // r atualiza e aponta p/ dir da c�lula, 
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
			printf("A chave %i est� na �rvore.", chave);
		else printf("A chave %i n�o est� na �rvore.", chave);
	}
	
}

void imprimir(TNo *ptr)
{
	if(ptr != NULL)
	{
		imprimir(ptr -> esq); //percorre toda a sub-�rvore a esquerda
		printf(" %i ", ptr -> chave);
		imprimir(ptr -> dir); //percorre toda a sub-�rvore a direita
	}
}


