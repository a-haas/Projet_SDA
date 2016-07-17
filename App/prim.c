#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"

#ifdef MERGESORT
#include "merge_sort.h"
#endif
#include "prim.h"
#ifdef TASBINAIRE
#include "tasBinaire.h"
#endif
Graphe prim(Graphe g)
{
	printf("Structure de file de priorité :\n");
	#ifdef TASBINAIRE
	printf("Tri par tas binaire.\n");
	#endif

	#ifdef MERGESORT
	printf("Tri par merge sort.\n");
	#endif

	if(g == NULL)
	{
		printf("Graphe non initialise.\n");
		return NULL;
	}
	if(g->listeNoeuds == NULL)
	{
		printf("Pas de doigts, pas de chocolats.\n");
		return NULL;
	}
	Graphe g1 = newGraphe();
	Priority_queue t = creerPQ();
	if(g->listeNoeuds == NULL)
	{
		printf("Il n'y a pas de noeuds dans le graphe.\n");
	}
	Arc a = g->listeNoeuds->listeArcs;
	ajouterNoeud(g1,g->listeNoeuds->id,0);

	while(a!=NULL)
	{
		ajouterArcPQ(t,a);
		a = a->aSuivant;
	}
	t = tri(t);
	while((g1->nbNoeuds<g->nbNoeuds)&&(t!=NULL))
	{
		Arc min = extraction(t);
		while((min!=NULL)&&(noeudExiste(g1,min->succ)==1))
		{
			min = extraction(t);
		}
		if(min==NULL)
		{
			printf("Graphe non connexe, retour d'une composante connexe du graphe.\n");
			supprimerPQ(t);
			return g1;	
		}
		ajouterArc(g1,min->pred,min->poids,min->succ);
		Noeud n = g->listeNoeuds;
		while(n->id!=min->succ)
		{
			n = n->nSuivant;
		}
		a = n->listeArcs;
		while(a!=NULL)
		{
			ajouterArcPQ(t,a);
			a = a->aSuivant;
		}
		t = tri(t);
	}
	//supprimerPQ(t);
	return g1;
}