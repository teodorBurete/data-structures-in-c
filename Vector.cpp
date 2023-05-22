#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct {
	
	int cod;
	char* denumire;
	float pret;
} produs;


void citireVector(produs* vectorProduse, int n) {

	char buffer[100];

	for (int i = 0; i < n; i++) {
		produs* p = &vectorProduse[i];
		printf("Cod produs: ");
		scanf("%d", &(p->cod));
		printf("Denumire produs: ");
		scanf("%s", buffer);

		p->denumire = (char*)malloc(strlen(buffer));
		strcpy(p->denumire, buffer);

		printf("Pret produs: ");
		scanf("%f", &(p->pret));
	}
}

void afisareVector(produs* vectorProduse, int n) {
	for (int i = 0; i < n; i++) {
		printf("Codul=%d, Denumire=%s, Pret=%5.2f", vectorProduse[i].cod, vectorProduse[i].denumire, vectorProduse[i].pret);
		printf("\n");
	}
}

void dezalocareVector(produs* vectorProduse, int n) {
	for (int i = 0; i < n; i++) {
		free(vectorProduse[i].denumire);
	}

	free(vectorProduse);

}
int main() {


	//dinamic
	int n;
	printf("Numar produse:");
	scanf("%d", &n);

	produs* vectorProduse = (produs*)malloc(n * sizeof(produs));
	citireVector(vectorProduse, n);
	afisareVector(vectorProduse, n);
//	return 0;
}