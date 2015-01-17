#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#ifdef TASBINAIRE
#include "tasBinaire.h"
#endif
#include "pile.h"
#include "prim.h"
#include "parser.h"

#ifdef MERGESORT
#include "merge_sort.h"
#endif

#include "kruskal.h"
#include "graphe.h"

int main(int argc,char *argv[])
{
	Graphe g = newGraphe();
	if(argc==2)
	{
		printf("Chargement du graphe.\n");
		remplissage_from_file(g,argv[1]);
	}
	else
	{
		printf("Pas de graphe chargé.\n");
	}
	//afficherGraphe(g);
	printf("Nombre de noeuds de g %d\n",g->nbNoeuds);
	Graphe g1 = kruskal(g);
	//safficherGraphe(g1);
	supprimerGraphe(g);
	supprimerGraphe(g1);
	return 1;
}

	/*int main(int argc, char *argv[]){
		int pred;
		int poids;
		int succ;
		Graphe g = newGraphe();
		char line[30];
		FILE* fd;
		long int dateFin;
		long int dateDebut;
		int i;
		struct timeval tvDebut1;
		struct timeval tvFin1;
		struct timeval tvDebut2;
		struct timeval tvFin2;
		char str[15];
		for(i=1; i<=5;i++){
			strcpy(str, argv[1]);
			printf("%s\n", str);
			switch(i){
				case 1:
					fd = fopen(strcat(str,"_1.g"), "r");
					break;
				case 2:
					fd = fopen(strcat(str,"_2.g"), "r");
					break;
				case 3:
					fd = fopen(strcat(str,"_3.g"), "r");
					break;
				case 4:
					fd = fopen(strcat(str,"_4.g"), "r");
					break;
				case 5:
					fd = fopen(strcat(str,"_5.g"), "r");
					break;
			}
			fseek(fd, 1, SEEK_SET);
			while(fgets(line, 30, fd)){
				sscanf(line, "%d %d %d", &pred, &succ, &poids);
				ajouterArc(g, pred ,poids, succ);
			}
			//Prim
			gettimeofday(&tvDebut1, NULL);
			dateDebut = tvDebut1.tv_sec*1000000+tvDebut1.tv_usec;
			prim(g);
			gettimeofday(&tvFin1, NULL);
			dateFin = tvFin1.tv_sec*1000000+tvFin1.tv_usec;
			printf("Temps d'exécution de Prim : %f ms\n", (double)dateFin/1000 - (double)dateDebut/1000);
			//Kruskal
			gettimeofday(&tvDebut2, NULL);
			dateDebut = tvDebut2.tv_sec*1000000+tvDebut2.tv_usec;
			kruskal(g);
			gettimeofday(&tvFin2, NULL);
			dateFin = tvFin2.tv_sec*1000000+tvFin2.tv_usec;
			printf("Temps d'exécution de Kruskal : %f ms\n", (double)dateFin/1000 - (double)dateDebut/1000);
			fclose(fd);
		}
		supprimerGraphe(g);
		return 0;	
	}*/