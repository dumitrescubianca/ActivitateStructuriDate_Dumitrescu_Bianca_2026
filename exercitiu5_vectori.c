#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pacient
{
	int id;
	char* nume;
	int varsta;
	float costTratament;
};

struct pacient initializare(int id, const char* nume, int varsta, float costTratament)
{
	struct pacient p;
	p.id = id;
	p.nume = NULL;
	p.varsta = varsta;
	p.costTratament = costTratament;

	p.nume = (char*)malloc(strlen(nume) + 1);
	if (p.nume != NULL)
	{
		strcpy_s(p.nume, strlen(nume) + 1, nume);
	}

	return p;
}

void afisare(struct pacient p)
{
	printf("ID: %d\n", p.id);
	printf("Nume: %s\n", p.nume);
	printf("Varsta: %d\n", p.varsta);
	printf("Cost tratament: %.2f\n", p.costTratament);
}

void afisareVector(struct pacient* vector, int nrElemente)
{
	for (int i = 0; i < nrElemente; i++)
	{
		printf("\nElementul %d:\n", i);
		afisare(vector[i]);
	}
}

struct pacient* copiazaPrimeleNElemente(struct pacient* vector, int nrElemente, int nrElementeCopiate)
{
	if (nrElementeCopiate > nrElemente)
	{
		nrElementeCopiate = nrElemente;
	}

	struct pacient* vectorNou = (struct pacient*)malloc(sizeof(struct pacient) * nrElementeCopiate);
	if (vectorNou == NULL)
	{
		return NULL;
	}

	for (int i = 0; i < nrElementeCopiate; i++)
	{
		vectorNou[i] = initializare(
			vector[i].id,
			vector[i].nume,
			vector[i].varsta,
			vector[i].costTratament
		);
	}

	return vectorNou;
}

void copiazaAnumiteElemente(struct pacient* vector, int nrElemente, float prag, struct pacient** vectorNou, int* dimensiune)
{
	*dimensiune = 0;

	for (int i = 0; i < nrElemente; i++)
	{
		if (vector[i].costTratament > prag)
		{
			(*dimensiune)++;
		}
	}

	if (*dimensiune == 0)
	{
		*vectorNou = NULL;
		return;
	}

	*vectorNou = (struct pacient*)malloc(sizeof(struct pacient) * (*dimensiune));
	if (*vectorNou == NULL)
	{
		*dimensiune = 0;
		return;
	}

	int k = 0;
	for (int i = 0; i < nrElemente; i++)
	{
		if (vector[i].costTratament > prag)
		{
			(*vectorNou)[k] = initializare(
				vector[i].id,
				vector[i].nume,
				vector[i].varsta,
				vector[i].costTratament
			);
			k++;
		}
	}
}

struct pacient getPrimulElementConditionat(struct pacient* vector, int nrElemente, const char* conditie)
{
	for (int i = 0; i < nrElemente; i++)
	{
		if (strcmp(vector[i].nume, conditie) == 0)
		{
			return initializare(
				vector[i].id,
				vector[i].nume,
				vector[i].varsta,
				vector[i].costTratament
			);
		}
	}

	return initializare(-1, "", 0, 0);
}

void dezalocare(struct pacient** vector, int* nrElemente)
{
	if (*vector != NULL)
	{
		for (int i = 0; i < *nrElemente; i++)
		{
			free((*vector)[i].nume);
		}

		free(*vector);
	}

	*vector = NULL;
	*nrElemente = 0;
}

int main()
{
	int nrElemente = 4;
	struct pacient* vector = (struct pacient*)malloc(sizeof(struct pacient) * nrElemente);

	if (vector == NULL)
	{
		printf("Eroare la alocarea memoriei.\n");
		return 1;
	}

	vector[0] = initializare(1, "Ion", 65, 1200.0f);
	vector[1] = initializare(2, "Maria", 45, 800.0f);
	vector[2] = initializare(3, "Andrei", 70, 1500.0f);
	vector[3] = initializare(4, "Elena", 55, 600.0f);

	printf("Vectorul initial:\n");
	afisareVector(vector, nrElemente);

	struct pacient* primele2 = copiazaPrimeleNElemente(vector, nrElemente, 2);
	int nrPrimele2 = 2;

	printf("\n\nPrimele 2 elemente copiate:\n");
	if (primele2 != NULL)
	{
		afisareVector(primele2, nrPrimele2);
	}

	struct pacient* vectorFiltrat = NULL;
	int dimensiuneNoua = 0;

	copiazaAnumiteElemente(vector, nrElemente, 1000.0f, &vectorFiltrat, &dimensiuneNoua);

	printf("\n\nPacientii cu costTratament > 1000:\n");
	if (vectorFiltrat != NULL)
	{
		afisareVector(vectorFiltrat, dimensiuneNoua);
	}
	else
	{
		printf("Nu exista pacienti care respecta conditia.\n");
	}

	struct pacient pGasit = getPrimulElementConditionat(vector, nrElemente, "Maria");

	printf("\n\nPrimul pacient gasit dupa nume:\n");
	afisare(pGasit);

	dezalocare(&vector, &nrElemente);
	dezalocare(&primele2, &nrPrimele2);
	dezalocare(&vectorFiltrat, &dimensiuneNoua);

	free(pGasit.nume);

	return 0;
}