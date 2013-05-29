#include "RootFirst.h"

/**
 * \details ouvre un fichier texte en lecture
 * @param filename nom du fichier texte
 * \return flux du fichier ouvert en lecture
 */
FILE * open_Fichier(char *filename){
	FILE * file;
	file = fopen(filename, "rt"); // ouvrir en lecture
  	if(file == NULL){
	    printf("Impossible d'ouvrir le fichier %s\n", filename);
	    exit(1);
	}
	return file; 
}

/**
 * \details ferme un  fichier texte
 * @param filename nom du fichier texte ouvert
 * @param file le flux du fichier
 */
void close_Fichier(FILE * file, char * filename){
	if(fclose(file) == EOF){
	    printf("Probleme de fermeture du fichier %s", filename);
	    exit(1);
  }
}

/**
 * \brief crée un tableau tabObjet de pointeurs vers des Objets
 * \details récupère dans un fichier texte les produits et leur crée leur Objet
 * @param filename nom du fichier texte
 * @param nb_lignes pointeur sur un entier, null lors de l'appel de la fonction
 * @param cap_max constante entier non signé indiquant la capacité max du chariot
 * \return le tableau tabObjet et le nombre d'objets avec nb_lignes 
 */
Objet ** creationTableauObjet(char * filename, int * nb_lignes, const unsigned int cap_max){
	int indice;
	int idObjet, coordx, coordy, poids;
	Objet ** tabObjet;
	FILE * file = open_Fichier(filename);
	
	if(fscanf(file, "%d", nb_lignes) == 0){ // récupère le nombre de lignes du fichier
											// qui correspond aux nombre de produits
		printf("Erreur de lecture du nombre de lignes du fichier \n");
		exit(1);
	}

	tabObjet = (Objet **) malloc(sizeof(Objet *) * *nb_lignes); // allocation du tableau de pointeurs vers des Objets

	for (indice = 0; indice < *nb_lignes; indice++){
		if(fscanf(file, "%d %d %d %d", &idObjet, &coordx, &coordy, &poids) == 0){ // récupère l'id, le coordonnée x, y et le poids du produit
			printf("Erreur de lecture du nombre de lignes du fichier \n");
			exit(1);
		}
		Objet * objet = Objet_create(); // crée un Objet
		Objet_setvalue_idObjet(objet, idObjet); // rempli les champs de l'Objet avec les valeurs récupérées dans le fichier
		Objet_setvalue_coordx(objet, coordx);
		Objet_setvalue_coordy(objet, coordy);
		Objet_setvalue_poids(objet, poids);
		if(objet->poids > cap_max){
            printf("Erreur poids superieur a la capacité du chariot \n");
            exit(1);
		}
		tabObjet[indice] = objet;
	}

	close_Fichier(file, filename); 
	return tabObjet;
}

ListeObjet * trieTabObjet(char * filename, const unsigned int cap_max){
	int indice = 0;
	int nb_lignes;
	ListeObjet * listeObjet, * listeObjetTmp, * listeObjetHead; 
	Objet * enCours, * objetPlusProche; 
	Objet ** tabObjet = creationTableauObjet(filename, &nb_lignes, cap_max);
	enCours = tabObjet[indice];
	listeObjetHead = ListeObjet_create();
	listeObjet = listeObjetHead;
	// s'il y a plus d'un objet chercher son voisin le plus proche
	if(nb_lignes > 1){
		while (indice < nb_lignes-1){
			listeObjetTmp = ListeObjet_create();
			listeObjet->succ = listeObjetTmp;
			listeObjet = listeObjet->succ; 
			#ifndef NDEBUG
				printf("%d \n", indice);
			#endif
			indice++; 
		}
		listeObjet = listeObjetHead;
		while(listeObjet != NULL){
			objetPlusProche = plusProche(enCours, tabObjet, nb_lignes);
			listeObjet->ptrO = objetPlusProche;
			enCours = objetPlusProche; 
			listeObjet = listeObjet->succ;  
		}
	}
	else{
		listeObjet->ptrO=enCours;
		printf("Un seul objet\n");
	}
	return listeObjet;
}

Objet *  plusProche(Objet * enCours, Objet ** tabObjet, int nb_lignes){
	int indice, x, y; 
	unsigned int minDist, dist; 
	Objet * objetPlusProche, * objetTmp; 
	indice = 0; 
	minDist= INT_MAX; 
	x = enCours->coordx;
	y = enCours->coordy; 
	objetPlusProche = NULL; 
	while(indice < nb_lignes){
		objetTmp = tabObjet[indice];
		if(enCours != objetTmp && objetTmp->trie == FALSE){
			dist = calculDistance(x, y, objetTmp->coordx, objetTmp->coordy);
			if(dist < minDist){
				minDist = dist; 
				objetPlusProche = objetTmp; 
			}
		}
		indice++;
	}
	objetPlusProche->trie = TRUE;
	return objetPlusProche; 
}

int calculDistance(int ax, int ay, int bx, int by){
	unsigned int dist;
	
	dist = abs((bx - ax)*(bx - ax)) + abs((by - ay)*(by - ay));
	return dist;
}

void creationListeCluster(ListeObjet * listeObjet, unsigned int cap_max){
	unsigned int cap = 0; 
	ListeObjet * listeObjetHead, *listeObjetTmp; 
	ListeCluster * listeCluster; 
	Objet * objet, * objetTmp; 
	// s'il y a plus d'un objet découper listeObjet en Cluster
	if(listeObjet->succ != NULL){
		while(listeObjet != NULL){
			objet = listeObjet->ptrO; 
			
		}
	}
	else{ 
		listeCluster = ListeCluster_create();
		listeCluster->ptrLO = listeObjet; 
	}
}