#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"

/*Cree un noeud et renvoie son pointeur*/
Noeud creerNoeud(int id,int flag)
{
	Noeud n = (Noeud)malloc(sizeof(strNoeud));
	n->id = id;
	n->flag = flag;
	n->nSuivant = NULL;
	n->listeArcs = NULL;
	return n;
}

/*Supprime un noeud*/
void supprimerNoeud(Noeud n)
{
	if(n!=NULL)
	{
		free(n);
	}
	else
	{
		printf("Free NULL\n");
	}
}

/*Cree un arc et renvoie son pointeur*/
Arc creerArc(int pred, int poids, int succ)
{
	Arc a = (Arc)malloc(sizeof(strArc));
	a->pred = pred;
	a->poids = poids;
	a->succ = succ;
	a->aSuivant = NULL;
	return a;
}

/*Supprime un arc*/
void supprimerArc(Arc a)
{
	if(a!=NULL)
	{
		free(a);
	}
	else
	{
		printf("WTF\n");
	}
}

/*Ajoute un arc a la liste des arcs adjacents*/
Arc ajouterArcListe(Arc l,Arc a)
{
	if(l==NULL)
	{
		return a;
	}
	else
	{
		Arc temp = l;
		while(temp->aSuivant != NULL)
		{
			if(temp->succ == a->succ)
			{
				temp->poids = a->poids;
				supprimerArc(a);
				return l;
			}
			temp = temp->aSuivant;
		}
		if(temp->succ==a->succ)
		{
			temp->poids = a->poids;
			supprimerArc(a);
			return l;
		}
		temp->aSuivant = a;
		return l;
	}
}

/*Supprime un arc de la liste des arcs adjacents a un noeud*/
Arc supprimerArcListe(Arc l, int succ)
{
	if(l == NULL)
	{
		return NULL;
	}
	if(l->succ == succ)
	{
		Arc temp = l->aSuivant;
		supprimerArc(l);
		temp = supprimerArcListe(temp,succ);
		return temp;
	}
	else
	{
		l->aSuivant = supprimerArcListe(l->aSuivant,succ);
		return l;
	}
}

/*Supprime toute la liste des arcs adjacents a un noeud, pour la suppression d'un noeud du graphe*/
Arc supprimerListeArcs(Arc l)
{
	Arc temp = l;
	Arc tempNext = NULL;
	while(temp != NULL)
	{
		tempNext = temp->aSuivant;
		supprimerArc(temp);
		temp = tempNext;
	}
	return NULL;
}

/*Initialisation d'un graphe.*/
Graphe newGraphe()
{
	Graphe g = (Graphe)malloc(sizeof(strGraphe));
	g->listeNoeuds = NULL;
	g->nbNoeuds = 0;
	return g;
}

/*Ajoute un noeud au graphe.*/
void ajouterNoeud(Graphe g, int id,int flag)
{
	Noeud n = NULL;
	Noeud n1 = NULL;
	if(g==NULL)
	{
		printf("Graphe non initialise.\n");
		return;
	}
	n = g->listeNoeuds;
	if(n==NULL)
	{
		n1 = creerNoeud(id,flag);
		g->listeNoeuds = n1;
	}
	else
	{
		if(n->id==id)
		{
			return;
		}
		while(n->nSuivant!=NULL)
		{
			if(n->id==id)
			{
				return;
			}
			n = n->nSuivant;
		}
		if(n->id==id)
		{
			return;
		}
		n1 = creerNoeud(id,flag);
		n->nSuivant = n1;
	}
	g->nbNoeuds++;
}

/*Ajoute un arc au graphe, et si besoin ajoute les noeuds dont il a besoin.*/
void ajouterArc(Graphe g,int pred,int poids,int succ)
{
	Noeud n = NULL;
	if(g == NULL)
	{
		printf("Graphe non initialise.\n");
		return;
	}
	ajouterNoeud(g,pred,0);
	ajouterNoeud(g,succ,0);

	n = g->listeNoeuds;
	while(n != NULL)
	{
		if(n->id == pred)
		{
			Arc a1 = creerArc(pred,poids,succ);
			n->listeArcs = ajouterArcListe(n->listeArcs,a1);
		}
		n = n->nSuivant;
	}
}

