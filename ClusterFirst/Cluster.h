#ifndef CLUSTER_H
#define CLUSTER_H

#include "Objet.h"

typedef struct _Cluster
{
	Objet * ptrO;
	struct _Cluster * succ;
} Cluster;

Cluster * Cluster_create(void);
void Cluster_init(Cluster * cluster);

#endif //CLUSTERFIRST_H
