#include "ListeCluster.h"

void ListeCluster_init(ListeCluster * listeCluster){
	listeCluster->cap = 0;
	listeCluster->succ = NULL;
	listeCluster->fini = FALSE;
	listeCluster->ptrC = NULL;
}

void ListeCluster_setvalue_cap(ListeCluster * listeCluster, const unsigned int value){
	listeCluster->cap =  value; 
}

void ListeCluster_setvalue_fini(ListeCluster * listeCluster, const bool value){
	listeCluster->fini = value; 
}

ListeCluster * ListeCluster_create(void){
	ListeCluster * listeCluster = (ListeCluster *) malloc (sizeof(ListeCluster));
	if (listeCluster == NULL){
		printf("Erreur creation listeCluster \n");
	    exit(1);
	}
	return listeCluster; 
}