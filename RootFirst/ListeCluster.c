#include "ListeCluster.h"

void ListeCluster_init(ListeCluster * liste){
	liste->ptrLO = NULL;
	liste->succ = NULL;
}

ListeCluster * ListeCluster_create(void){
	ListeCluster* liste = (ListeCluster *) malloc (sizeof(ListeCluster));
	if (liste == NULL){
		printf("Erreur creation listeCluster \n");
	    exit(1);
	}
	ListeCluster_init(liste);
	return liste; 
}