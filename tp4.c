#include <stdio.h>
#include <stdlib.h>

typedef struct tas_binaire{
	int racine;
	struct tas_binaire* ag;
	struct tas_binaire* ad;
	static int compteur = 0;
}Noeud,*Tas;

Noeud creerNoeud(int racine)
{
	Noeud n;
	n.racine = racine;
	return n;
}

