#ifndef LISTECLUSTER_H
#define LISTECLUSTER_H

#include "Cluster.h"
#include "util.h"

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
