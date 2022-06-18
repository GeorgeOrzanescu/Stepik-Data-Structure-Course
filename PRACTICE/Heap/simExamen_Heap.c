#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<malloc.h>


typedef struct {
	int idClient;
	char* numeClient;
	char* problema;
	int severitate;
}Tichet;

typedef struct {
	Tichet* tichete;
	int dimensiune;
}Heap;


void filtrare(Heap h, int index) {
	int indexRoot = index;
	int indexSt = 2 * index + 1;
	int indexDr = 2 * index + 2;

	if (indexSt < h.dimensiune && h.tichete[indexRoot].severitate < h.tichete[indexSt].severitate) {
		indexRoot = indexSt;
	}
	if (indexDr < h.dimensiune && h.tichete[indexRoot].severitate < h.tichete[indexDr].severitate) {
		indexRoot = indexDr;
	}
	if (indexRoot != index) {
		Tichet temp = h.tichete[index];
		h.tichete[index] = h.tichete[indexRoot];
		h.tichete[indexRoot] = temp;

		filtrare(h, indexRoot);
	}
}


Heap inserare(Heap h, Tichet t) {
	Tichet* ticheteNoi = (Tichet*)malloc(sizeof(Tichet) * (h.dimensiune + 1));
	for (int i = 0; i < h.dimensiune + 1; i++)
	{
		ticheteNoi[i] = h.tichete[i];
	}
	
	ticheteNoi[h.dimensiune] = t;
	h.dimensiune++;
	free(h.tichete);
	h.tichete = ticheteNoi;

	for (int i = (h.dimensiune -1) /2 ; i >= 0 ; i--)
	{
		filtrare(h, i);
	}

	return h;
}


void afisareHeap(Heap h) {
	for (int i = 0; i < h.dimensiune; i++)
	{
		printf("%d -- %s -- %s -- %d\n", h.tichete[i].idClient, h.tichete[i].numeClient,
			h.tichete[i].problema, h.tichete[i].severitate);
	}
}

int numUrgentePeste8(Heap h) {
	int result = 0;
	for (int i = 0; i < h.dimensiune; i++){
		if (h.tichete[i].severitate > 8) {
			result++;
		}
	}
	return result;
}

int numarTicheteClient(Heap h,const char* numeClient) {
		int result = 0;
		for (int i = 0; i < h.dimensiune; i++) {
			if (strcmp(h.tichete[i].numeClient,numeClient) == 0) {
				result++;
			}
		}
		return result;
}



Tichet* getTicheteClient(Heap h, const char* numeClient) {
	int numTicheteClient = numarTicheteClient(h, numeClient);
	Tichet* ticheteClient = (Tichet*)malloc(sizeof(Tichet) * numTicheteClient);
	int index = 0;
	for (int i = 0; i < h.dimensiune; i++) {
		if (strcmp(h.tichete[i].numeClient, numeClient) == 0) {
			ticheteClient[index] = h.tichete[i];
			index++;
		}
	}

	return ticheteClient;
}


void main() {
	Heap h;
	h.dimensiune = 0;
	h.tichete = NULL;
	h.tichete = (Tichet*)malloc(sizeof(Tichet) * h.dimensiune);

	//Tichet t1 = { 1,"George","No access", 6 };
	//Tichet t2 = { 4,"Maria","Fail to connect", 7 };
	//Tichet t3 = { 7,"Denisa","Bad Gateway", 2 };
	//Tichet t4 = { 5,"Denisa","Not working Urgent",10 };
	//Tichet t5 = { 2,"Raisa","Restricted access",9};

	//h = inserare(h, t1);
	//h = inserare(h, t2);
	//h = inserare(h, t3);
	//h = inserare(h, t4);
	//h = inserare(h, t5);


	FILE* f = fopen("tichete.txt", "r");
	int n = 0;
	char buffer[20];
	if (f) {
		fscanf(f, "%d", &n);
		for (int i = 0; i < n; i++)
		{
			Tichet t;
			fscanf(f, "%d", &t.idClient);
			fscanf(f, "%s", buffer);
			t.numeClient = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
			strcpy(t.numeClient, buffer);
			fscanf(f, "%s", buffer);
			t.problema = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
			strcpy(t.problema, buffer);
			fscanf(f, "%d", &t.severitate);

			h = inserare(h, t);
		}
	}
	fclose(f);



	afisareHeap(h);

	printf("Numar tichete peste 8 prioritate: %d\n", numUrgentePeste8(h));
	printf("\nEnd of main!");
}