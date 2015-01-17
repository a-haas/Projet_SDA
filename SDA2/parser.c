#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"
#include "parser.h"

void remplissage_from_file(Graphe g,char *filename)
{
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	if(pfile == NULL)
	{
		perror("Fichier non valide.");
		return;
	}

	int nbNoeuds = 0;
	int nbArcs = 0;
	int pred,poids,succ,n;
	fscanf(pfile,"%d",&nbNoeuds);
	fscanf(pfile,"%d",&nbArcs);
	//printf("Nombre de noeuds %d\n",nbNoeuds);
	//printf("Nombre d'arcs %d\n",nbArcs);
	for(n = 0;n<nbArcs;n++)
	{
		fscanf(pfile, "%d", & pred);
		fscanf(pfile, "%d", & succ);
		fscanf(pfile, "%d", & poids);
		//printf("Ajout de %d %d %d\n",pred,poids,succ);
		ajouterArc(g,pred,poids,succ);
	}
		fclose (pfile);
}