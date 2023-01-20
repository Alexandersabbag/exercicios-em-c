/*Armazenar em ordem de favoritos(preferencial) os jogos de uma biblioteca de jogos.
Em uma biblioteca de n jogos(inserido pelo user) de uma plataforma digital, o usu�rio pode definir quais 
jogos s�o os de sua preferencia e portanto  organizar por prioridade em uma fila.*/
//declara��o das bibliotecas.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <conio.h>

//criando a struct base.
typedef struct dados     //struct que armazenar� as informa��es inseridas pelo jogador.
{
	int cod , rank ;     //c�digo do jogo e ranking(prioridade).
	char nome[99] ;      //nome do jogo.
	dados *prox ;        //proximo do struct.
	dados *ant;          //anterior do struct.
};

//declarando os ponteiros.
dados *aux ;                                       //ponteiro auxiliar.
dados *auxant ;                                    //ponteiro aux anterior (usado para fun��o destruir uma c�lula)
dados *auxprox ;                                   //ponteiro aux posterior (usado para fun��o destruir uma c�lula)
dados *fim ;                                       //ponteiro da ultima c�lula da fila

//declarando a struct que armazenar� somente os valores inseridos pelo usu�rio
dados novo ;

//criando os headers.
dados *inicio = (dados *)malloc(sizeof(dados)) ;   //struct header (c�lula fixa no inicio da fila)
dados *inimed = (dados *)malloc(sizeof(dados)) ;   //struct header (c�lula fixa no inicio das c�lulas meio da fila)
dados *inifim = (dados *)malloc(sizeof(dados)) ;   //struct header (c�lula fixa no inicio das c�lulas fim da fila)

//declara��o das fun��es
void inserir() ;     //fun��o para adicionar um  novo elemento.
void remover() ;     //fun��o para remover um elemento.
void imprimir() ;    //fun��o para imprimir um elemento.
void ajuda() ;       //fun��o ajuda.

//declara��o das vari�veis globais.
int opc , i  ;       //op��o e contador.

