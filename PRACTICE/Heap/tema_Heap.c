#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<malloc.h>

typedef enum {
	telefonic,aplicatie
}CanalRezervare;

typedef struct {
	int durataRezervare;
	char* numeClient;
	CanalRezervare canalRezervare;
} Rezervare;

typedef struct {
	Rezervare* rezervari;
	int dimensiune;
}Heap;


void filtrare(Heap h, int index) {
	int indexRoot = index;
	int indexSt = 2 * index + 1;
	int indexDr = 2 * index + 2;

	if (indexSt < h.dimensiune &&
		h.rezervari[indexSt].durataRezervare > h.rezervari[indexRoot].durataRezervare) {
		indexRoot = indexSt;
	}
	if (indexDr < h.dimensiune &&
		h.rezervari[indexDr].durataRezervare > h.rezervari[indexRoot].durataRezervare) {
		indexRoot = indexDr;
	}

	if (indexRoot != index) {
		Rezervare temp = h.rezervari[index];
		h.rezervari[index] = h.rezervari[indexRoot];
		h.rezervari[indexRoot] = temp;

		filtrare(h, indexRoot);
	}

}


Heap inserareHeap(Heap h, Rezervare r) {

	Rezervare* rezervariNoi = (Rezervare*)malloc(sizeof(Rezervare) * (h.dimensiune + 1));
	for (int i = 0; i < h.dimensiune; i++)
	{
		rezervariNoi[i] = h.rezervari[i];
	}
	rezervariNoi[h.dimensiune] = r;
	h.dimensiune++;
	free(h.rezervari);
	h.rezervari = rezervariNoi;

	for (int i = (h.dimensiune - 1) / 2; i >= 0; i--)
	{
		filtrare(h, i);
	}
	return h;
}


void afisare(Heap h) {
	for (int i = 0; i <h.dimensiune; i++)
	{
		printf("%d --> %s\n", h.rezervari[i].durataRezervare, h.rezervari[i].numeClient);
	}
}



int numRezPesteTreiOre(Heap h){
	int rez = 0;
	for (int i = 0; i < h.dimensiune; i++)
	{
		if (h.rezervari[i].durataRezervare > 3) {
			rez++;
		}
	}
	return rez;
}

Rezervare* rezervariPesteTreiOre(Heap h) {
	int rezPesteTreiOre = numRezPesteTreiOre(h);
	
	if (rezervariPesteTreiOre == 0) {
		return NULL;
	}
	Rezervare* rezervariPesteTreiOre = (Rezervare*)malloc(sizeof(Rezervare)*rezPesteTreiOre);
	for (int i = 0; i < h.dimensiune; i++)
	{
		if (h.rezervari[i].durataRezervare > 3) {
			rezervariPesteTreiOre[i] = h.rezervari[i];
		}
	}

	return rezervariPesteTreiOre;
}


void generareRaportClient(Heap h,char* client) {
	FILE* f = fopen("client.txt", "w");
	if (f) {
		for (int i = 0; i < h.dimensiune; i++)
		{
			if (strcmp(h.rezervari[i].numeClient,client) == 0) {
				fprintf(f, "%d", h.rezervari[i].durataRezervare);
				fprintf(f, "%s", h.rezervari[i].numeClient);
			}
		}
	}
	fclose(f);
}

Heap extragereRezervare(Heap h,Rezervare* rez) {
	Rezervare* rezervariNoi = (Rezervare*)malloc(sizeof(Rezervare) * (h.dimensiune - 1));
	
	Rezervare temp = h.rezervari[0];
	h.rezervari[0] = h.rezervari[h.dimensiune - 1];
	h.rezervari[h.dimensiune - 1] = temp;

	*rez = h.rezervari[h.dimensiune - 1];
	for (int i = 0; i < h.dimensiune - 1; i++)
	{
		rezervariNoi[i] = h.rezervari[i];
	}
	h.dimensiune--;
	free(h.rezervari);
	h.rezervari = rezervariNoi;

	for (int i = (h.dimensiune - 1) / 2; i >= 0; i--)
	{
		filtrare(h, i);
	}
	return h;
}

void main() {

	Heap h;
	h.dimensiune = 0;
	h.rezervari = (Rezervare*)malloc(sizeof(Rezervare) * h.dimensiune);

	Rezervare r1 = { 1,"Geo",aplicatie };
	Rezervare r2 = {5,"Maria",telefonic };
	Rezervare r3 = { 2,"Geo",aplicatie };
	Rezervare r4 = { 6,"Filip",aplicatie };

	h = inserareHeap(h, r1);
	h = inserareHeap(h, r2);
	h = inserareHeap(h, r3);
	h = inserareHeap(h, r4);


	afisare(h);
	int rezNumPesteTreiOre = numRezPesteTreiOre(h);
	Rezervare* rezPesteTreiOre = rezervariPesteTreiOre(h);
	for (int i = 0; i < rezNumPesteTreiOre; i++){
		printf("%d --> %s\n", rezPesteTreiOre[i].durataRezervare, rezPesteTreiOre[i].numeClient);
	}
	generareRaportClient(h, "Geo");

	Rezervare rezExtrasa;
	h = extragereRezervare(h, &rezExtrasa);
	printf("%d --> %s\n", rezExtrasa.durataRezervare, rezExtrasa.numeClient);
	printf("End of main!");
}