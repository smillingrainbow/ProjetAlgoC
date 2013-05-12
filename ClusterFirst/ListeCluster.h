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
	struct _Cluster * ptrC;
}ListeCluster;

void ListeCluster_init(ListeCluster * listeCluster);

void ListeCluster_setvalue_cap(ListeCluster * listeCluster, const int value);
void ListeCluster_setvalue_fini(ListeCluster * listeCluster, const int value);




#endif //LISTECLUSTER_H
