#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct {
	int cod;
	char* nume;
	float medie;
	char* programStudiu;
} candidat;

typedef struct {
	candidat** vect;
	int dim;
} hashT;

int functieDispersie(hashT tabela, char nume[20])
{
	return nume[0] % tabela.dim;
}

int inserare(hashT tabela, candidat* c)
{
	int pozitie = 0;
	if (tabela.vect != NULL)
	{
		pozitie = functieDispersie(tabela, (*c).nume);
		if (tabela.vect[pozitie] == NULL)
		{
			tabela.vect[pozitie] = c;
		}
		else
		{
			int index = 1;
			while (pozitie + index < tabela.dim)
			{
				if (tabela.vect[pozitie + index] == NULL)
				{
					tabela.vect[pozitie + index] = c;
					pozitie += index;
					break;
				}
				index++;
			}
		}
	}
	return pozitie;
}

void traversareTabela(hashT tabela)
{
	if (tabela.vect != NULL)
	{
		for (int i = 0; i < tabela.dim; i++)
		{
			if (tabela.vect[i] != NULL)
			{
				printf("\npozitie = %d", i);
				printf("\nCod: %d,Nume: %s, Media: %5.2f, Program studiu: %s",
					tabela.vect[i]->cod, tabela.vect[i]->nume, tabela.vect[i]->medie, tabela.vect[i]->programStudiu);
			}
		}
	}
}

void dezalocareTabela(hashT tabela)
{
	if (tabela.vect != NULL)
	{
		for (int i = 0; i < tabela.dim; i++)
		{
			if (tabela.vect[i] != NULL)
			{
				free(tabela.vect[i]->nume);
				free(tabela.vect[i]->programStudiu);
				free(tabela.vect[i]);
			}
		}
		free(tabela.vect);
	}
}
void main()
{
	hashT tabela;
	tabela.dim = 101;
	tabela.vect = (candidat**)malloc(tabela.dim * sizeof(candidat*));
	for (int i = 0; i < tabela.dim; i++)
	{
		tabela.vect[i] = NULL;
	}
	//candidat* c;
	//char buffer[20];
	//int n;

	//FILE* f = fopen("fisier.txt", "r");
	//fscanf(f, "%d", &n);
	//for (int i = 0; i < n; i++)
	//{
	//	c = (candidat*)malloc(sizeof(candidat));
	//	fscanf(f, "%d", &c->cod);
	//	fscanf(f, "%s", buffer);
	//	c->nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	//	strcpy(c->nume, buffer);
	//	fscanf(f, "%f", &c->medie);
	//	fscanf(f, "%s", buffer);
	//	c->programStudiu = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	//	strcpy(c->programStudiu, buffer);

	//	inserare(tabela, c);
	//}
	//fclose(f);


	// DEZALOCARE DA EROARE DACA FOLOSESTI CANDIDATI DECLARATI DIRECT 

	// !! DACA CITESTI DIN FISIER MERGE !! DUBIOS 
	candidat c1 = { 1,"Geo",6.7,"CSIE" }; 
	candidat c2 = {2,"Maria",6.9,"CSIE" };

	candidat* pc1 = &c1;
	candidat* pc2 = &c2;

	inserare(tabela, pc1);
	inserare(tabela, pc2);

	traversareTabela(tabela);
	dezalocareTabela(tabela);

}
