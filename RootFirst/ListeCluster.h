#ifndef LISTECLUSTER_H
#define LISTECLUSTER_H
 
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "util.h"
#include "ListeObjet.h"

typedef struct _ListeCluster
{
	struct _ListeObjet * ptrLO; 
	struct _ListeCluster * succ; 
} ListeCluster;

void ListeCluster_init(ListeCluster * liste); 
ListeCluster * ListeCluster_create(void); 

#endif //LISTECLUSTER_H