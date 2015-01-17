#include <stdio.h>
#include <stdlib.h>

#include "tasBinaire.h"
#include "pile.h"
#include "graphe.h"

Node *creerNode(Arc nb)
{
	Node *n = (Node*)malloc(sizeof(Node));
	n->a = nb;
	n->ag = NULL;
	n->ad = NULL;
	return n;
}

int valeurPoidsArc(Priority_queue t,int n)
{
	if(t==NULL)
	{
		printf("Priority_queue tn initialise.\n");
		return -1;
	}
	else if((n>t->compteur)||(n<1))
	{
		printf("Recherche du poids du noeud %d invalide.\n",n);
		return -1;
	}
	else if(n==1)
	{
		return t->racine->a->poids;
	}
	else
	{
		Pile *p = remplissagePile(n);
		Node *n1 = t->racine;
		while(p!=NULL)
		{
			if(p->nombre == 0)
			{
				n1 = n1->ag;
			}
			else
			{
				n1 = n1->ad;
			}
			p = suppressionTetePile(p);
		}
		return n1->a->poids;
	}
}

Arc valeurArc(Priority_queue t,int n)
{
	if(t==NULL)
	{
		printf("Priority_queue non initialise.\n");
		return NULL;
	}
	else if((n>t->compteur)||(n<1))
	{
		printf("Recherche du noeud %d invalide.\n",n);
		return NULL;
	}
	else if(n==1)
	{
		return t->racine->a;
	}
	else
	{
		Pile *p = remplissagePile(n);
		Node *n1 = t->racine;
		while(p!=NULL)
		{
			if(p->nombre == 0)
			{
				n1 = n1->ag;
			}
			else
			{
				n1 = n1->ad;
			}
			p = suppressionTetePile(p);
		}
		return n1->a;
	}
}

Priority_queue creerPQ()
{
	Priority_queue t = (Priority_queue)malloc(sizeof(strPriority_queue));
	t->racine = NULL;
	t->compteur = 0;
	return t;
}

void supprimerPQ(Priority_queue t)
{
	while(t->compteur>0)
	{
		supprimerDernierNodeTas(t);
	}
	free(t);
}

/*PAS TRIE*/
Priority_queue ajouterNodeTas(Priority_queue t,Arc nb)
{
	//printf("Ajout de l'arc de predecesseur %d de successeur %d et de poids %d\n",nb->pred,nb->succ,nb->poids);
	//printf("Le compteur est egal a %d\n",t->compteur);
	Node *n = NULL;
	Pile *p = NULL;
	Node *n1;
	if(t == NULL)
	{
		printf("Il faut creer le tas avant d'y ajouter le noeud.\n");
		return NULL;
	}
	else if(t->compteur == 0)
	{
		//printf("Ajout a la racine.\n");
		n = creerNode(nb);
		t->racine = n;
		t->compteur++;
		return t;
	}
	else
	{
		n1 = t->racine;
		t->compteur++;
		p = remplissagePile(t->compteur);
		while(p->suiv!=NULL)
		{
			if(p->nombre==0)
			{
				n1 = n1->ag;
			}
			else
			{
				n1 = n1->ad;
			}
			p = suppressionTetePile(p);
		}
		n = creerNode(nb);
		if(p->nombre==0)
		{
			n1->ag = n;
		}
		else
		{
			n1->ad = n;
		}
		p = suppressionTetePile(p);
		return t;
	}
}

Priority_queue echangeEtiquettes(Priority_queue t,int num1, int num2)
{
	if(t ==NULL)
	{
		printf("Priority_queue tn initialise.\n");
		return t;
	}
	else if((num1<1)||(num2<1)||(num1>t->compteur)||(num2>t->compteur))
	{
		printf("Echange impossible, recherche d'un des deux noeuds %d %d impossible.\n",num1,num2);
		return t;
	}
	else
	{
		//printf("Echange des noeuds %d et %d.\n",num1,num2);
		Pile *p1,*p2;
		Node *n1,*n2;
		n1 = t->racine;
		n2 = t->racine;
		p1 = remplissagePile(num1);
		p2 = remplissagePile(num2);
		while(p1!=NULL)
		{
			if(p1->nombre==0)
			{
				n1 = n1->ag;
			}
			else
			{
				n1 = n1->ad;
			}
			p1 = suppressionTetePile(p1);
		}
		while(p2!=NULL)
		{
			if(p2->nombre==0)
			{
				n2 = n2->ag;
			}
			else
			{
				n2 = n2->ad;
			}
			p2 = suppressionTetePile(p2);
		}
		Arc temp = n1->a;
		n1->a = n2->a;
		n2->a = temp;
	}
	return t;
}

Priority_queue ajouterArcPQ(Priority_queue t,Arc nb)
{
	int fils,pere;
	t = ajouterNodeTas(t,nb);
	if(t->compteur>1)
	{
		fils = t->compteur;
		pere = fils/2;
		/*Percolate up*/
		//while((pere>0)&&(valeurNoeud(t,fils)>valeurNoeud(t,pere)))
		while((pere>0)&&(valeurPoidsArc(t,fils)<valeurPoidsArc(t,pere)))
		{
			echangeEtiquettes(t,fils,pere);
			fils = pere;
			pere = fils/2;
		}
	}
	return t;
}

