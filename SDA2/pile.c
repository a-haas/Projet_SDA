#include <stdio.h>
#include <stdlib.h>

#include "pile.h"

Pile *adjonctionTetePile(Pile *p,int nb)
{
	if(p==NULL)
	{
		p = (Pile*)malloc(sizeof(Pile));
		p->nombre = nb;
		p->suiv = NULL;
		return p;
	}
	else
	{
		Pile *p1 = (Pile*)malloc(sizeof(Pile));
		p1->nombre = nb;
		p1->suiv = p;
		return p1;
	}
}

Pile *suppressionTetePile(Pile *p)
{
	if(p==NULL)
	{
		return NULL;
	}
	else
	{
		Pile *p1 = p->suiv;
		free(p);
		return p1;
	}
}

void afficherPile(Pile *p)
{
	Pile *p1 = p;
	if(p==NULL)
	{
		printf("La pile est vide.\n");
	}
	else
	{
		printf("La pile contient:\n");
		while(p1!=NULL)
		{
			printf("%d\n",p1->nombre);
			p1 = p1->suiv;
		}
	}
}

Pile *remplissagePile(int compteur)
{
	Pile *p = NULL;
	int resultat = compteur;
	while(resultat>1)
	{
		//printf("Nombre %d\n",resultat);
		p = adjonctionTetePile(p,resultat%2);
		resultat = resultat/2;
	}
	return p;
}