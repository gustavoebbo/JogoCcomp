#include <stdio.h>

int main()
{
	int numero = 0;
	int fase[11][17];
	int linha, coluna;

	FILE* leitor;
	leitor = fopen("fases2.txt" ,"r");

	for(linha=0;linha<11;linha++)
	{
		for(coluna=0;coluna<17;coluna++)
		{
		
			fscanf(leitor,"%d", &numero);
			fase[linha][coluna] = numero;
		}
		
	}

    for(linha=0;linha<11;linha++)
	{
		for(coluna=0;coluna<17;coluna++)
		{
			printf("%d",fase[linha][coluna]);
		}
		printf("\n");
	}

}