#include "Cluster.h"

void Cluster_init(Cluster * cluster){
	cluster->ptrO = NULL; 
	cluster->succ = NULL;
}

Cluster * Cluster_create(void){
	Cluster * cluster = (Cluster *) malloc (sizeof(Cluster));
	if (cluster == NULL){
		printf("Erreur creation listeCluster \n");
	    exit(1);
	}
	Cluster_init(cluster);
	return cluster;
}