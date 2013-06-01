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

/**
 * \brief Trie le tableau d'Objet
 * \details Cette fonction crée un tableau de pointeurs vers des Objets, et le trie suivant le chemin le plus court pour tous les récupérer.
 * @param filename Fichier texte contenant les données sur les produits
 * @param cap_max Entier non signé représentant la capacité max du chariot.
 * \return Cette fonction retourne un pointeur sur la tête de la liste d'Objet triée.
 */
ListeObjet * trieTabObjet(char * filename, const unsigned int cap_max){
	int indice = 0;
	int nb_lignes;
	int dist = 0;
	unsigned int distTotal = 0;
	int parcours = 0;
	ListeObjet * listeObjet, * listeObjetTmp, * listeObjetHead; 
	Objet * enCours, * objetPlusProche; 
	Objet ** tabObjet = creationTableauObjet(filename, &nb_lignes, cap_max);
	enCours = tabObjet[indice];
	listeObjetHead = ListeObjet_create();
	listeObjet = listeObjetHead;
	// s'il y a plus d'un objet chercher son voisin le plus proche
	if(nb_lignes > 1){
		// création de la liste en fonction du nombre de produits
		while (indice < nb_lignes-1){
			listeObjetTmp = ListeObjet_create();
			listeObjet->succ = listeObjetTmp;
			listeObjet = listeObjet->succ; 
			#ifndef NDEBUG
				printf("%d \n", indice);
			#endif
			indice++; 
		}
		// le pointeur pointe sur la tête de liste
		listeObjet = listeObjetHead;
		while(listeObjet != NULL){
			// recherche du plus proche produit de celui en cours
			objetPlusProche = plusProche(enCours, tabObjet, nb_lignes, &dist);
			listeObjet->ptrO = objetPlusProche;
			enCours = objetPlusProche; 
			listeObjet = listeObjet->succ;  
			// ne crecupère pas la première valeur
			if(parcours != 0){
				distTotal += dist;
			}
			#ifndef NDEBUG
				printf("distance min :  %d \n", dist);
				printf("distanceTotal : %d \n", distTotal);
			#endif
			parcours++;
		}
	}
	// s'il n'y a qu'un seul produit dans la commande
	else{
		listeObjet->ptrO=enCours;
		#ifndef NDEBUG
				printf("Un seul objet\n");
		#endif
	}
	printf("La distance a parcourir est : %d \n", distTotal);
	// on retourne le pointeur sur la tête de la liste
	return listeObjetHead;
}

/**
 * \brief Cherche l'élément le plus proche
 * \details Cette fonction cherche le produit le plus proche du produit en cours.
 * @param enCours pointeur sur l'Objet courant
 * @param tabObjet tableau de pointeurs vers des Objets
 * @param nb_lignes entier représentant le nombre de produit de la commande
 * \return Cette fonction retourne un pointeur sur le produit le plus proche de celui courant.
 */
Objet *  plusProche(Objet * enCours, Objet ** tabObjet, int nb_lignes,int * minDist){
	int indice, x, y; 
	int dist = 0; 
	Objet * objetPlusProche, * objetTmp; 
	indice = 0; 
	*minDist= INT_MAX; // initialisation de minDist à un nombre très grand
	x = enCours->coordx;
	y = enCours->coordy; 
	objetPlusProche = NULL; 
	while(indice < nb_lignes){
		objetTmp = tabObjet[indice];
		// si le produit a parcourir n'est pas le produit courant et n'a pas déjà été trié
		if(enCours != objetTmp && objetTmp->trie == FALSE){
			dist = calculDistance(x, y, objetTmp->coordx, objetTmp->coordy);
			if(dist < *minDist){
				*minDist = dist; 
				objetPlusProche = objetTmp; 
			}
		}
		indice++;
	}
	if(*minDist == INT_MAX){
		*minDist = 0;
	}
	#ifndef NDEBUG
		printf("minDist : %d \n", *minDist);
	#endif
	// le champ trie de l'objet le plus proche passe à TRUE
	objetPlusProche->trie = TRUE;
	return objetPlusProche; 
}

/**
 * \brief Calcul la distance entre deux produits
 * \details Calcul la distance entre le produit courant et le produit à parcourir
 * @param ax entier coordonnée x de l'objet courant 
 * @param ay entier coordonnée y de l'objet courant
 * @param bx entier coordonnée x de l'objet à tester
 * @param by entier coordonnée y de l'objet à tester
 * \return la distance entre les deux objets
 */
int calculDistance(int ax, int ay, int bx, int by){
	int dist;
	
	dist = abs((bx - ax)) + abs((by - ay));
	return dist;
}

/**
 * \brief Crée les différents Cluster
 * \details Cette fonction découpe la liste d'Objet en Cluster avec une capacité inférieur ou égal à la capacité maximum du chariot.
 * @param listeObjet Pointeur vers la liste d'Objet crée dans trieTabObjet
 * @param cap_max Entier non signé représentant la capacité max du chariot.
 */
void creationListeCluster(ListeObjet * listeObjet, unsigned int cap_max){
	unsigned int cap = 0; 
	ListeObjet * listeObjetHead, *listeObjetTmp; 
	ListeCluster * listeCluster, * listeClusterTmp; 
	Objet * objet, * objetTmp;
	listeObjetHead = listeObjet; 
	listeCluster = ListeCluster_create();
	#ifndef NDEBUG
		printf("avant boucle\n");
	#endif
	// s'il y a plus d'un objet découper listeObjet en Cluster
	if(listeObjet->succ != NULL){
		while(listeObjet != NULL){
			objet = listeObjet->ptrO; 
			cap += objet->poids;
			// s'il listeObjet n'est pas l'avant dernier élément
			if(listeObjet->succ != NULL){
				listeObjetTmp = listeObjet->succ;
				objetTmp = listeObjetTmp->ptrO;
				// permet de vérifier si le prochain objet peut être dans le cluster courant
				if ((cap + objetTmp->poids) > cap_max){
					listeClusterTmp = ListeCluster_create(); // crée le cluster suivant
					listeCluster->ptrLO = listeObjetHead; // listeCLuster pointe vers le début de la liste
					listeObjet->succ = NULL; // dernier élément du Cluster
					listeObjetHead = listeObjetTmp; // pointeur sur le début du Cluster suivant
					listeObjet = listeObjet->succ; 
					listeCluster->succ = listeClusterTmp;
					listeCluster = listeCluster->succ; // listeCluster pointe sur la liste du prochain Cluster
					cap = 0; // remise à zéro de la capacité pour le prochain cluster
				} // si oui on continue de parcourir listeObjet
				else{
					listeObjet = listeObjet->succ; 
				}
			} // cas pour le dernier élément de listeObjet
			else{
			// ajoute le dernier objet de listeObjet au dernier cluster 	
				listeCluster->ptrLO = listeObjetHead;
				listeObjet = listeObjet->succ; // fin de la boucle while listeObjet = NULL;
			}
		}
	}
	else{ 
		listeCluster->ptrLO = listeObjetHead; 
	}
}