void supprimerNode(Node *n)
{
	if(n==NULL)
	{
		printf("Noeud deja supprime.\n");
	}
	else
	{
		//printf("Suppression du noeud dont la valeur est %d.\n",n->etiquette);
		free(n);
	}
}

Priority_queue supprimerDernierNodeTas(Priority_queue t)
{
	Pile *p;
	if(t==NULL)
	{
		printf("Priority_queue texistant.\n");
		return NULL;
	}
	else
	{
		Node *n1 = t->racine;
		if(t->compteur==1)
		{
			supprimerNode(n1);
			t->compteur--;
			printf("Dernier noeud.\n");
			return t;
		}
		else
		{
			p = remplissagePile(t->compteur);
			while(p->suiv!=NULL)
			{
				if(p->nombre==0)
				{
					n1 = n1->ag;
				}
				else
				{
					n1 = n1->ad;
				}
				p = suppressionTetePile(p);
			}
			if(p->nombre==0)
			{
				supprimerNode(n1->ag);
			}
			else
			{
				supprimerNode(n1->ad);
			}
			p = suppressionTetePile(p);
			t->compteur--;
		}
		return t;
	}
}

Arc extraction(Priority_queue t)
{
	if(t == NULL)
	{
		printf("Priority_queue tn initialise.\n");
		return NULL;
	}
	else if(t->compteur==0)
	{
		printf("extraction du maximum impossible : tas vide.\n");
		return NULL;
	}
	else
	{
		Arc valeur = t->racine->a;
		t->racine->a = valeurArc(t,t->compteur);
		supprimerDernierNodeTas(t);
		
		if(t->compteur>0)
		{
			int pere,filsg,filsd;
			pere = 1;
			filsg = 2;
			filsd = 3;
			//while(((filsg<=t->compteur)&&(filsd<=t->compteur)&&((valeurNoeud(t,pere)<valeurNoeud(t,filsg))||(valeurNoeud(t,pere)<valeurNoeud(t,filsd))))||((filsg<=t->compteur)&&(valeurNoeud(t,pere)<valeurNoeud(t,filsg))))
			while(((filsg<=t->compteur)&&(filsd<=t->compteur)&&((valeurPoidsArc(t,pere)>valeurPoidsArc(t,filsg))||(valeurPoidsArc(t,pere)>valeurPoidsArc(t,filsd))))||((filsg<=t->compteur)&&(valeurPoidsArc(t,pere)>valeurPoidsArc(t,filsg))))
			{
				if(filsd<=t->compteur)
				{
					//if(valeurNoeud(t,filsg)>valeurNoeud(t,filsd))
					if(valeurPoidsArc(t,filsg)<valeurPoidsArc(t,filsd))
					{
						echangeEtiquettes(t,pere,filsg);
						pere = filsg;
					}
					else
					{
						echangeEtiquettes(t,pere,filsd);
						pere = filsd;
					}
					filsg = pere*2;
					filsd = (pere*2)+1;
				}
				else
				{ 
					echangeEtiquettes(t,pere,filsg);
					pere = filsg;
					filsg = pere*2;
					filsd = (pere*2)+1;
				}
			}
		}
		//printf("La valeur retournee est %d\n",valeur);
		return valeur;
	}
}

void affichePQ(Priority_queue t)
{
	if(t == NULL)
	{
		printf("Priority_queue tn initialise.\n");
	}
	else
	{
		printf("Le tas est compose de\n");
		int i = 1;
		while(i<=t->compteur)
		{
			Node *n = t->racine;
			Pile *p = NULL;
			p = remplissagePile(i);
			while(p!=NULL)
			{
				if(p->nombre == 0)
				{
					n = n->ag;
				}
				else
				{
					n = n->ad;
				}
				p = suppressionTetePile(p);
			}
			printf("Noeud %d: Arc %d %d de poids %d\n",i,n->a->pred,n->a->succ,n->a->poids);
			i++;
		}
	}
}

TableauRange *rangerTableau(Priority_queue t)
{
	if(t==NULL)
	{
		printf("Erreur tas donne en parametre non initialise.\n");
		return NULL;
	}
	else
	{
		TableauRange *tr = (TableauRange*)malloc(sizeof(TableauRange));
		tr->tableau = (Arc*)malloc((t->compteur)*sizeof(Arc));
		tr->compteur = 0;
		int i = 0;
		while(t->compteur>0)
		{
			tr->tableau[i] = extraction(t);
			i++;
			tr->compteur++;
		}
		return tr;
	}
}

void afficheTableauRange(TableauRange *tr)
{
	if(tr == NULL)
	{
		printf("Erreur tableau non initialise.\n");
	}
	else
	{
		int i;
		printf("Le tableau range donne :\n");
		for(i = 0;i<tr->compteur;i++)
		{
			printf("%d %d de poids %d\n",tr->tableau[i]->pred,tr->tableau[i]->succ,tr->tableau[i]->poids);
		}
		printf("\n");
	}
}

void supprimerTableauRange(TableauRange *tr)
{
	if(tr!=NULL)
	{
		if(tr->tableau!=NULL)
		{
			free(tr->tableau);
		}
		free(tr);
	}
}

Priority_queue tri(Priority_queue t)
{
	return t;
}