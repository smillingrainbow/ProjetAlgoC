#ifndef CLUSTER_H
#define CLUSTER_H

#include "Objet.h"

/**
 * Structure Cluster de type liste
 * Chaque cellule contient : 
 * @param ptrO un pointeur vers un Objet
 * @param succ pointeur vers le suivant de la liste Cluster
 */
typedef struct _Cluster
{
	Objet * ptrO;
	struct _Cluster * succ;
} Cluster;

Cluster * Cluster_create(void);
void Cluster_init(Cluster * cluster);

#endif //CLUSTERFIRST_H
