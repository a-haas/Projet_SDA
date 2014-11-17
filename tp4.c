#include <stdio.h>
#include <stdlib.h>

typedef struct tas_binaire{
	int racine;
	struct tas_binaire* ag;
	struct tas_binaire* ad;
}Tas;