#include<stdlib.h>
#include<stdio.h>

int main()
{
	int fatorial(int x);
	int num , res ;
	
	printf("Digite um numero inteiro: ");
	scanf("%i" , &num);
	
	res = fatorial(num);
	
	printf("Fatorial de %i eh %i\n" , num, res);
	
	system("pause");
	return 0;
}
int fatorial(int x) //ex.: x = 3
{
	int resultado;
	
	if(x == 0)
	{
		resultado = 1 ;
	}
	else
	{
		resultado = x *	fatorial(x - 1);
		/*          3 *  abre a fun��o fatorial de 2, e ainda n executa o fatorial anterior
                    2 *  abre a fun��o fatorial de 1, e ainda n executa o fatorial anterior
					1 *  abre a fun��o fatorial de 0, e ainda n executa o fatorial anterior
					como x = 0 e no if de cima p x=o resultado � 1 � a condi��o de loop � 
					parada e agora sim a fun��o executa o fatorial de 3 percorrendo o loop 
					de tr�s p frente . A Resposta de cada loop � colocada em (fatorial(x - 1))
		*/
	}
	
	return resultado;
}