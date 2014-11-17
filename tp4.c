#include <stdio.h>
#include <stdlib.h>



typedef struct tas_binaire{
	int racine;
	struct tas_binaire* ag;
	struct tas_binaire* ad;
}Noeud,*Tas;

typedef struct tete{
	int compteur;
	Tas t;	
}*Tete;

typedef struct pile{
	int val;
	struct pile* suiv;
}*Pile;

Pile creerPile()
{
	Pile p = (Pile)malloc(sizeof(struct pile));
	p->suiv = NULL;
	p->val = 0;
	return p;
}

Pile adjonctionTete(Pile p, int val)
{
	Pile p1 = creerPile();
	p1->suiv = p;
	p1->val = val;
	return p1;
}

Pile retirerTete(Pile p){
	Pile p1 = creerPile();
	if(p == NULL){
		return NULL;
	}
	else{
		p1 = p->suiv;
		free(p);
		return p1;
	}
}

int tete(Pile p)
{
	if(p==NULL)
	{
		printf("Pile vide.\n");
		return -1;
	}
	else
	{
		return p->val;
	}
}

Noeud creerNoeud(int racine)
{
	Noeud n;
	n.racine = racine;
	return n;
}

Tas parcours(Tete t){
	int cpt = t->compteur;
	Tas tas = t->t;
	Pile p = creerPile();
	int val;
	while(cpt != 1){
		cpt = cpt/2;
		adjonctionTete(p, cpt);
	}
	while(p->suiv != NULL){
		val = tete(p);
		p = retirerTete(p);
		if(p->val%2 == 0){
			tas = tas->ag;
		}
		else
			tas = tas->ad;
	}
	return tas;
}

int main(){
	Tete t = (Tete)malloc(sizeof(struct tete));
	t->compteur = 0;	
	return 0;
}