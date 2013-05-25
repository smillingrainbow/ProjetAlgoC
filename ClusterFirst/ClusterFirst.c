#include "ClusterFirst.h"


/**
 * \details ouvre un fichier texte en lecture
 * \author Natacha Marlio-Marette
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
 * \author Natacha Marlio-Marette
 * @param filename nom du fichier texte ouvert
 * @param file le flux du fichier
 */
void close_Fichier(FILE * file, char * filename){
	if(fclose(file) == EOF){
	    printf("Probleme de fermeture du fichier %s", filename);
	    exit(1);
  }
}

Objet ** creationTableauObjet(char * filename, int * nb_lignes, const unsigned int cap_max){
	int indice;
	int idObjet, coordx, coordy, poids;
	Objet ** tabObjet;
	FILE * file = open_Fichier(filename);

#ifndef NDEBUG
	printf("creationTableauObjet \n");
#endif

	fscanf(file, "%d", nb_lignes);

#ifndef NDEBUG
	printf("nombre de lignes :  %d\n", *nb_lignes);
#endif

	tabObjet = (Objet **) malloc(sizeof(Objet *) * *nb_lignes);

	for (indice = 0; indice < *nb_lignes; indice++){
		fscanf(file, "%d %d %d %d", &idObjet, &coordx, &coordy, &poids);
		Objet * objet = Objet_create();
		Objet_setvalue_idObjet(objet, idObjet);
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
	//nb_lignes = (int) sizeof(tabObjet);
	//ListeCluster_init(listeCluster);
#ifndef NDEBUG
	printf("remplissageCluster \n");
	printf("nombre de lignes :  %d\n", nb_lignes);
#endif
	if (indice<nb_lignes){
		printf("indice<nb_lignes\n");
	}
	while (indice < nb_lignes){
		printf("1\n");
		objet = tabObjet[indice];
				printf("2\n");
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
		printf("fin remplissageCluster\n");
	}
	printf("indice :  %d\n", indice);
	return listeCluster ;
}

void trieListeCluster(ListeCluster * liste){
	while (liste != NULL){
		trieCLuster(liste->ptrC);
		liste = liste->succ;
	}
}

void trieCLuster(Cluster * head){
	Cluster * enCours, * clusterTmp;
#ifndef NDEBUG
	int i=0;
#endif
	enCours = head;
	if (enCours->succ ==  NULL)
		printf("on a souci succ =  NULL !!! \n");
	while (enCours->succ != NULL){
		#ifndef NDEBUG
			printf("trie cluster \n");
			printf("\ttour n°%d\n", i);
		#endif
		clusterTmp = lePlusProche(enCours);
		// cas ou il n'y a pas de plus proche (un seul cluster)
		if (clusterTmp == NULL){
			break;	// pour eviter d'inserer une cellule NULL quitte le while
		}
		inserer(enCours, clusterTmp, head);
		enCours = clusterTmp;
			if (enCours ==  NULL){}
		printf("on a souci !!! \n");
		exit(-1);

	}
}

Cluster * lePlusProche(Cluster * cluster){
	Cluster * plusProche;
	Objet * ObjetCourant, * objetTmp;
	unsigned int minDist, x, y, dist;
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
	objetTmp->trie =  TRUE ;
	return plusProche;
}

int calculDistance(int ax, int ay, int bx, int by){
	unsigned int dist;
	//dist = (unsigned int) sqrt(((bx - ax)*(bx - ax)) + ((by - ay)*(by - ay)));
	dist = abs((bx - ax)*(bx - ax)) + abs((by - ay)*(by - ay));
	return dist;
}

void inserer(Cluster * enCours, Cluster * cluster, Cluster * head){
	Cluster * clusterTmp;
	clusterTmp = head;
	if (head == enCours){
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
