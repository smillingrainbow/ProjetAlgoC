#ifndef LISTEOBJET_H
#define LISTEOBJET_H
 
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "util.h"
#include "Objet.h"


/**
 * \_struct ListeObjet
 * \brief ListeObjet est une liste de pointeurs vers des objets
 *
 * ListeObjet est une liste chainée qui pointe vers des objets. Celle-ci est trié suivant l'itinéraire le plus court pour récupérer tous les produits dans un entrepôt.
 */
typedef struct _ListeObjet
{
	struct _Objet * ptrO; /*!< pointeur vers un élément de type Objet */
	struct _ListeObjet * succ; /*< pointeur vers l'éméent suivant de la liste */
} ListeObjet;

void ListeObjet_init(ListeObjet * liste); 
ListeObjet * ListeObjet_create(void); 

#endif //LISTEOBJET_H