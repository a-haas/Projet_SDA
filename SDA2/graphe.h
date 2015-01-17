#ifndef __GRAPHE_H
#define __GRAPHE_H

typedef struct arc{
	int pred;
	int poids;
	int succ;
	struct arc *aSuivant;
}*Arc,strArc;

typedef struct noeud{
	int flag;
	int id;
	struct noeud *nSuivant;
	Arc listeArcs;
}*Noeud,strNoeud;

typedef struct graphe{
	Noeud listeNoeuds;
	int nbNoeuds;
}*Graphe,strGraphe;

/**
*\brief Cree un noeud et renvoie un pointeur vers celui-ci.
*\param id L'identifiant du noeud.
*\return Un pointeur vers le noeud nouvellement cree.
*/
Noeud creerNoeud(int id,int flag);

/**
*\brief Supprime un noeud.
*\param n Le noeud que l'on veut supprimer.
*/
void supprimerNoeud(Noeud n);

/**
*\brief Cree un arc et renvoie un pointeur vers celui-ci.
*\param pred L'identifiant du noeud predecesseur.
*\param poids Le poids de l'arc.
*\param succ L'identifiant du noeud successeur.
*\return Un pointeur vers l'arc nouvellement cree.
*/
Arc creerArc(int pred, int poids, int succ);

/**
*\brief Supprime un arc.
*\param a L'arc a supprimer.
*/
void supprimerArc(Arc a);

/**
*\brief Ajoute un arc a la liste des arcs d'un noeud.
*\param l La liste des arcs d'un noeud.
*\return Un pointeur vers la nouvelle liste des arcs.
*/
Arc ajouterArcListe(Arc l,Arc a);

/**
*\brief Supprime un arc de la liste des arc.
*\param l La liste des arcs d'un noeud.
*\param succ L'identifiant du successeur de l'arc que l'on veut supprimer, le predecesseur n'est pas necessaire car on s'arrange pour chercher un pred donne.
*\return Un pointeur vers la nouvelle liste d'arcs nouvellement cree.
*/
Arc supprimerArcListe(Arc l, int succ);

/**
*\brief Supprime toute la liste des arcs d'un noeud.
*\param l La liste des arcs.
*\return NULL.
*/
Arc supprimerListeArcs(Arc l);

/**
*\brief Initialise un graphe.
*\return Un pointeur vers un graphe.
*/
Graphe newGraphe();

/**
*\brief Ajoute un noeud au graphe deja initialise.
*\param g Le graphe.
*\param id L'identifiant du noeud a ajouter.
*/
void ajouterNoeud(Graphe g, int id, int flag);

/**
*\brief Ajoute un arc au graphe et ajoute egalement les noeuds dont il depend si necessaire;
*\param g Le graphe auquel on veut ajouter un noeud.
*\param pred l'identifiant du predecesseur.
*\param poids Le poids de l'arc.
*\param succ L'identifiant du successeur.
*/
void ajouterArc(Graphe g,int pred,int poids,int succ);

/**
*\brief Supprime un arc du graphe.
*\param g Le graphe.
*\param pred Le predecesseur de l'arc a supprimer.
*\param pred Le successeur de l'arc a supprimer.
*/
void supprimerArcGraphe(Graphe g, int pred, int succ);

/**
*\brief Dit si un noeud existe dans un graphe donne.
*\param g Le graphe dont on veut savoir si le noeud existe.
*\param id L'identifiant du noeud dont on veut savoir si il appartient au graphe.
*\return 0 si le noeud n'est pas dans le graphe, -1 en cas d'erreur et 1 sinon.
*/
int noeudExiste(Graphe g,int id);

/**
*\brief Renvoie un pointeur vers le noeud que l'on cherche.
*\param g Le graphe dans lequel se trouve le noeud.
*\param id L'identifiant du noeud dont on veut avoir le pointeur de noeud.
*\return NULL si le graphe n'existe pas ou bien si le noeud n'appartient pas au graphe et le pointeur vers le noeud sinon.
*/
Noeud trouveNoeud(Graphe g,int id);

/**
*\brief Supprime un noeud du graphe ainsi que toutes ses dependances si elles existent.
*\param g Le graphe dont on veut supprimer un noeud.
*\param id L'identifiant du noeud.
*/
void supprimerNoeudGraphe(Graphe g,int id);

/**
*\brief Supprime un graphe.
*\param g Le graphe a supprimer.
*/
void supprimerGraphe(Graphe g);

/**
*\brief Affiche un graphe.
*\param g Le graphe que l'on veut afficher.
*/
void afficherGraphe(Graphe g);

#endif
