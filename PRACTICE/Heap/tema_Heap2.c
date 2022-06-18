#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<malloc.h>



typedef struct {
	int cod;
	char* nume;
	char* descriere;
	float varsta;
	int prioritate;
}Pacient;

typedef struct {
	int dimensiune;
	Pacient* pacienti;
}Heap;

void filtrare(Heap h, int index) {
	int indexRoot = index;
	int indexStanga = 2 * index + 1;
	int indexDreapta = 2 * index + 2;

	if (indexStanga < h.dimensiune && 
		h.pacienti[indexRoot].prioritate < h.pacienti[indexStanga].prioritate) {
		indexRoot = indexStanga;
	}
	if (indexDreapta < h.dimensiune && 
		h.pacienti[indexRoot].prioritate < h.pacienti[indexDreapta].prioritate) {
		indexRoot = indexDreapta;
	}
	if (indexRoot != index) {
		Pacient temp = h.pacienti[index];
		h.pacienti[index] = h.pacienti[indexRoot];
		h.pacienti[indexRoot] = temp;

		filtrare(h, indexRoot);
	}
}

Heap inserareHeap(Heap h, Pacient p) {
	Pacient* pacientiNoi = (Pacient*)malloc(sizeof(Pacient) * (h.dimensiune + 1));
	for (int i = 0; i < (h.dimensiune + 1); i++)
	{
		pacientiNoi[i] = h.pacienti[i];
	}
	pacientiNoi[h.dimensiune] = p;
	h.dimensiune++;
	free(h.pacienti);
	h.pacienti = pacientiNoi;

	for (int i = (h.dimensiune -1) / 2 ; i >= 0; i--)
	{
		filtrare(h, i);
	}

	return h;
}

void afisareHeap(Heap h) {
	for (int i = 0; i < h.dimensiune; i++)
	{
		printf("%s -- %s -- %d\n", h.pacienti[i].nume, 
			h.pacienti[i].descriere, 
			h.pacienti[i].prioritate);
	}
}


int numarCategorie1(Heap h) {
	int numarCateg1 = 0;
	for (int i = 0; i < h.dimensiune; i++)
	{
		if (h.pacienti[i].prioritate == 5) {
			numarCateg1++;
		}
	}

	return numarCateg1;
}

Heap extragerePacient(Heap h, Pacient* p) {
	*p = h.pacienti[0];
	// schimbam primul cu ultimul ca sa stergem apoi
	Pacient temp = h.pacienti[0];
	h.pacienti[0] = h.pacienti[h.dimensiune - 1];
	h.pacienti[h.dimensiune - 1] = temp;

	Pacient* pacientiNoi = (Pacient*)malloc(sizeof(Pacient) * (h.dimensiune - 1));
	for (int i = 0; i < (h.dimensiune - 1); i++)
	{
		pacientiNoi[i] = h.pacienti[i];
	}
	h.dimensiune--;
	free(h.pacienti);

	h.pacienti = pacientiNoi;
	for (int i = (h.dimensiune - 1) / 2; i >= 0; i--)
	{
		filtrare(h, i);
	}
	return h;
}
void main() {
	Heap h;
	h.dimensiune = 0;
	h.pacienti = (Pacient*)malloc(sizeof(Pacient) * h.dimensiune);

	Pacient p1 = { 1,"Geo","Tuse",35.7, 1 };
	Pacient p2 = { 5,"Marius","Febra",0.9, 5 };
	Pacient p3 = { 6,"Denisa","Durere cap",28.3, 2 };
	Pacient p4= { 2,"Ioana","Tuse seaca",0.6, 5};

	h = inserareHeap(h, p1);
	h = inserareHeap(h, p2);
	h = inserareHeap(h, p3);
	h = inserareHeap(h, p4);
	afisareHeap(h);

	printf("\n Numar categorie 1 prioritate: %d \n", numarCategorie1(h));

	Pacient p;
	h = extragerePacient(h, &p);
	printf("%s -- %s -- %d\n",p.nume,
		p.descriere,
		p.prioritate);
	printf("\n");
	afisareHeap(h);
}