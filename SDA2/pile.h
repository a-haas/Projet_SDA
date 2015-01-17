/**\file pile.h
 * \brief gestion de la pile servant a connaitre le chemin pour acceder
 * au noeud du tas desire (header)
 * 
 * */

#ifndef __PILE_H
#define __PILE_H

typedef struct pile{
	int nombre;
	struct pile *suiv;
}Pile;

/**
 * \brief Si la pile n'existe pas, cree la pile et ajoute le noeud a la
 * tete de la pile
 * \relatesalso Pile
 * \param p la pile de nombres.
 * \param nb le nombre que l'on veut ajouter a la pile, normalement
 * seulement 0 ou 1.
 * \return Un pointeur vers la pile avec l'element ajoute en tete.
 * */
Pile *adjonctionTetePile(Pile *p,int nb);

/**
 * \brief Supprime le premier element de la pile.
 * \relatesalso Pile
 * \param p la pile dont on veut supprimer le premier element.
 * \return Un pointeur vers la pile avec l'element en tete supprime.
 * */
Pile *suppressionTetePile(Pile *p);

/**
 * \brief Cree la pile contenant le chemin pour aller au noeud grace a
 * l'ajout successif des 0 et 1, 0 pour aller a gauche et 1 pour aller
 * a droite.
 * \relatesalso Pile
 * \param compteur le numero du noeud dont on veut le chemin.
 * \return Une pile contenant les mouvements successifs pour arriver au
 * noeud du tas que l'on veut atteindre.
 * */
Pile *remplissagePile(int compteur);



#endif
