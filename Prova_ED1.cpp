/*Armazenar em ordem de favoritos(preferencial) os jogos de uma biblioteca de jogos.
Em uma biblioteca de n jogos(inserido pelo user) de uma plataforma digital, o usuário pode definir quais 
jogos são os de sua preferencia e portanto  organizar por prioridade em uma fila.*/
//declaração das bibliotecas.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <conio.h>

//criando a struct base.
typedef struct dados     //struct que armazenará as informações inseridas pelo jogador.
{
	int cod , rank ;     //código do jogo e ranking(prioridade).
	char nome[99] ;      //nome do jogo.
	dados *prox ;        //proximo do struct.
	dados *ant;          //anterior do struct.
};

//declarando os ponteiros.
dados *aux ;                                       //ponteiro auxiliar.
dados *auxant ;                                    //ponteiro aux anterior (usado para função destruir uma célula)
dados *auxprox ;                                   //ponteiro aux posterior (usado para função destruir uma célula)
dados *fim ;                                       //ponteiro da ultima célula da fila

//declarando a struct que armazenará somente os valores inseridos pelo usuário
dados novo ;

//criando os headers.
dados *inicio = (dados *)malloc(sizeof(dados)) ;   //struct header (célula fixa no inicio da fila)
dados *inimed = (dados *)malloc(sizeof(dados)) ;   //struct header (célula fixa no inicio das células meio da fila)
dados *inifim = (dados *)malloc(sizeof(dados)) ;   //struct header (célula fixa no inicio das células fim da fila)

//declaração das funções
void inserir() ;     //função para adicionar um  novo elemento.
void remover() ;     //função para remover um elemento.
void imprimir() ;    //função para imprimir um elemento.
void ajuda() ;       //função ajuda.

//declaração das variáveis globais.
int opc , i  ;       //opção e contador.

//função principal
int main()
{

	setlocale(LC_ALL, "Portuguese");

	//fazendo os apontamentos iniciais das headers.
	fim = inicio ;
	fim -> ant = NULL ;
	fim -> prox = inimed ;
	fim -> prox -> ant = inicio ;
	fim = inimed ;
	fim -> prox = inifim ;
	fim -> prox -> ant = inimed ;
	fim = inifim ;
	fim -> prox = NULL ;

	do
	{
		//Menu
		system("cls");
		printf("\n\tMenu\n");
		printf("Escolha uma das opções abaixo:");
		printf("\n1 - Inserir");
		printf("\n2 - Remover") ;
		printf("\n3 - Imprimir") ;
		printf("\n4 - Ajuda") ;
		printf("\n5 - Sair") ;
		printf("\nOpção : ") ;
		scanf("%i" , &opc) ;
		if(opc < 1 || opc > 5)
		{
			printf("\nOpção inválida.\n") ;
			system ("pause") ;
		}
		switch(opc)
		{
			case 1:
				inserir();
				break;
			case 2:
				remover();
				break;
			case 3:
				imprimir();
				break;
			case 4:
				ajuda() ;
				break;
		}

	}
	while(opc != 5) ;
	return 0;
}

void inserir() //O usuário informará o código , nome e ranking do jogo respectivamente.
{
	//A STRUCT NOVO SERVE APENAS PARA INSERIR OS DADOS QUE O USUÁRIO PASSARÁ.
	//inserindo as informações na struct novo.
	printf("\nInsira o código do jogo: ");
	scanf("%i" , &novo.cod) ;
	printf("\nDigite o nome do jogo: ");
	fflush(stdin);
	gets(novo.nome);
	do
	{
		printf("\nRank do Jogo (1 - Favorito , 2 - Intermediario , 3 - Não sabe)");
		printf("\nRank = ") ;
		scanf("%i" , &novo.rank);
		if(novo.rank < 1 || novo.rank > 3)
			printf("\nValor Incorreto!");
	}
	while(novo.rank < 1 || novo.rank > 3);
	//ant e prox são tratados como ponteiros e não como variaveis, portanto são irrelevantes nessa célula.
	novo.ant = NULL ;
	novo.prox = NULL ;

	//A partir do Ranking que será feito a inserção na fila por prioridade
	if(novo.rank == 1)
	{
		//Percorre todo o inicio de favorito (header) até chegar no mais recente
		aux = inicio ;
		while(aux -> prox != inimed)
			aux = aux -> prox;

		//Faz os apontamentos necessários para inserção
		aux -> prox = NULL ;
		inimed -> ant =  NULL ;
		aux -> prox = (dados *)malloc(sizeof(dados)) ;
		aux -> prox -> ant = aux ;
		aux = aux -> prox ;
		aux -> prox = inimed ;
		inimed -> ant = aux ;

		//Copiando os dados da struct novo
		aux -> cod = novo.cod ;
		strcpy(aux -> nome , novo.nome) ;
		aux -> rank = novo.rank ;

		printf("\nDados Salvos!\n");
		system ("pause") ;
		system ("cls") ;
	}
	else if(novo.rank == 2)
	{
		//Percorre todo o inicio de intermediario(header) até chegar no mais recente
		aux = inimed ;
		while(aux -> prox != inifim)
			aux = aux -> prox ;

		//Faz os apontamentos necessários para inserção
		aux -> prox = NULL ;
		inifim -> ant = NULL ;
		aux -> prox = (dados *)malloc(sizeof(dados)) ;
		aux -> prox -> ant = aux ;
		aux = aux -> prox ;
		aux -> prox = inifim ;
		inifim -> ant = aux ;

		//Copiando os dados da struct novo
		aux -> cod = novo.cod ;
		strcpy(aux -> nome , novo.nome) ;
		aux -> rank = novo.rank ;

		printf("\nDados Salvos!\n");
		system ("pause") ;
		system ("cls") ;
	}
	else
	{
		//Percorre todo o inicio de fim(header) até chegar no mais recente
		aux = inifim ;
		while (aux != fim )
			aux = aux -> prox ;

		//Faz os apontamentos necessários para inserção
		aux -> prox = (dados *)malloc(sizeof(dados)) ;
		aux -> prox -> ant = aux ;
		aux = aux -> prox ;
		fim = aux ;
		fim -> prox = NULL ;

		//Copiando os dados da struct novo
		aux -> cod = novo.cod ;
		strcpy(aux -> nome , novo.nome) ;
		aux -> rank = novo.rank ;

		printf("\nDados Salvos!\n");
		system ("pause") ;
		system ("cls") ;
	}
}

