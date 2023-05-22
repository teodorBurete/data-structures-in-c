#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct {

	int cod;
	char* denumire;
	float pret;
} produs;

typedef struct {

	produs inf;
	struct nodLs* next;

}nodLs;


void inserareNod(nodLs** cap, produs p) {

	nodLs* nou = (nodLs*)malloc(sizeof(nodLs));
	nou->next = NULL;

	nou->inf.cod = p.cod;
	nou->inf.denumire = (char*)malloc((strlen(p.denumire) + 1) * sizeof(char));
	strcpy(nou->inf.denumire, p.denumire);
	
	nou->inf.pret = p.pret;

	if (*cap == NULL) {
		*cap = nou;
	}
	else {
		nodLs* temp = *cap;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nou;
	}

}
 
void traversareLista(nodLs* cap) {
	nodLs* temp = cap;
	while (temp) {
		printf("Codul=%d, Denumire=%s, Pret=%5.2f", temp->inf.cod,temp->inf.denumire,temp->inf.pret);
		printf("\n");
		temp = temp->next;
	}
}

void dezalocareLista(nodLs* cap) {

	nodLs* temp = cap;
	while (temp) {
		free(temp->inf.denumire);
		nodLs* temp1 = temp;
		temp = temp->next;
		free(temp1);
	}
}

void citireProdus(produs* p) {

	char buffer[20];

	printf("Cod: ");
	scanf("%d", &(p->cod));

	printf("Denumire: ");
	scanf("%s", buffer);
	p->denumire = (char*)malloc((strlen(buffer)+1)*sizeof(char));
	strcpy(p->denumire, buffer);

	printf("Pret: ");
	scanf("%f", &(p->pret));
}

produs citireProdus2() {
	produs p;
	char buffer[20];

	printf("Cod: ");
	scanf("%d", &p.cod);

	printf("Denumire: ");
	scanf("%s", buffer);
	p.denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(p.denumire, buffer);

	printf("Pret: ");
	scanf("%f", &p.pret);

	return p;
}


int main() {

	nodLs* cap = NULL;
	int n = 2;
	/*produs* p = (produs*)malloc(sizeof(produs));
	for (int i = 0; i < n; i++) {
		citireProdus(p);
		inserareNod(&cap, *p);
		free(p->denumire);
	}
	traversareLista(cap);*/

	produs p;
	for (int i = 0; i < n; i++) {
		p = citireProdus2();
		inserareNod(&cap, p);
		free(p.denumire);
	}

	traversareLista(cap);
	dezalocareLista(cap);


}