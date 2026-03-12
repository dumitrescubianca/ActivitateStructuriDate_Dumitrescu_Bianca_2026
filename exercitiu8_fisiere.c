#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraCarte {
	int id;
	int nrPagini;
	float pret;
	char* titlu;
	char* autor;
};

typedef struct StructuraCarte Carte;

void afisareCarte(Carte c) {
	printf("ID: %d\n", c.id);
	printf("Nr pagini: %d\n", c.nrPagini);
	printf("Pret: %.2f\n", c.pret);
	printf("Titlu: %s\n", c.titlu);
	printf("Autor: %s\n\n", c.autor);
}

void afisareVectorCarti(Carte* carti, int nrCarti) {
	for (int i = 0; i < nrCarti; i++) {
		afisareCarte(carti[i]);
	}
}

void adaugaCarteInVector(Carte** carti, int* nrCarti, Carte carteNoua) {

	Carte* aux = (Carte*)malloc(sizeof(Carte) * ((*nrCarti) + 1));

	for (int i = 0; i < *nrCarti; i++) {
		aux[i] = (*carti)[i];
	}

	aux[*nrCarti] = carteNoua;

	free(*carti);
	*carti = aux;
	(*nrCarti)++;
}

Carte citireCarteFisier(FILE* file) {

	char buffer[100];
	char sep[] = ",\n";

	fgets(buffer, 100, file);

	char* token;
	Carte c;

	token = strtok(buffer, sep);
	c.id = atoi(token);

	token = strtok(NULL, sep);
	c.nrPagini = atoi(token);

	token = strtok(NULL, sep);
	c.pret = atof(token);

	token = strtok(NULL, sep);
	c.titlu = (char*)malloc(strlen(token) + 1);
	strcpy(c.titlu, token);

	token = strtok(NULL, sep);
	c.autor = (char*)malloc(strlen(token) + 1);
	strcpy(c.autor, token);

	return c;
}

Carte* citireVectorCartiFisier(const char* numeFisier, int* nrCarti) {

	FILE* f = fopen(numeFisier, "r");

	if (f == NULL) {
		printf("Nu s-a putut deschide fisierul!\n");
		return NULL;
	}

	Carte* vector = NULL;
	*nrCarti = 0;

	while (!feof(f)) {

		Carte c = citireCarteFisier(f);

		if (c.titlu != NULL) {
			adaugaCarteInVector(&vector, nrCarti, c);
		}
	}

	fclose(f);

	return vector;
}

void dezalocareVectorCarti(Carte** vector, int* nrCarti) {

	for (int i = 0; i < *nrCarti; i++) {
		free((*vector)[i].titlu);
		free((*vector)[i].autor);
	}

	free(*vector);

	*vector = NULL;
	*nrCarti = 0;
}

int main() {

	int nrCarti = 0;

	Carte* carti = citireVectorCartiFisier("carti.txt", &nrCarti);

	if (carti != NULL) {

		afisareVectorCarti(carti, nrCarti);

		dezalocareVectorCarti(&carti, &nrCarti);
	}

	return 0;
}