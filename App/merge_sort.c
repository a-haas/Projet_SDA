#include <stdio.h>
#include <stdlib.h>

#include "graphe.h"
#include "merge_sort.h"

void print_liste(Priority_queue l){
 while(l != NULL){
 	print_bloc(l->bloc);
 	l = l->suiv;
 	}
	printf("------Fin print_liste------\n");
}


void print_bloc(Bloc b){
	while(b != NULL){
		printf("%d %d %d\n",b->arc->pred,b->arc->poids,b->arc->succ);
		b = b->suiv;
	}
	printf("------Fin print_bloc------\n");
}

Arc extraction(Priority_queue t){
 if(t == NULL){
  return NULL;
 }

 if(t->bloc != NULL){
  Arc res = t->bloc->arc;
  Bloc temp = t->bloc->suiv;
  t->bloc = temp;
  return res;
 }
 else{
  return NULL;
 }
}

Priority_queue creerPQ(){
	Priority_queue liste = malloc(sizeof(struct liste));
	liste->bloc = creerBloc();
	return liste;
}

Bloc creerBloc(){
	Bloc bloc = malloc(sizeof(struct bloc));
	return bloc;
}

void supprimerBloc(Bloc b){
	supprimerListeArcs(b->arc);
	free(b);
}

void supprimerListeBlocs(Bloc b){
	supprimerListeArcs(b->arc);
	Bloc temp = b;
	Bloc tempNext = NULL;
	while(temp != NULL)
	{
		tempNext = temp->suiv;
		supprimerListeArcs(temp->arc);
		supprimerBloc(temp);
		temp = tempNext;
	}
}

void supprimerListePQ(Priority_queue t){
	Priority_queue temp = t;
	Priority_queue tempNext = NULL;
	while(temp != NULL)
	{
		tempNext = temp->suiv;
		supprimerListeBlocs(temp->bloc);
		supprimerPQ(temp);
		temp = tempNext;
	}
}

void supprimerPQ(Priority_queue t){
	supprimerBloc(t->bloc);
	free(t);
}

void ajouterArcPQ(Priority_queue t, Arc nb){
	if(t->bloc->arc == NULL){
		t->bloc->arc = nb;
	}
	else{
		Priority_queue pq = creerPQ();
		pq->suiv = t->suiv;
		pq->bloc->arc = nb;
		t->suiv = pq;
	}
}

void tri_bloc(Priority_queue l1, Priority_queue l2, Priority_queue l){
	if(l2 == NULL){
		l->bloc = malloc(sizeof(struct bloc));
		l->bloc->arc = l1->bloc->arc;
		l->bloc->suiv = l1->bloc->suiv;
		l->suiv = l1->suiv;
	}
	else{
		Bloc b1 = l1->bloc;
		Bloc b2 = l2->bloc;
		l->bloc = malloc(sizeof(struct bloc));
		Bloc b = l->bloc;
		int flag = 0;
		while((b1 != NULL || b2 != NULL) && flag == 0){
			
			if(b1 == NULL){
				b->arc = b2->arc;
				b->suiv = b2->suiv;
				flag = 1;
			}
			else if(b2 == NULL){
				b->arc = b1->arc;
				b->suiv = b1->suiv;
				flag = 1;
			}
			else if(b1->arc->poids <= b2->arc->poids){
				b->arc = b1->arc;
				b1 = b1->suiv;
				b->suiv = malloc(sizeof(struct bloc));
				b = b->suiv;
			}
			else{
				b->arc = b2->arc;
				b2 = b2->suiv;
				b->suiv = malloc(sizeof(struct bloc));
				b = b->suiv;
			}
		}
	}
}

Priority_queue tri(Priority_queue liste){
	if(liste->suiv == NULL){
		return liste;
	}
	Priority_queue l;
	l = malloc(sizeof(struct liste));
	Priority_queue tete = l;
	Priority_queue l1;
	Priority_queue l2;
	while(liste != NULL){
		l1 = liste;
		l2 = liste->suiv;
		tri_bloc(l1, l2, l);
		if(l2 == NULL)
			liste = liste->suiv;
		else
			liste = liste->suiv->suiv;
		if(liste != NULL){
			l->suiv = malloc(sizeof(struct liste));
			l = l->suiv;
		}
	}
	supprimerListePQ(liste);
	return tri(tete);
}

/*int main(){
	
	//Allocations blocs
	Bloc b1 = malloc(sizeof(struct bloc));
	Bloc b2 = malloc(sizeof(struct bloc));
	Bloc b3 = malloc(sizeof(struct bloc));
	Bloc b4 = malloc(sizeof(struct bloc));	
	Bloc b5 = malloc(sizeof(struct bloc));
	
	//Allocation listes
	Priority_queue l1 = malloc(sizeof(struct liste));
	Priority_queue l2 = malloc(sizeof(struct liste));
	Priority_queue l3 = malloc(sizeof(struct liste));
	Priority_queue l4 = malloc(sizeof(struct liste));
	Priority_queue l5 = malloc(sizeof(struct liste));
	
	//Allocation sommets
	Noeud n1 = creerNoeud(1);
	Noeud n2 = creerNoeud(2);
	Noeud n3 = creerNoeud(3);
	Noeud n4 = creerNoeud(4);
	Noeud n5 = creerNoeud(5);

	//Allocation arcs
	Arc a1 = creerArc(1, 3, 2);
	Arc a2 = creerArc(2, 5, 3);
	Arc a3 = creerArc(3, 2, 4);
	Arc a4 = creerArc(4, 4, 5);
	Arc a5 = creerArc(5, 10,1);

	//Valuation blocs
	b1->arc = a1;
	b2->arc = a2;
	b3->arc = a3;
	b4->arc = a4;
	b5->arc = a5;

	//Association bloc liste
	l1->bloc = b1;
	l2->bloc = b2;
	l3->bloc = b3;
	l4->bloc = b4;
	l5->bloc = b5;

	//Chainage listes
	l1->suiv = l2;
	l2->suiv = l3;
	l3->suiv = l4;
	l4->suiv = l5;
	l5->suiv = NULL;
	
	cpt = 0;

	print_liste(l1);
	Priority_queue l = merge_sort(l1);
	print_bloc(l->bloc);

	printf("%d\n", cpt);
	return 0;
}*/