//fun��o principal
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
		printf("Escolha uma das op��es abaixo:");
		printf("\n1 - Inserir");
		printf("\n2 - Remover") ;
		printf("\n3 - Imprimir") ;
		printf("\n4 - Ajuda") ;
		printf("\n5 - Sair") ;
		printf("\nOp��o : ") ;
		scanf("%i" , &opc) ;
		if(opc < 1 || opc > 5)
		{
			printf("\nOp��o inv�lida.\n") ;
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

void inserir() //O usu�rio informar� o c�digo , nome e ranking do jogo respectivamente.
{
	//A STRUCT NOVO SERVE APENAS PARA INSERIR OS DADOS QUE O USU�RIO PASSAR�.
	//inserindo as informa��es na struct novo.
	printf("\nInsira o c�digo do jogo: ");
	scanf("%i" , &novo.cod) ;
	printf("\nDigite o nome do jogo: ");
	fflush(stdin);
	gets(novo.nome);
	do
	{
		printf("\nRank do Jogo (1 - Favorito , 2 - Intermediario , 3 - N�o sabe)");
		printf("\nRank = ") ;
		scanf("%i" , &novo.rank);
		if(novo.rank < 1 || novo.rank > 3)
			printf("\nValor Incorreto!");
	}
	while(novo.rank < 1 || novo.rank > 3);
	//ant e prox s�o tratados como ponteiros e n�o como variaveis, portanto s�o irrelevantes nessa c�lula.
	novo.ant = NULL ;
	novo.prox = NULL ;

	//A partir do Ranking que ser� feito a inser��o na fila por prioridade
	if(novo.rank == 1)
	{
		//Percorre todo o inicio de favorito (header) at� chegar no mais recente
		aux = inicio ;
		while(aux -> prox != inimed)
			aux = aux -> prox;

		//Faz os apontamentos necess�rios para inser��o
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
		//Percorre todo o inicio de intermediario(header) at� chegar no mais recente
		aux = inimed ;
		while(aux -> prox != inifim)
			aux = aux -> prox ;

		//Faz os apontamentos necess�rios para inser��o
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
		//Percorre todo o inicio de fim(header) at� chegar no mais recente
		aux = inifim ;
		while (aux != fim )
			aux = aux -> prox ;

		//Faz os apontamentos necess�rios para inser��o
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

void remover() //Fun��o que percorrer� toda a lista at� achar o c�digo do jogo para sua remo��o
{
	int codigo ;                                       //vari�vel local de compara��o entre o c�digo desejado e o que ser� procurado.
	printf("\nDigite o c�digo do jogo a ser removido: ");
	scanf("%i" , &codigo);

	//percorro as c�lulas at� chegar no valor desejado.
	aux = inicio ;                                     //aux que percorrer� a c�lula a partir do header inicio
	while (aux -> cod != codigo || aux -> cod == NULL) //percorrendo a lista inteira
		aux = aux -> prox ;

	if(aux -> cod == NULL)                             //caso percorra a lista inteira e n�o ache o c�digo do jogo
	{
		printf("\nNenhum jogo inserido ou achado\n");
		system("pause") ;
		system("cls") ;
	}
	else if(aux == fim)                                //caso a c�lula desejada a ser removida esteja no final da lista.
	{
		//� feito os apontamentos para a c�lula anterior somente.
		auxant = aux ;
		auxant = aux -> ant ;
		fim = auxant ;
		fim -> prox = NULL ;

		//destroi a �ltima c�lula
		free(aux) ;

		printf("\nJogo encontrado e exclu�do!\n") ;
		system("pause") ;
		system("cls") ;
	}
	else                                               //caso o valor esteja entre o inicio e fim (at� a penultima c�lula)
	{
		//apontando as auxiliares para a c�lula anterior e posterior para n�o perder a refer�ncia
		auxant = aux ;
		auxant = aux -> ant ;
		auxprox = aux ;
		auxprox = aux -> prox ;

		//desconectando a c�lula que ser� removida
		auxant -> prox = NULL ;
		auxprox -> ant = NULL ;
		aux -> ant = NULL ;
		aux -> prox = NULL ;

		//destr�i a c�lula
		free(aux) ;

		//aponto as c�lulas refer�nciadas
		auxant -> prox = auxprox ;
		auxprox -> ant = auxant ;

		printf("\nJogo encontrado e exclu�do!\n") ;
		system("pause") ;
		system("cls") ;
	}
}

void imprimir() //Exibir� somente a parte da lista de jogos inseridos.(A partir do ranking de prioridade)
{
	int numrank ;             //numero do rank.
	printf("\nDigite o ranking da lista a ser exibida: ");
	scanf("%i" , &numrank);

	
	if(numrank == 1)          //caso o rank seja 1 imprimir toda a lista de rank 1(Priorit�rio)
	{
		if (inicio -> prox == inimed) //caso a lista esteja vazia entre os headers
		{
			printf("\nJogo(s) n�o inserido(s) rank 1\n") ;
		}
		else              //caso a lista n�o esteja vazia entre os headers
		{
			printf("\n\tFavorito(s)\n");
			printf("----------------------------------------------------------") ;
			aux = inicio ;                //aux que percorrer� a lista a partir do header
			while(aux != inimed)          //percorrendo a lista
			{
				//exibindo os jogos da lista
				if(aux != inicio)
				{
					printf("\nC�digo : %i" , aux -> cod);
					printf("\nNome do Jogo : %s" , aux -> nome);
					printf("\n----------------------------------------------------------") ;
				}
				aux = aux -> prox ;
			}
		}
	}
	else if(numrank == 2)     //caso o rank seja 2 imprimir toda a lista de rank 2(N�o t�o priorit�rio)
	{
		if (inimed -> prox == inifim) //caso a lista esteja vazia entre os headers
		{
			printf("\nJogo(s) n�o inserido(s) no rank 2\n") ;
		}
		else                          //caso a lista n�o esteja vazia entre os headers
		{
			printf("\n\tIntermediario(s)\n");
			printf("\----------------------------------------------------------") ;
			aux = inimed ;               //aux percorrer� a lista a partir do header
			while(aux != inifim) //percorrendo a lista
			{
				//exibindo os jogos da lista
				if(aux != inimed)
				{
					printf("\nC�digo : %i" , aux -> cod);
					printf("\nNome do Jogo : %s" , aux -> nome);
					printf("\n----------------------------------------------------------") ;
				}
				aux = aux -> prox ;
			}
		}
	}
	else if(numrank == 3)                //caso o rank seja 3 imprimir toda a lista do rank 3(N�o priorit�rios)
	{
		if (inifim -> prox == NULL) //caso a lista esteja vazia e o ponteiro apontando para o header
		{
			printf("\nJogo(s) n�o inserido(s) no rank 3") ;
		}
		else               //caso a lista n�o esteja vazia entre o header e o ponteiro fim
		{
			printf("\n\tN�o sabe\n");
			printf("----------------------------------------------------------") ;
			aux = inifim ;             //aux  percorrer� a lista a partir do header
			while(aux != NULL) //percorrendo a lista
			{
				//exibindo os jogos da lista
				if(aux != inifim)
				{
					printf("\nC�digo : %i" , aux -> cod);
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
		printf ("\nEscolha uma das op��es abaixo:");
		printf ("\n1 - Como funciona o programa ?");
		printf ("\n2 - Para que serve INSERIR ?") ;
		printf ("\n3 - Para que serve REMOVER ?") ;
		printf ("\n4 - Para que serve IMPRIMIR ?");
		printf ("\n5 - Sair do Menu") ;
		printf ("\nDigite o valor correspondente a d�vida e pressione ENTER: ") ;
		scanf ("%i" , &opc1) ;
		
		switch (opc1)
		{
			case 1:
			{
				printf("\nA partir de uma escolha feita por voc� no menu principal, o programa executar� o solicitado. Basta seguir os informes pedidos.");
				printf("\nOBS.: Tenha em mente que se voc� n�o adicionar nenhum jogo, a op��o REMOVER E IMPRIMIR acusar� erro.");
				break ;
			}
			case 2:
			{
				printf("\nSer� pedido para que digite os dados na lista. Voc� deve informar o c�digo, nome e um rank.");
				printf("\nLEMBRANDO que deve ter em m�os o c�digo e nome do jogo.");
				break;
			}
			case 3:
			{
				printf("\nSer� exclu�do da lista um jogo. Voc� deve informar o c�digo quando for solicitado.");
				printf("\nOBS1.: Caso n�o tenha adicionado nenhum jogo , o programa acusar� erro.");
				printf("\nOBS2.: Tenha em m�os o c�digo do jogo.") ;
				break;
	
			}
			case 4 :
			{
				printf("\nSer� exibido todo(s) jogo(s) da lista a partir do ranking escolhido. Voc� dever� informar o ranking.") ;
				printf("\nOBS.: Caso n�o tenha adicionado qualquer jogo do ranking espec�fico , o programa acusar� erro") ;
				break ;
			}
			case 5 :
			{
				break ;
			}
			default :
			{
				printf("Valor inserido inv�lido.");
				break ;
			}
		}
		printf("\n") ;
		system("pause");
	}
	while (opc1 != 5) ;
	/* O que me motivou a fazer esse c�digo foi a minha prefer�ncia por jogos virtuais ent�o a partir disso ,porque
	n�o implementar um c�digo de algo que eu realmente gosto ? Al�m de que o conceito de listas  pode ser aplicado
	a bibliotecas de jogos de uma loja virtual(como a da Steam ou Epic Games) e a partir dos jogos comprados , pode se organizar
	por prioridade atraves de lista , os jogos mais jogados (Favoritos) , os que s�o bons mais n�o jogados com uma certa frequencia
	(Intermediarios) e por fim , os que voce compra devido a cr�tica ou usu�rios dizer que � bom , mais voce se arrependeu da compra (Comuns).
	Partindo desse pressuposto pode se criar uma lista , pois assim o usu�rio saber� aonde est�o seus jogos predil�tos (come�o da lista)
	e os que n�o compensam jogar.(final da lista)*/
}