void remover() //Função que percorrerá toda a lista até achar o código do jogo para sua remoção
{
	int codigo ;                                       //variável local de comparação entre o código desejado e o que será procurado.
	printf("\nDigite o código do jogo a ser removido: ");
	scanf("%i" , &codigo);

	//percorro as células até chegar no valor desejado.
	aux = inicio ;                                     //aux que percorrerá a célula a partir do header inicio
	while (aux -> cod != codigo || aux -> cod == NULL) //percorrendo a lista inteira
		aux = aux -> prox ;

	if(aux -> cod == NULL)                             //caso percorra a lista inteira e não ache o código do jogo
	{
		printf("\nNenhum jogo inserido ou achado\n");
		system("pause") ;
		system("cls") ;
	}
	else if(aux == fim)                                //caso a célula desejada a ser removida esteja no final da lista.
	{
		//é feito os apontamentos para a célula anterior somente.
		auxant = aux ;
		auxant = aux -> ant ;
		fim = auxant ;
		fim -> prox = NULL ;

		//destroi a última célula
		free(aux) ;

		printf("\nJogo encontrado e excluído!\n") ;
		system("pause") ;
		system("cls") ;
	}
	else                                               //caso o valor esteja entre o inicio e fim (até a penultima célula)
	{
		//apontando as auxiliares para a célula anterior e posterior para não perder a referência
		auxant = aux ;
		auxant = aux -> ant ;
		auxprox = aux ;
		auxprox = aux -> prox ;

		//desconectando a célula que será removida
		auxant -> prox = NULL ;
		auxprox -> ant = NULL ;
		aux -> ant = NULL ;
		aux -> prox = NULL ;

		//destrói a célula
		free(aux) ;

		//aponto as células referênciadas
		auxant -> prox = auxprox ;
		auxprox -> ant = auxant ;

		printf("\nJogo encontrado e excluído!\n") ;
		system("pause") ;
		system("cls") ;
	}
}