/*Supprime un arc du graphe*/
void supprimerArcGraphe(Graphe g, int pred, int succ)
{
	if(g == NULL)
	{
		printf("Graphe non initialise.\n");
		return;
	}
	Noeud n = g->listeNoeuds;
	while(n!=NULL)
	{
		if(n->id == pred)
		{
			n->listeArcs = supprimerArcListe(n->listeArcs,succ) ;
		}
		n = n->nSuivant;
	}
}

int noeudExiste(Graphe g,int id)
{
	Noeud n = NULL;
	if(g == NULL)
	{
		printf("Graphe non initialise.\n");
		return -1;
	}
	n = g->listeNoeuds;
	while(n!=NULL)
	{
		if(n->id == id)
		{
			return 1;
		}
		n = n->nSuivant;
	}
	return 0;
}

Noeud trouveNoeud(Graphe g,int id)
{
	Noeud n = NULL;
	if(g == NULL)
	{
		printf("Graphe non initialise.\n");
		return NULL;
	}
	n = g->listeNoeuds;
	while(n!=NULL)
	{
		if(n->id == id)
		{
			return n;
		}
		n = n->nSuivant;
	}
	printf("Noeud non trouve.\n");
	return NULL;
}

/*Supprime un noeud du graphe, ainsi que la liste des arcs dont il est le predecesseur*/
/******************************************************Ne supprime pas encore les arcs qui en dependent*********************************************************/
void supprimerNoeudGraphe(Graphe g,int id)
{
	if(g == NULL)
	{
		printf("Graphe non initialise.\n");
		return;
	}
	if(g->listeNoeuds==NULL)
	{
		return;
	}
	Noeud n = NULL;
	if(g->listeNoeuds->id == id)
	{
		n = g->listeNoeuds->nSuivant;
		g->listeNoeuds->listeArcs = supprimerListeArcs(g->listeNoeuds->listeArcs);
		supprimerNoeud(g->listeNoeuds);
		g->listeNoeuds = n;
		g->nbNoeuds--;
	}
	else
	{
		Noeud next = NULL;
		n = g->listeNoeuds;
		next = n->nSuivant;
		while(next!=NULL)
		{
			if(next->id == id)
			{
				n->nSuivant = next->nSuivant;
				next->listeArcs = supprimerListeArcs(next->listeArcs);
				supprimerNoeud(next);
				g->nbNoeuds--;
			}
			n = n->nSuivant;
			next = n->nSuivant;
		}
		n = g->listeNoeuds;
		while(n!=NULL)
		{
			supprimerArcGraphe(g,n->id,id);
			n = n->nSuivant;
		}
	}
}

void supprimerGraphe(Graphe g)
{
	if(g!=NULL)
	{
		while(g->listeNoeuds!=NULL)
		{
			supprimerNoeudGraphe(g,g->listeNoeuds->id);
		}
		free(g);
	}
}

/*Affice le graphe*/
void afficherGraphe(Graphe g)
{
	Noeud n = NULL;
	Arc a = NULL;
	if(g==NULL)
	{
		printf("Graphe non initialise.\n");
	}
	else
	{
		n = g->listeNoeuds;
		while(n!=NULL)
		{
			if(n->listeArcs==NULL)
			{
				printf("Le noeud %d n'a pas de successeurs.\n",n->id);
			}
			else
			{
				a = n->listeArcs;
				printf("Le noeud %d a pour successeurs\n",n->id);
				while(a!=NULL)
				{
					printf("le noeud %d.\n",a->succ);
					a = a->aSuivant;
				}
			}
			n = n->nSuivant;
		}
	}
}

/*int main()
{
	Graphe g = newGraphe();
	ajouterArc(g,10,12,4);
	ajouterArc(g,15,12,1);
	ajouterArc(g,15,12,1);
	ajouterArc(g,1,12,1);
	ajouterArc(g,3,12,2);
	ajouterArc(g,8,12,3);
	ajouterArc(g,13,12,2);
	supprimerNoeudGraphe(g,2);
	afficherGraphe(g);
	supprimerGraphe(g);
	return 1;
}*/