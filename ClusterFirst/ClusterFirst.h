#ifndef CLUSTERFIRST_H
#define CLUSTERFIRST_H

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "ListeCluster.h"
#include "Objet.h"
#include "Cluster.h"

void remplissageCluster(const int cap_max, char * filename);

Objet ** creationTableauObjet(char * filename);
FILE *  open_Fichier(char * filename);
void close_Fichier(FILE * file, char * filename);


#endif //CLUSTERFIRST_H
