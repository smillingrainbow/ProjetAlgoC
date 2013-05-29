#ifndef ROOTFIRST_H
#define ROOTFIRST_H

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "Objet.h"
#include "ListeObjet.h"
#include "util.h"
#include "ListeCluster.h"

Objet ** creationTableauObjet(char * filename, int * nb_lignes, const unsigned int cap_max);
FILE *  open_Fichier(char * filename);
void close_Fichier(FILE * file, char * filename);
ListeObjet * trieTabObjet(char * filename, const unsigned int cap_max);
Objet *  plusProche(Objet * enCours, Objet ** tabObjet, int nb_lignes); 
int calculDistance(int ax, int ay, int bx, int by);
void creationListeCluster(ListeObjet * listeObjet, unsigned int cap_max);

#endif //ROOTFIRST_H