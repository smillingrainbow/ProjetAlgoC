#ifndef LISTECLUSTER_H
#define LISTECLUSTER_H
 
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "util.h"
#include "ListeObjet.h"


/**
 * \_struct ListeCluster
 * \brief ListeCluster est une liste de pointeurs vers les têtes de liste d'objets
 *
 * ListeCluster est une liste chainée qui pointe vers es têtes de liste d'objets. 
 */
typedef struct _ListeCluster
{
	struct _ListeObjet * ptrLO; /*!< pointeur vers la tête de la liste d'Objet de type ListeObjet */
	struct _ListeCluster * succ; /*< pointeur vers l'éméent suivant de la liste */
} ListeCluster;

void ListeCluster_init(ListeCluster * liste); 
ListeCluster * ListeCluster_create(void); 

#endif //LISTECLUSTER_H