#ifndef LISTECLUSTER_H
#define LISTECLUSTER_H

#include "Cluster.h"
#include "util.h"
/**
 * Structure ListeCluster de type liste
 * Chaque cellule contient : 
 * @param cap un entier non signé correspondant à la capacité du cluster
 * @param succ un pointeur vers le suivant de la liste ListeCluster
 * @param fini un booleen qui indique si le cluster est plein
 * @param ptrC un pointeur vers une liste de Cluster
 */
typedef struct _ListeCluster
{
	unsigned int cap;
	struct _ListeCluster * succ;
	bool fini;
	struct _Cluster * ptrC;
}ListeCluster;

void ListeCluster_init(ListeCluster * listeCluster);
ListeCluster * ListeCluster_create(void); 
void ListeCluster_setvalue_cap(ListeCluster * listeCluster, const unsigned int value);
void ListeCluster_setvalue_fini(ListeCluster * listeCluster, const int value);




#endif //LISTECLUSTER_H
