#ifndef CLUSTERFIRST_H
#define CLUSTERFIRST_H

#include "Objet.h"

typedef struct _Cluster
{
	Objet * ptrO;
	struct _Cluster * succ;
} Cluster;


void Cluster_init(Cluster * cluster);


#endif //CLUSTERFIRST_H