void imprimir() //Exibirá somente a parte da lista de jogos inseridos.(A partir do ranking de prioridade)
{
	int numrank ;             //numero do rank.
	printf("\nDigite o ranking da lista a ser exibida: ");
	scanf("%i" , &numrank);

	
	if(numrank == 1)          //caso o rank seja 1 imprimir toda a lista de rank 1(Prioritário)
	{
		if (inicio -> prox == inimed) //caso a lista esteja vazia entre os headers
		{
			printf("\nJogo(s) não inserido(s) rank 1\n") ;
		}
		else              //caso a lista não esteja vazia entre os headers
		{
			printf("\n\tFavorito(s)\n");
			printf("----------------------------------------------------------") ;
			aux = inicio ;                //aux que percorrerá a lista a partir do header
			while(aux != inimed)          //percorrendo a lista
			{
				//exibindo os jogos da lista
				if(aux != inicio)
				{
					printf("\nCódigo : %i" , aux -> cod);
					printf("\nNome do Jogo : %s" , aux -> nome);
					printf("\n----------------------------------------------------------") ;
				}
				aux = aux -> prox ;
			}
		}
	}
	else if(numrank == 2)     //caso o rank seja 2 imprimir toda a lista de rank 2(Não tão prioritário)
	{
		if (inimed -> prox == inifim) //caso a lista esteja vazia entre os headers
		{
			printf("\nJogo(s) não inserido(s) no rank 2\n") ;
		}
		else                          //caso a lista não esteja vazia entre os headers
		{
			printf("\n\tIntermediario(s)\n");
			printf("\----------------------------------------------------------") ;
			aux = inimed ;               //aux percorrerá a lista a partir do header
			while(aux != inifim) //percorrendo a lista
			{
				//exibindo os jogos da lista
				if(aux != inimed)
				{
					printf("\nCódigo : %i" , aux -> cod);
					printf("\nNome do Jogo : %s" , aux -> nome);
					printf("\n----------------------------------------------------------") ;
				}
				aux = aux -> prox ;
			}
		}
	}
	else if(numrank == 3)                //caso o rank seja 3 imprimir toda a lista do rank 3(Não prioritários)
	{
		if (inifim -> prox == NULL) //caso a lista esteja vazia e o ponteiro apontando para o header
		{
			printf("\nJogo(s) não inserido(s) no rank 3") ;
		}
		else               //caso a lista não esteja vazia entre o header e o ponteiro fim
		{
			printf("\n\tNão sabe\n");
			printf("----------------------------------------------------------") ;
			aux = inifim ;             //aux  percorrerá a lista a partir do header
			while(aux != NULL) //percorrendo a lista
			{
				//exibindo os jogos da lista
				if(aux != inifim)
				{
					printf("\nCódigo : %i" , aux -> cod);
					printf("\nNome do Jogo : %s" , aux -> nome);
					printf("\n----------------------------------------------------------") ;
				}
				aux = aux -> prox ;
			}
		}
	}
	printf("\n") ;
	system("pause");
	system("cls") ;
}

void ajuda()
{
	int opc1 ;
	do
	{
		system("cls") ;
		printf ("\tBem Vindo ao Menu de Ajuda");
		printf ("\nEscolha uma das opções abaixo:");
		printf ("\n1 - Como funciona o programa ?");
		printf ("\n2 - Para que serve INSERIR ?") ;
		printf ("\n3 - Para que serve REMOVER ?") ;
		printf ("\n4 - Para que serve IMPRIMIR ?");
		printf ("\n5 - Sair do Menu") ;
		printf ("\nDigite o valor correspondente a dúvida e pressione ENTER: ") ;
		scanf ("%i" , &opc1) ;
		
		switch (opc1)
		{
			case 1:
			{
				printf("\nA partir de uma escolha feita por você no menu principal, o programa executará o solicitado. Basta seguir os informes pedidos.");
				printf("\nOBS.: Tenha em mente que se você não adicionar nenhum jogo, a opção REMOVER E IMPRIMIR acusará erro.");
				break ;
			}
			case 2:
			{
				printf("\nSerá pedido para que digite os dados na lista. Você deve informar o código, nome e um rank.");
				printf("\nLEMBRANDO que deve ter em mãos o código e nome do jogo.");
				break;
			}
			case 3:
			{
				printf("\nSerá excluído da lista um jogo. Você deve informar o código quando for solicitado.");
				printf("\nOBS1.: Caso não tenha adicionado nenhum jogo , o programa acusará erro.");
				printf("\nOBS2.: Tenha em mãos o código do jogo.") ;
				break;
	
			}
			case 4 :
			{
				printf("\nSerá exibido todo(s) jogo(s) da lista a partir do ranking escolhido. Você deverá informar o ranking.") ;
				printf("\nOBS.: Caso não tenha adicionado qualquer jogo do ranking específico , o programa acusará erro") ;
				break ;
			}
			case 5 :
			{
				break ;
			}
			default :
			{
				printf("Valor inserido inválido.");
				break ;
			}
		}
		printf("\n") ;
		system("pause");
	}
	while (opc1 != 5) ;
	/* O que me motivou a fazer esse código foi a minha preferência por jogos virtuais então a partir disso ,porque
	não implementar um código de algo que eu realmente gosto ? Além de que o conceito de listas  pode ser aplicado
	a bibliotecas de jogos de uma loja virtual(como a da Steam ou Epic Games) e a partir dos jogos comprados , pode se organizar
	por prioridade atraves de lista , os jogos mais jogados (Favoritos) , os que são bons mais não jogados com uma certa frequencia
	(Intermediarios) e por fim , os que voce compra devido a crítica ou usuários dizer que é bom , mais voce se arrependeu da compra (Comuns).
	Partindo desse pressuposto pode se criar uma lista , pois assim o usuário saberá aonde estão seus jogos predilétos (começo da lista)
	e os que não compensam jogar.(final da lista)*/
}
