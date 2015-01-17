/**\file tasBinaire.h
 * \brief gestion du tas binaire (header)
 * 
 * */

#ifndef __TASBINAIRE_H
#define __TASBINAIRE_H

#include "pile.h"
#include "graphe.h"

/**\struct Noeud
 * */
typedef struct node{
	Arc a;/**La valeur du noeud*/
	struct node *ag;/**Le pointeur vers l'arbre gauche*/
	struct node *ad;/**Le pointeur vers l'arbre droit*/
}Node;

/**\struct Priority_queue
* */
typedef struct tas_binaire{
	Node *racine;/**Le noeud a la racine du tas*/
	int compteur;/**Le compteur de noeuds du tas*/
}*Priority_queue,strPriority_queue;
/**\struct TableauRange
 * \brief Le tableau range dans l'ordre du plus grand au plus petit.
 * */
typedef struct tableauRange{
	Arc *tableau;/**Un pointeur vers le tableau range d'elements*/
	int compteur;/**Le compteur d'elements du tableau*/
}TableauRange;


/**
 * \brief Cree un noeud a partir du poids du noeud.
 * \relatesalso Noeud
 * \param nb le poids du noeud.
 * \return Un pointeur vers le noeud cree.
 * */
Node *creerNode(Arc nb);

/**
 * \brief Renvoie le pointeur vers n-ieme noeud du tas 
 * \relatesalso Noeud
 * \param t le tas binaire.
 * \param n le numero du noeud dont on veut la valeur, la numerotation
 * commence a 1.
 * \return La valeur du noeud sous forme d'entier.
 * */
Arc valeurArc(Priority_queue t,int n);

/**
 * \brief Renvoie le poids du n-ieme noeud du tas 
 * \relatesalso Noeud
 * \param t le tas binaire.
 * \param n le numero du noeud dont on veut la valeur, la numerotation
 * commence a 1.
 * \return La valeur du noeud sous forme d'entier.
 * */
int valeurPoidsArc(Priority_queue t,int n);

/**
 * \brief Creation de la structure de tas binaire et initialisation du
 * compteur de noeud a 0.
 * \relatesalso Priority_queue
* \return Un pointeur vers le tas cree.
 * */
Priority_queue creerPQ();

/**
 * \brief Supprime le tas. 
 * \relatesalso Priority_queue
* \param t le pointeur vers le tas que l'on veut supprimer.
 * */
void supprimerPQ(Priority_queue t);

/**
 * \brief Fonction auxiliaire a ajouterNoeudTasMax
 * Ajoute un noeud dans le tas a la premiere place disponible,ne se
 * preoccupe pas de ranger le tas binaire a ce stade.
 * \relatesalso Priority_queue
* \param t le tas binaire auquel on veut ajouter le noeud.
 * \param nb la valeur du noeud que l'on veut ajouter.
 * \return t le tas binaire avec le noeud ajoute a la premiere feuille
 * disponible.
 * */
Priority_queue ajouterNodeTas(Priority_queue t,Arc nb);

/**
 * \brief Ajoute un noeud dans le tas a la premiere place disponible,
 * puis effectue une permutation de ce noeud avec son pere tant que le
 * fils est superieur a son pere.
 * \relatesalso Priority_queue
* \param t le tas binaire auquel on veut ajouter le noeud.
 * \param nb la valeur du noeud que l'on veut ajouter.
 * \return t le tas binaire avec le noeud ajoute a la premiere feuille
 * disponible.
 * */
Priority_queue ajouterArcPQ(Priority_queue t,Arc nb);

/**
 * \brief Supprime un noeud.
 * \relatesalso Noeud
 * \param n le pointeur vers le noeud que l'on veut supprimer.
 * */
void supprimerNode(Node *n);

/**
 * \brief Supprime le dernier noed du tas et decremente le compteur de
 * noeuds du tas.
 * \relatesalso Priority_queue
* \param t le pointeur vers le tas dont on veut supprimer le dernier
 * noeud.
 * \return t le tas avec le dernier noeud supprime.
 * */
Priority_queue supprimerDernierNodeTas(Priority_queue t);

/**
 * \brief Extrait la racine( = max ) du tas binaire et le reorganise
 * pour garder un tas binaire range.
 * \relatesalso Priority_queue
* \param t le tas dont on veut le maximum.
 * \return la valeur du noeud de la racine du tas.
 * */
Arc extraction(Priority_queue t);

/**
 * \brief Affiche le tas binaire.
 * \relatesalso Priority_queue
* \param t le tas que l'on veut afficher.
 * \return
 * */
void affichePQ(Priority_queue t);

/**
 * \brief Cree et range le tableau du plus grand au plus petit.
 * \relatesalso TableauRange
 * \param t le tas que l'on veut trier.
 * \return Un tableau dont les elements sont ranges du plus grand au
 * plus petit.
 * */
TableauRange *rangerTableau(Priority_queue t);

/**
 * \brief Affiche le tableau.
 * \relatesalso TableauRange
 * \param tr le tableau que l'on veut afficher.
 * */
void afficheTableauRange(TableauRange *tr);

/**
 * \brief Supprime le tableau range.
 * \relatesalso TableauRange
 * \param tr le pointeur vers le tableau range que l'on veut supprimer.
 * */
void supprimerTableauRange(TableauRange *tr);

Priority_queue tri(Priority_queue t);//A FAIRE

#endif
