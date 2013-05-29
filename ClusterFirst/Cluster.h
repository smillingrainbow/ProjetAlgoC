#ifndef CLUSTER_H
#define CLUSTER_H

#include "Objet.h"


 /**
 * \_struct Cluster
 * \brief Liste chainée de pointeur vers des Objets
 *
 * Cluster est une liste chainée de pointeur qui se termine par NULL.
 */
typedef struct _Cluster
{
	Objet * ptrO; /*!< pointeur vers un Objet*/
	struct _Cluster * succ; /*!< pointeur vers la cellule suivante */
} Cluster;

Cluster * Cluster_create(void);
void Cluster_init(Cluster * cluster);

#endif //CLUSTERFIRST_H
