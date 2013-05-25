#include "ListeCluster.h"

/**
 * \details initialise une ListeCluster, les pointeurs à null et les entiers à 0
 * @param listeCluster pointeur vers une liste de cluster
 */ 
void ListeCluster_init(ListeCluster * listeCluster){
	listeCluster->cap = 0;
	listeCluster->succ = NULL;
	listeCluster->fini = FALSE;
	listeCluster->ptrC = NULL;
}

/**
 * \details rempli le champ capacité de listeCluster avec value
 * @param listeCluster pointeur vers une liste de cluster
 * @param value valeur de la capacité (entier non signé)
 */ 
void ListeCluster_setvalue_cap(ListeCluster * listeCluster, const unsigned int value){
	listeCluster->cap =  value; 
}

/**
 * \details rempli le champ fini de listeCluster avec value
 * @param listeCluster pointeur vers une liste de cluster
 * @param value valeur de fini (booleen)
 */
void ListeCluster_setvalue_fini(ListeCluster * listeCluster, const bool value){
	listeCluster->fini = value; 
}

/**
 * \details crée une nouvelle cellule de type ListeCluster et l'initialise avec la fonction init
 * \return listeCluster pointeur vers une structure de type ListeCluster
 */
ListeCluster * ListeCluster_create(void){
	ListeCluster * listeCluster = (ListeCluster *) malloc (sizeof(ListeCluster));
	if (listeCluster == NULL){
		printf("Erreur creation listeCluster \n");
	    exit(1);
	}
	ListeCluster_init(listeCluster);
	return listeCluster; 
}