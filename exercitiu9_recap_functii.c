#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct masina
{
	int id;
	char* marca;
	float pret;
};

struct masina initializare(int id, char* marca, float pret)
{
	struct masina m;
	m.id = id;
	m.marca = (char*)malloc(strlen(marca) + 1);
		strcpy_s(m.marca,strlen(marca) + 1, marca);
		
	m.pret = pret;

	return m;

}

void afisare(struct masina m)
{
	printf("ID:%d\n", m.id);
	printf("marca:%s\n", m.marca);
	printf("pret:%.2f\n",m.pret);
}
void modificaAtribut(struct masina* m)
{
	m->pret = m->pret + 2500;
}
void dezalocare(struct masina* m)
{
	free(m->marca);

}

int main()
{
	struct masina m;
	m = initializare (1, "BMW", 17000);
	afisare(m);
	modificaAtribut(&m);
	printf("\nDupa scumpire:\n");
	afisare(m);
	dezalocare(&m);


	return 0;
}