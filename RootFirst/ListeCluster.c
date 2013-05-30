#include "ListeCluster.h"


/**
 * \details initialise une ListeCluster en mettant les pointeurs à null
 * @param liste pointeur vers une liste de Cluster
 */ 
void ListeCluster_init(ListeCluster * liste){
	liste->ptrLO = NULL;
	liste->succ = NULL;
}

/**
 * \details crée une nouvelle cellule de type ListeCluster et l'initialise avec la fonction init
 * \return listeCluster pointeur vers une structure de type ListeCluster
 */
ListeCluster * ListeCluster_create(void){
	ListeCluster* liste = (ListeCluster *) malloc (sizeof(ListeCluster));
	if (liste == NULL){
		printf("Erreur creation listeCluster \n");
	    exit(1);
	}
	ListeCluster_init(liste);
	return liste; 
}