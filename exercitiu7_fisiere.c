#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraPacient {
	int id;
	int varsta;
	float costTratament;
	char* nume;
	char* diagnostic;
	unsigned char salon;
};
typedef struct StructuraPacient Pacient;

void afisarePacient(Pacient pacient) {
	printf("ID: %d\n", pacient.id);
	printf("Varsta: %d\n", pacient.varsta);
	printf("Cost tratament: %.2f\n", pacient.costTratament);
	printf("Nume: %s\n", pacient.nume);
	printf("Diagnostic: %s\n", pacient.diagnostic);
	printf("Salon: %c\n\n", pacient.salon);
}

void afisareVectorPacienti(Pacient* pacienti, int nrPacienti) {
	for (int i = 0; i < nrPacienti; i++) {
		afisarePacient(pacienti[i]);
	}
}

void adaugaPacientInVector(Pacient** pacienti, int* nrPacienti, Pacient pacientNou) {
	Pacient* aux = (Pacient*)malloc(sizeof(Pacient) * ((*nrPacienti) + 1));

	for (int i = 0; i < *nrPacienti; i++) {
		aux[i] = (*pacienti)[i];
	}

	aux[*nrPacienti] = pacientNou;

	free(*pacienti);
	*pacienti = aux;
	(*nrPacienti)++;
}

Pacient citirePacientFisier(FILE* file) {
	char buffer[256];
	char sep[] = ",\n";

	Pacient p;
	p.id = -1;
	p.varsta = 0;
	p.costTratament = 0;
	p.nume = NULL;
	p.diagnostic = NULL;
	p.salon = '-';

	if (fgets(buffer, 256, file) == NULL) {
		return p;
	}

	char* token = strtok(buffer, sep);
	if (token == NULL) return p;
	p.id = atoi(token);

	token = strtok(NULL, sep);
	if (token == NULL) return p;
	p.varsta = atoi(token);

	token = strtok(NULL, sep);
	if (token == NULL) return p;
	p.costTratament = (float)atof(token);

	token = strtok(NULL, sep);
	if (token == NULL) return p;
	p.nume = (char*)malloc(strlen(token) + 1);
	strcpy(p.nume, token);

	token = strtok(NULL, sep);
	if (token == NULL) {
		free(p.nume);
		p.nume = NULL;
		return p;
	}
	p.diagnostic = (char*)malloc(strlen(token) + 1);
	strcpy(p.diagnostic, token);

	token = strtok(NULL, sep);
	if (token == NULL) {
		free(p.nume);
		free(p.diagnostic);
		p.nume = NULL;
		p.diagnostic = NULL;
		return p;
	}
	p.salon = token[0];

	return p;
}

Pacient* citireVectorPacientiFisier(const char* numeFisier, int* nrPacientiCititi) {
	FILE* f = fopen(numeFisier, "r");
	Pacient* vector = NULL;
	*nrPacientiCititi = 0;

	if (f == NULL) {
		printf("Nu s-a putut deschide fisierul: %s\n", numeFisier);
		return NULL;
	}

	while (1) {
		Pacient p = citirePacientFisier(f);

		if (p.id == -1) {
			break;
		}

		adaugaPacientInVector(&vector, nrPacientiCititi, p);
	}

	fclose(f);
	return vector;
}

void dezalocareVectorPacienti(Pacient** vector, int* nrPacienti) {
	for (int i = 0; i < *nrPacienti; i++) {
		free((*vector)[i].nume);
		free((*vector)[i].diagnostic);
	}

	free(*vector);
	*vector = NULL;
	*nrPacienti = 0;
}

int main() {
	int nrPacienti = 0;
	Pacient* pacienti = citireVectorPacientiFisier("pacienti.txt", &nrPacienti);

	if (pacienti != NULL) {
		afisareVectorPacienti(pacienti, nrPacienti);
		dezalocareVectorPacienti(&pacienti, &nrPacienti);
	}
	else {
		printf("Vectorul nu a fost incarcat.\n");
	}

	return 0;
}