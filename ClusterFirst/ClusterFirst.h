#ifndef CLUSTERFIRST_H
#define CLUSTERFIRST_H

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "ListeCluster.h"
#include "Objet.h"
#include "Cluster.h"
#include "util.h"



Objet ** creationTableauObjet(char * filename, int * nb_lignes, const unsigned int cap_max);
FILE *  open_Fichier(char * filename);
void close_Fichier(FILE * file, char * filename);
ListeCluster * remplissageCluster(const unsigned int cap_max, char * filename);
void trieListeCluster(ListeCluster * liste);
void trieCLuster(Cluster * head, int * distTotal);
Cluster * lePlusProche(Cluster * head, Cluster * cluster, int * minDist, int compt);
int calculDistance(int ax, int ay, int bx, int by);
void inserer(Cluster * enCours, Cluster * cluster, Cluster * head);

#endif //CLUSTERFIRST_H
