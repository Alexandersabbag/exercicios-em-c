/*Exerc�cio: Elaborar um programa para gerar um c�digo automaticamente,
ler nome e o valor do produto e armazenar em arquivo(n produtos), s�
poder� acessar o programa o usu�rio cadastrado, assim a primeira vez
que o programa for executado deve-se cadastrar um usu�rio e senha,
depois s� acessar� o programa com o usu�rio e senha cadastrados.
- utilizar fun��es
- gerar tr�s arquivos: sequ�ncia, usu�rio e produto*/
#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>
#include<conio.h>

FILE *user;        //usu�rio
FILE *product;     //produto
FILE *sequence;    //sequ�ncia

void cadastro()
{
	int s, password ; // s = sequencia,
	char name[30], opc, nameproduct[30];
	float value ;
	do
	{
		system("cls");
		printf("Deseja cadastrar? (Y/N): ");
		opc = getche();
		if(toupper(opc) == 'N')
			break;
		
		printf("\nNome: ");
		fflush(stdin);
		scanf("\n%30[^\n]", name);
		printf("\nSenha: ");
		scanf("%i" , &password);
		
		//condi��es para o user
		if((user = fopen("user.txt" , "r")) == NULL)
		{
			user = fopen("user.txt" , "w");
			fprintf(user, "%s ; %i ;\n", name , password);
			fclose(user);
		}
		else
		{
			fclose(user);

			user = fopen("user.txt" , "a");
			fseek(user, 0 , SEEK_END);
			fprintf(user, "%s ; %i ;\n", name , password);
			fclose(user);
		}
		
		//para cadastrar o arquivo preciso validar o nome e senha do usu�rio , uso strcpy entre os arquivos user e product ????
		//condicoes do produto
		do
		{
			system("cls");
			printf("Deseja adicionar um produto? (Y/N)");
			opc = getche();
			
			if(toupper(opc) == 'N')
				break;
		
			printf("\nNome do produto: ");
			fflush(stdin);
			scanf("\n%30[^\n]", nameproduct);
			printf("\nPreco do produto : ");
			scanf("%f" , &value);
			
			if((product = fopen("product.txt" , "r")) == NULL)
			{
				product = fopen("product.txt" , "w");
				fprintf (product, "%s ; %.2f ;\n", nameproduct, value);
				fclose(product);
			}
			else
			{
				fclose(product);
				
				product = fopen("product.txt" , "a");
				fseek(product , 0 , SEEK_END);
				fprintf (product, "%s ; %.2f ;\n", nameproduct, value);
				fclose(product);
			}
		}
		while(toupper(opc) != 'N');
		
		//condi��es da sequencia
		if((sequence = fopen("sequence.txt" , "r")) == NULL)
		{
			s = 1 ;
			sequence = fopen("sequence.txt" , "w");
			fprintf(sequence , "%i" , s);
			fclose(sequence);
		}
		else
		{
			while((fscanf(sequence, "%i" , &s)) != EOF)
			{
				fclose(sequence);
				s++;
				sequence = fopen("sequence.txt" , "w");
				fprintf(sequence , "%i" , s);
				fclose(sequence);
			}
		}
		
		printf("Deseja cadastrar mais um cliente? (Y/N)");
		opc = getche();
	}
	while(toupper(opc) != 'N');
}

int main(int argc, char** argv)
{
	cadastro() ;
	return 0;
}
