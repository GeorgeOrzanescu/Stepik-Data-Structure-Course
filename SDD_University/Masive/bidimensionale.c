#include<stdio.h>
#include<malloc.h>



void interschimbare(int linie1, int linie2, int matrice[4][4]) {
	int aux;

	for (int i = 0; i < 4; i++)
	{
		aux = matrice[linie1][i];
		matrice[linie1][i] = matrice[linie2][i];
		matrice[linie2][i] = aux;
	}
}


void liniarizare(int dupaLiniarizare[], int matrice[4][4]) {
	int index = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++) {
			dupaLiniarizare[index++] = matrice[i][j];
		}
	}
}

int main() {
	int masivBi[4][4];

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			masivBi[i][j] = i * j;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf("%d ", masivBi[i][j]);
		}
		printf("\n");

	}

	// interschimbare linii sau coloane
	interschimbare(1, 3, masivBi);  // arrays sunt folosite ca referinta by default 

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf("%d ", masivBi[i][j]);
		}
		printf("\n");

	}


	// liniarizare matrice bidimensionala
	int matriceLiniarizata[16];
	liniarizare(matriceLiniarizata, masivBi);
	for (int i = 0; i < 16; i++)
	{
		printf("%d ", matriceLiniarizata[i]);

	}

	return 0;
}


