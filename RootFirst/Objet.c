#include "Objet.h"

/**
 * \details initialise un Objet, les entiers à 0 et le booleen à FALSE
 * @param listeCluster pointeur vers une liste de cluster
 */ 
void Objet_init(Objet * objet){
	objet->idObjet = 0;
	objet->coordx = 0; 
	objet->coordy = 0;
	objet->poids = 0;
	objet->trie = FALSE;
}

/**
 * \details rempli le champ idObjet d'Objet avec value
 * @param Objet pointeur vers un Objet
 * @param value valeur de l'id du produit (entier non signé)
 */ 
void Objet_setvalue_idObjet(Objet * objet, const unsigned int value){
	objet->idObjet = value; 
}

/**
 * \details rempli le champ coordx d'Objet avec value
 * @param Objet pointeur vers un Objet
 * @param value valeur du coordonnée x du produit 
 */ 
void Objet_setvalue_coordx(Objet * objet, const int value){
	objet->coordx = value; 
}

/**
 * \details rempli le champ coordy d'Objet avec value
 * @param Objet pointeur vers un Objet
 * @param value valeur du coordonnée y du produit 
 */ 
void Objet_setvalue_coordy(Objet * objet, const int value){
	objet->coordy = value; 
}

/**
 * \details rempli le champ poids d'Objet avec value
 * @param Objet pointeur vers un Objet
 * @param value valeur du poids du produit (entier non signé)
 */ 
void Objet_setvalue_poids(Objet * objet, const unsigned int value){
	objet->poids = value; 
}

/**
 * \brief Crée un élement de type Objet
 * \details Cette fonction crée un élément de type objet et l'initialise.
 * \return Elle retourne un pointeur sur l'élément alloué et initialisé.
 */
Objet * Objet_create(void){
	Objet * objet = (Objet *) malloc (sizeof(Objet));
	if (objet == NULL){
		printf("Erreur creation objet \n");
	    exit(1);
	}
	Objet_init(objet);
	return objet;
}