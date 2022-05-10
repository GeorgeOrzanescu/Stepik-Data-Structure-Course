#include<stdio.h>
#include<malloc.h>
#include <string.h>


typedef struct {
	char* name;
	char* symbol;
	float value;
} cryptoCoin;

// structuri ierarhizate

typedef struct {
	int day;
	int month;
	int year;
} date;

typedef struct {
	date birthdate;
	char* firstName;
	char* lastName;
	int* age;
} person;


void main() {


	cryptoCoin btc;
	btc.name = (char*)malloc((strlen("Bitcoin") + 1) * sizeof(char));
	strcpy(btc.name, "Bitcoin");
	btc.symbol = (char*)malloc((strlen("BTC") + 1) * sizeof(char));
	strcpy(btc.symbol, "BTC");


	printf("%s\n", btc.name);
	printf("%s\n", btc.symbol);

	cryptoCoin coin = { "Bitcoin", "BTC", 35000.434 }; // u can initialize a struct like this;
	printf("%5.2f\n", coin.value);
	printf("%s\n", coin.name);


    // structuri ierarhizate

    person p1;
    p1.birthdate.day = 1;
    p1.birthdate.month = 1;
    p1.birthdate.year = 1970;

    p1.firstName = (char*)malloc((strlen("John") + 1) * sizeof(char));
    strcpy(p1.firstName, "John");

    p1.lastName = (char*)malloc((strlen("Doe") + 1) * sizeof(char));
    strcpy(p1.lastName, "Doe");

    p1.age = (int*)malloc(sizeof(int));
    *p1.age = 30;

    printf("%s\n", p1.firstName);
    printf("%s\n", p1.lastName);
    printf("%d\n", *p1.age);

    person* p2 = (person*)malloc(sizeof(person));
    p2->birthdate.day = 1;
    p2->birthdate.month = 1;
    p2->birthdate.year = 1970;

    p2->firstName = (char*)malloc((strlen("John") + 1) * sizeof(char));
    strcpy(p2->firstName, "John");

    p2->lastName = (char*)malloc((strlen("Doe") + 1) * sizeof(char));
    strcpy(p2->lastName, "Doe");

    p2->age = (int*)malloc(sizeof(int));
    *p2->age = 30;

    printf("%s\n", p2->firstName);
    printf("%s\n", p2->lastName);
    printf("%d\n", *p2->age);
    
    
}