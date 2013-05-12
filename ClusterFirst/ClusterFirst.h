#ifndef CLUSTERFIRST_H
#define CLUSTERFIRST_H

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "ListeCluster.h"
#include "Objet.h"

//void remplissageCluster(Objet **tabObjet);

void creationTableauObjet(char * filename);
FILE *  open_Fichier(char * filename);
void close_Fichier(FILE * file, char * filename);


#endif //CLUSTERFIRST_H
