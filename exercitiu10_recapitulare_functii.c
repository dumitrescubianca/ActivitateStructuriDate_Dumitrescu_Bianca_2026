#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct pantof
{
	int id;
	float pret;
	float marime;
	char* caracteristica;
};

struct pantof initializare(int id, float pret, float marime, char* caracteristica)
{
	struct pantof p;
	p.id = id;
	p.pret = pret;
	p.marime = marime;
	p.caracteristica = (char*)malloc(strlen(caracteristica) + 1);
		strcpy_s(p.caracteristica, strlen(caracteristica) + 1, caracteristica);
	return p;
}
void afisare(struct pantof p)
{
	printf("ID:%d\n", p.id);
	printf("pret:%.2f\n", p.pret);
	printf("marime:%.2f\n", p.marime);
	printf("caracteristica:%s\n", p.caracteristica);

}
void modifica_Atribut(struct pantof* p)
{
	p->pret=p->pret - 60.50;

}
void dezalocare(struct pantof* p)
{
	free(p->caracteristica);
}

int main()
{
	struct pantof p;
	p = initializare(1, 250, 36.5, "toc");
	afisare(p);
	modifica_Atribut(&p);
	printf("\nDupa reducere : \n");
	afisare(p);
	dezalocare(&p);
	return 0;
	

}

