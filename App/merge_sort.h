#include "graphe.h"

#ifndef __TASBINAIRE_H
#define __TASBINAIRE_H

typedef struct bloc{
	Arc arc;
	struct bloc *suiv;
}*Bloc;

typedef struct liste{
	Bloc bloc;
	struct liste *suiv;
}*Priority_queue;

Arc extraction(Priority_queue t);

Priority_queue tri(Priority_queue t);

Priority_queue creerPQ();

void supprimerPQ(Priority_queue t);

void ajouterArcPQ(Priority_queue t, Arc a);

void print_bloc(Bloc b);

void print_liste(Priority_queue l);

Bloc creerBloc();

void supprimerBloc(Bloc b);

void supprimerListeBlocs(Bloc b);

void supprimerListePQ(Priority_queue t);


#endif