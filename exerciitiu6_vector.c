#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct carte
{
	int id;
	char* titlu;
	float pret;
};

struct carte initializare(int id, const char* titlu, float pret)
{
	struct carte c;
	c.id = id;
	c.titlu = NULL;
	c.pret = pret;

	c.titlu = (char*)malloc(strlen(titlu) + 1);
	if (c.titlu != NULL)
	{
		strcpy_s(c.titlu, strlen(titlu) + 1, titlu);
	}

	return c;
}

void afisare(struct carte c)
{
	printf("ID: %d\n", c.id);
	printf("Titlu: %s\n", c.titlu);
	printf("Pret: %.2f\n", c.pret);
}

void afisareVector(struct carte* vector, int nrElemente)
{
	for (int i = 0; i < nrElemente; i++)
	{
		printf("\nElementul %d:\n", i);
		afisare(vector[i]);
	}
}

void copiazaAnumiteElemente(struct carte* vector, int nrElemente, float prag, struct carte** vectorNou, int* dimensiune)
{
	*dimensiune = 0;

	for (int i = 0; i < nrElemente; i++)
	{
		if (vector[i].pret > prag)
		{
			(*dimensiune)++;
		}
	}

	if (*dimensiune == 0)
	{
		*vectorNou = NULL;
		return;
	}

	*vectorNou = (struct carte*)malloc(sizeof(struct carte) * (*dimensiune));

	int k = 0;
	for (int i = 0; i < nrElemente; i++)
	{
		if (vector[i].pret > prag)
		{
			(*vectorNou)[k] = initializare(vector[i].id, vector[i].titlu, vector[i].pret);
			k++;
		}
	}
}

void dezalocare(struct carte** vector, int* nrElemente)
{
	if (*vector != NULL)
	{
		for (int i = 0; i < *nrElemente; i++)
		{
			free((*vector)[i].titlu);
		}
		free(*vector);
	}

	*vector = NULL;
	*nrElemente = 0;
}

int main()
{
	int nrElemente = 4;
	struct carte* vector = (struct carte*)malloc(sizeof(struct carte) * nrElemente);

	vector[0] = initializare(1, "Ion", 35.0f);
	vector[1] = initializare(2, "Morometii", 42.5f);
	vector[2] = initializare(3, "Baltagul", 28.0f);
	vector[3] = initializare(4, "Enigma Otiliei", 50.0f);

	printf("Vector initial:\n");
	afisareVector(vector, nrElemente);

	struct carte* vectorFiltrat = NULL;
	int dimensiuneNoua = 0;

	copiazaAnumiteElemente(vector, nrElemente, 30.0f, &vectorFiltrat, &dimensiuneNoua);

	printf("\nCartile cu pret > 30:\n");
	afisareVector(vectorFiltrat, dimensiuneNoua);

	dezalocare(&vector, &nrElemente);
	dezalocare(&vectorFiltrat, &dimensiuneNoua);

	return 0;
}