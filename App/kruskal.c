#include <stdio.h>
#include <stdlib.h>
#ifdef TASBINAIRE
#include "tasBinaire.h"
#endif
#ifdef MERGESORT
#include "merge_sort.h"
#endif
#include "graphe.h"

Graphe kruskal(Graphe g)
{
	if(g==NULL)
	{
		printf("Graphe non initialise.\n");
		return NULL;
	}
	if(g->listeNoeuds==NULL)
	{
		printf("Il n'y a pas de noeuds dans le graphe.\n");
		return NULL;
	}
	Graphe g1 = newGraphe();
	/*Initialisation des arcs*/
	Priority_queue t = creerPQ();
	Noeud n = g->listeNoeuds;
	Arc a = NULL;
	int i = 1;
	while(n!=NULL)
	{
		ajouterNoeud(g1,n->id,i);
		i++;
		a = n->listeArcs;
		while(a!=NULL)
		{
			ajouterArcPQ(t,a);
			a = a->aSuivant;
		}
		n = n->nSuivant;
	}
	t = tri(t);
	Arc min = extraction(t);
	Noeud pred,succ,n1;
	int compteur = 0;
	while((min!=NULL)&&(compteur<g->nbNoeuds-1))
	{
		//printf("Traitement de l'arc %d et %d\n",min->pred,min->succ);
		pred = trouveNoeud(g1,min->pred);
		succ = trouveNoeud(g1,min->succ);
		//printf("Avec comme flags %d %d\n",pred->flag,succ->flag);
		int temp,temp2;
		if(pred->flag!=succ->flag)
		{
			//printf("Les flags de %d et %d sont differents\n",min->pred,min->succ);
			compteur++;
			ajouterArc(g1,min->pred,min->poids,min->succ);
			if(pred->flag<succ->flag)
			{
				temp = pred->flag;
				temp2 = succ->flag;
				pred->flag = succ->flag;
			}
			else if(pred->flag>succ->flag)
			{
				temp = succ->flag;
				temp2 = pred->flag;
				succ->flag = pred->flag;
			}
			n1 = g1->listeNoeuds;
			while(n1!=NULL)
			{
				if(n1->flag==temp)
				{
					n1->flag = temp2;
				}
				n1 = n1->nSuivant;
			}
/*			printf("Mise a jour\n");
*/			n1 = g1->listeNoeuds;
			while(n1!=NULL)
			{
				//printf("Noeud %d flag %d\n",n1->id,n1->flag);
				n1 = n1->nSuivant;
			}
		}
		min = extraction(t);
	}
	//supprimerPQ(t);
	//printf("Le compteur est egal a %d\n",compteur);
	return g1;
}