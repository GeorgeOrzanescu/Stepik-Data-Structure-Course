#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct {
	int idArticol;
	char* categArticol;
	char* titlu;
	int nrPag;
	int nrAutori;
}Articol;

typedef struct {
	Articol articol;
	struct NodeLS* next;
}NodeLS;

typedef struct {
	NodeLS** articole;
	int dimensiune;
}TabelaD;

int hashFunction(const char* categorie) {
	return  (categorie[0] / 5 + categorie[1] / 5) / 4 + strlen(categorie);
}

TabelaD inserare(TabelaD tabelaD, Articol a) {
	NodeLS* nodDeInserat = (NodeLS*)malloc(sizeof(NodeLS));
	nodDeInserat->articol.idArticol = a.idArticol;
	nodDeInserat->articol.categArticol = (char*)malloc((strlen(a.categArticol) + 1) * sizeof(char));
	strcpy(nodDeInserat->articol.categArticol, a.categArticol);
	nodDeInserat->articol.titlu = (char*)malloc((strlen(a.titlu) + 1) * sizeof(char));
	strcpy(nodDeInserat->articol.titlu, a.titlu);
	nodDeInserat->articol.nrPag = a.nrPag;
	nodDeInserat->articol.nrAutori = a.nrAutori;

	nodDeInserat->next = NULL;
	int pozitie = hashFunction(a.categArticol);
	if (pozitie < tabelaD.dimensiune) {
		if (tabelaD.articole[pozitie] == NULL) {
			tabelaD.articole[pozitie] = nodDeInserat;

		}
		else {
			NodeLS* nodDeplasare = tabelaD.articole[pozitie];
			while (nodDeplasare->next) {
				nodDeplasare = nodDeplasare->next;
			}
			nodDeplasare->next = nodDeInserat;
		}
	}
	return tabelaD;
}

void afisareTabela(TabelaD tabelaD) {
	for (int i = 0;  i < tabelaD.dimensiune; i++)
	{
		if (tabelaD.articole[i] != NULL) {
			printf("Pozitia: %d\n", i);
			NodeLS* nodDeplasare = tabelaD.articole[i];
			while (nodDeplasare) {
				printf("%d -- %s -- %s -- %d\n", nodDeplasare->articol.idArticol, nodDeplasare->articol.categArticol,
					nodDeplasare->articol.titlu,nodDeplasare->articol.nrPag);
				nodDeplasare = nodDeplasare->next;
			}
		}
	}
}

int numArticoleCategorie(TabelaD tabelaD, const char* categorie) {
	int result = 0;
	for (int i = 0; i < tabelaD.dimensiune; i++)
	{
		if (tabelaD.articole[i] != NULL) {
			NodeLS* nodDeplasare = tabelaD.articole[i];
			while (nodDeplasare) {
				if (strcmp(nodDeplasare->articol.categArticol, categorie) == 0)
				{
					result++;
				}
				nodDeplasare = nodDeplasare->next;
			}
		}
	}
	return result;
}

Articol* getArticoleCategorie(TabelaD tabelaD, const char* categorie) {
	int numArticoleGasite = numArticoleCategorie(tabelaD, categorie);
	Articol* articole = (Articol*)malloc(sizeof(Articol) * numArticoleGasite);
	int index = 0;
	for (int i = 0; i < tabelaD.dimensiune; i++)
	{
		if (tabelaD.articole[i] != NULL) {
			NodeLS* nodDeplasare = tabelaD.articole[i];
			while (nodDeplasare) {
				if (strcmp(nodDeplasare->articol.categArticol, categorie) == 0)
				{
					articole[index] = nodDeplasare->articol;
					index++;
				}
				nodDeplasare = nodDeplasare->next;
			}
		}
	}
	return articole;
}

