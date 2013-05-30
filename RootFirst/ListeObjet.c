#include "ListeObjet.h"


/**
 * \details initialise une ListeObjet en mettant les pointeurs à null
 * @param liste pointeur vers une liste d'Objet'
 */ 
void ListeObjet_init(ListeObjet * liste){
	liste->ptrO = NULL;
	liste->succ = NULL;
}


/**
 * \details crée une nouvelle cellule de type ListeObjet et l'initialise avec la fonction init
 * \return liste pointeur vers une structure de type ListeObjet
 */
ListeObjet * ListeObjet_create(void){
	ListeObjet * liste = (ListeObjet *) malloc (sizeof(ListeObjet));
	if (liste == NULL){
		printf("Erreur creation listeObjet \n");
	    exit(1);
	}
	ListeObjet_init(liste);
	return liste; 
}