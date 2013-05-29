#include "ListeObjet.h"

void ListeObjet_init(ListeObjet * liste){
	liste->ptrO = NULL;
	liste->succ = NULL;
}

ListeObjet * ListeObjet_create(void){
	ListeObjet * liste = (ListeObjet *) malloc (sizeof(ListeObjet));
	if (liste == NULL){
		printf("Erreur creation listeObjet \n");
	    exit(1);
	}
	ListeObjet_init(liste);
	return liste; 
}