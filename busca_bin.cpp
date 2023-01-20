#include<iostream>

using namespace std;

int binaria(int vetor[], int tamanho, int x);

int main(int argc, char** argv)
{
	int val ;     //Elemento desejado
	int x ;       // Tamanho do Vetor
	int j ;       //contador
	int r ;       // resposta
	int vet[100] ; // Vetor
	// Lendo o tamanho do Vetor
	cin >> x;

	// Lendo os elementos do Vetor
	for(j = 0 ; j < x ; j++)
	{
		cin >> vet[j] ;
	}

	//Lendo Elemento a ser procurado
	cin >> val;

	//Procurando elemento do vetor
	r = binaria(vet, x, val) ;

	//Apresentando o resultado
	if(r == meio)
	{
		cout << "Valor encontrado" ;
	}
	else
	{
		cout << "valor não encontrado." ;
	}
	return 0;
}


int binaria(int vetor[], int tamanho, int x)
{
	bool achou; // var aux p/ busca
	int baixo, meio, alto; // var aux
	baixo = 0;
	alto = tamanho - 1;
	achou = false;

	while ((baixo <= alto) && (achou == false))
	{
		meio = (baixo + alto) / 2;
		if (x < vetor[meio])
			alto = meio - 1;
		else if (x > vetor[meio])
			baixo = meio + 1;
		else
			achou = true;
	}
	if (achou)
		return meio;
	else
		return -1;
}
