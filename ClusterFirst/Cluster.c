#include "Cluster.h"

/**
 * \details initialise un Cluster, les pointeurs à null
 * @param Cluster pointeur vers un Objet
 */ 
void Cluster_init(Cluster * cluster){
	cluster->ptrO = NULL; 
	cluster->succ = NULL;
}

/**
 * \details crée une nouvelle cellule de type Cluster et l'initialise avec la fonction init
 * \return Cluster pointeur vers une structure de type Cluster
 */
Cluster * Cluster_create(void){
	Cluster * cluster = (Cluster *) malloc (sizeof(Cluster));
	if (cluster == NULL){
		printf("Erreur creation listeCluster \n");
	    exit(1);
	}
	Cluster_init(cluster);
	return cluster;
}