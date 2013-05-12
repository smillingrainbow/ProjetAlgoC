#ifndef LISTECLUSTER_H
#define LISTECLUSTER_H

#include "Cluster.h"

typedef int bool;
#define TRUE 1
#define FALSE 0

typedef struct _ListeCluster
{
	int cap;
	struct _ListeCluster * succ;
	bool fini;
	struct _Cluster * valC;
}ListeCluster;





#endif //LISTECLUSTER_H