TabelaD stergereArticol(TabelaD tabelaD, const char* categorie, int idArticol) {
	int pozitie = hashFunction(categorie);
	if (pozitie < tabelaD.dimensiune) {
		if (tabelaD.articole[pozitie] != NULL) {
			NodeLS* nodDeplasare = tabelaD.articole[pozitie];
			if (nodDeplasare->next == NULL && nodDeplasare->articol.idArticol == idArticol) {
				free(nodDeplasare->articol.categArticol);
				free(nodDeplasare->articol.titlu);
				free(nodDeplasare);
				tabelaD.articole[pozitie] = NULL;
				return tabelaD;
			}
			else if(nodDeplasare->next != NULL && nodDeplasare->articol.idArticol == idArticol) {
				tabelaD.articole[pozitie] = nodDeplasare->next;
				free(nodDeplasare->articol.categArticol);
				free(nodDeplasare->articol.titlu);
				free(nodDeplasare);
				return tabelaD;
			}
			else {
				NodeLS* nodAnterior = nodDeplasare;
				nodDeplasare = nodDeplasare->next;
				while (nodDeplasare) {
					if (nodDeplasare->articol.idArticol == idArticol) {
						nodAnterior->next = nodDeplasare->next;
						free(nodDeplasare->articol.categArticol);
						free(nodDeplasare->articol.titlu);
						free(nodDeplasare);
						return tabelaD;
					}
				}
			}
		}
	}
	return tabelaD;
}

TabelaD incrementarePagini(TabelaD tabelaD) {
	for (int i = 0; i < tabelaD.dimensiune; i++)
	{
		if (tabelaD.articole[i] != NULL) {
			NodeLS* nodDeplasare = tabelaD.articole[i];
			while (nodDeplasare) {
				nodDeplasare->articol.nrPag++;
				nodDeplasare = nodDeplasare->next;
			}
		}
	}
	return tabelaD;
}

int getNumCategory(TabelaD tabelaD) {
	int result = 0;
	for (int i = 0; i < tabelaD.dimensiune; i++)
	{
		if (tabelaD.articole[i] != NULL) {
			result++;
		}
	}
	return result;
}

int* getCategorii(TabelaD tabelaD) {
	int numCat = getNumCategory(tabelaD);
	int*  numPag = (int*)malloc(sizeof(int)* numCat);
	for (int i = 0; i < numCat; i++)
	{
		numPag[i] = 0;
	}
	int index = 0;
	for (int i = 0; i < tabelaD.dimensiune; i++)
	{
		if (tabelaD.articole[i] != NULL) {
			NodeLS* nodDeplasare = tabelaD.articole[i];
			while (nodDeplasare) {
				numPag[index] += nodDeplasare->articol.nrPag;
				nodDeplasare = nodDeplasare->next;
			}
			index++;
		}
		
	}
	return numPag;
}

void main() {
	TabelaD tabelaD;
	tabelaD.dimensiune = 100;
	tabelaD.articole = (NodeLS**)malloc(sizeof(NodeLS*) * tabelaD.dimensiune);

	for (int i = 0; i < tabelaD.dimensiune; i++)
	{
		tabelaD.articole[i] = NULL;
	}

	Articol a1 = { 11,"Iot Security","Security",12,2 };
	Articol a2 = { 12,"Backend","Development",4,3 };
	Articol a2b = { 14,"Backend","Development",4,3 };
	Articol a3 = { 17,"Frontend","React",1,6 };
	
	tabelaD = inserare(tabelaD, a1);
	tabelaD = inserare(tabelaD, a2);
	tabelaD = inserare(tabelaD, a2b);
	tabelaD = inserare(tabelaD, a3);

	Articol* articoleBackend = NULL;
	articoleBackend = getArticoleCategorie(tabelaD, "Backend");
	//for (int i = 0; i < 2; i++)
	//{
	//	printf("%d -- %s -- %s\n", articoleBackend[i].idArticol, articoleBackend[i].categArticol,
	//		articoleBackend[i].titlu);

	//}
	//tabelaD = stergereArticol(tabelaD, "Backend", 14);
	/*afisareTabela(tabelaD);
	tabelaD = incrementarePagini(tabelaD);*/
	afisareTabela(tabelaD);
	int numCategory = getNumCategory(tabelaD);
	int* numPag = getCategorii(tabelaD);
	for (int i = 0; i < numCategory; i++)
	{
		printf("%d\n", numPag[i]);
	}
	printf("End of program!");
}