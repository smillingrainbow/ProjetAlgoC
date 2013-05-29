#ifndef LISTECLUSTER_H
#define LISTECLUSTER_H

#include "Cluster.h"
#include "util.h"

 /**
 * \_struct ListeCluster
 * \brief Liste chainée de pointeur vers des Clusters
 *
 * ListeCluster est une liste chainée de pointeur qui se termine par NULL.
 */
typedef struct _ListeCluster
{
	unsigned int cap; /*!< entier non signé correspondant à la capacité du cluster */
	struct _ListeCluster * succ; /*!< pointeur vers la cellule suivante */
	bool fini; /*!< booleen qui indique si la liste de Cluster est pleine */
	struct _Cluster * ptrC; /*!< pointeur vers une liste de Cluster*/
}ListeCluster;

void ListeCluster_init(ListeCluster * listeCluster);
ListeCluster * ListeCluster_create(void); 
void ListeCluster_setvalue_cap(ListeCluster * listeCluster, const unsigned int value);
void ListeCluster_setvalue_fini(ListeCluster * listeCluster, const int value);




#endif //LISTECLUSTER_H
