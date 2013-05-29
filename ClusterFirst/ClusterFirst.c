#include "ClusterFirst.h"


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
 * \details ferme un fichier texte
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
 * \brief rempli la liste listeCluster
 * \details crée les différents Cluster, et dans chaque cellule des Clusters ajoute un Objet à partir du tableau tabObjet
 * @param filename nom du fichier texte
 * @param cap_max constante entier non signé indiquant la capacité max du chariot
 * \return un pointeur vers la liste listeCluster 
 */
ListeCluster * remplissageCluster(const unsigned int cap_max, char * filename){
	int indice = 0;
	unsigned int newCap =0;
	int nb_lignes;
	ListeCluster * listeCluster = ListeCluster_create();
	ListeCluster * listeClusterTmp;
	Cluster * cluster;
	Cluster * clusterTmp;
	Objet * objet;
	Objet ** tabObjet = creationTableauObjet(filename, &nb_lignes, cap_max);

	while (indice < nb_lignes){ 
		objet = tabObjet[indice]; 
        newCap = listeCluster->cap + objet->poids;
		while ((cap_max < newCap) && (listeCluster->succ != NULL)){
			listeCluster = listeCluster->succ;
			newCap = listeCluster->cap + objet->poids;
		}
        if(newCap <= cap_max){
            if(listeCluster->succ != NULL){
        	clusterTmp = listeCluster->ptrC;
			while (clusterTmp->succ != NULL){
				clusterTmp = clusterTmp->succ;
			}
			cluster = Cluster_create();
			clusterTmp->succ = cluster;
			cluster->ptrO = objet;
			listeCluster->cap = newCap;
            }
            else{
                clusterTmp = Cluster_create();
                listeCluster->ptrC = clusterTmp;
                clusterTmp->ptrO = objet;
                listeCluster->cap = newCap;
            }
            if (newCap == cap_max){
				listeCluster->fini =  TRUE;
            }
        }
		else{
			listeClusterTmp = ListeCluster_create();
			listeCluster->succ = listeClusterTmp;
			listeClusterTmp->cap = objet->poids;
			if (listeClusterTmp->cap == cap_max){
				listeClusterTmp->fini = TRUE;
            }
			cluster = Cluster_create();
			listeClusterTmp->ptrC = cluster;
			cluster->ptrO = objet;
		}
		indice ++;
	}
	return listeCluster ;
}

/**
 * \brief trie la liste listeCluster
 * \details va trier chaque Cluster de la liste 
 * @param liste pointeur vers la liste listecLuster
 */
void trieListeCluster(ListeCluster * liste){
	while (liste != NULL){
		trieCLuster(liste->ptrC); // trie chaque cluster de la liste
		liste = liste->succ;
	}
}

/**
 * \brief trie la liste Cluster
 * \details trie un Cluster en cherchant la cellule la plus proche de la cellule courante et en l'insérant avant celle-ci
 * @param head pointeur vers la tête de la liste Cluster
 */
void trieCLuster(Cluster * head){
	Cluster * enCours, * clusterTmp;
	enCours = head;
	while (enCours->succ != NULL){
		clusterTmp = lePlusProche(enCours);
		// cas ou il n'y a pas de plus proche (un seul cluster)
		if (clusterTmp == NULL){
			break;	// pour eviter d'inserer une cellule NULL quitte le while
		}
		inserer(enCours, clusterTmp, head); // insere la clusterTmp avant enCours
		enCours = clusterTmp;
		if (enCours ==  NULL){
			printf("Erreur trieCLuster \n");
			exit(-1);
		}
	}
}

/**
 * \details cherche le Cluster le plus proche du Cluster courant 
 * @param cluster pointeur vers le Cluster courant
 * \return le Cluster contenant l'objet le plus proche de l'objet courant
 */
Cluster * lePlusProche(Cluster * cluster){
	Cluster * plusProche;
	Objet * ObjetCourant, * objetTmp;
	unsigned int minDist, dist;
	int x, y; 
	minDist = INT_MAX;
	plusProche = NULL;
	ObjetCourant = cluster->ptrO;
	x = ObjetCourant->coordx;
	y = ObjetCourant->coordy;
	cluster = cluster->succ;
	while ( cluster != NULL){
		objetTmp = cluster->ptrO;
		if (objetTmp->trie == FALSE){
			dist = calculDistance(x, y , objetTmp->coordx, objetTmp->coordy);
			if (dist < minDist){
				minDist = dist;
				plusProche = cluster;
			}
		}
		cluster = cluster->succ;
	}
	objetTmp->trie =  TRUE ; // l'Objet est trie, on met le champ a TRUE pour ne pas le retrier 
	return plusProche;
}

/** 
 * \details calcul la distance entre deux objets
 * @param ax entier coordonnée x de l'objet courant 
 * @param ay entier coordonnée y de l'objet courant
 * @param bx entier coordonnée x de l'objet à tester
 * @param by entier coordonnée y de l'objet à tester
 * \return la distance entre les deux objets
 */
int calculDistance(int ax, int ay, int bx, int by){
	unsigned int dist;
	
	dist = abs((bx - ax)*(bx - ax)) + abs((by - ay)*(by - ay));
	return dist;
}

/** 
 * \details insere la cellule cluster juste avant la cellule enCours en rechainant toutes la liste
 * @param enCours pointeur vers la cellule Cluster courante
 * @param cluster pointeur vers la cellule Cluster à inserer
 * @param head pointeur vers la cellule Cluster de tête de liste
 */
void inserer(Cluster * enCours, Cluster * cluster, Cluster * head){
	Cluster * clusterTmp;
	clusterTmp = head;
	if (head == enCours){ // si la cellule enCours est la même que le tête de liste
		head = cluster;
		while ( clusterTmp->succ != cluster){
			clusterTmp = clusterTmp->succ;
		}
		clusterTmp = cluster->succ;
		cluster->succ = enCours;
	}
	else{
		while (head->succ != enCours){
			head = head->succ;
		}
		while ( clusterTmp->succ != cluster){
			clusterTmp = clusterTmp->succ;
		}
		head->succ = cluster;
		clusterTmp->succ = cluster->succ;
		cluster->succ = enCours;
	}
}
