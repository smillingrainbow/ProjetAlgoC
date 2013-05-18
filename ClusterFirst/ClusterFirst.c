#include "ClusterFirst.h"

FILE * open_Fichier(char *filename){
	FILE * file; 
	file = fopen(filename, "rt"); // ouvrir en lecture
  	if(file == NULL){
	    printf("Impossible d'ouvrir le fichier %s\n", filename);
	    exit(1);
	}
	return file; 
}

void close_Fichier(FILE * file, char * filename){
	if(fclose(file) == EOF){
	    printf("Probleme de fermeture du fichier %s", filename);
	    exit(1);
  }
}

Objet ** creationTableauObjet(char * filename){
	int indice, nb_lignes, idObjet, coordx, coordy, poids; 
	Objet ** tabObjet;
	FILE * file = open_Fichier(filename);
	fscanf(file, "%d", &nb_lignes);
	tabObjet = (Objet **) malloc (sizeof(Objet *) * nb_lignes);
	
	for (indice = 0; indice <= nb_lignes; indice++){
		fscanf(file, "%d %d %d %d", &idObjet, &coordx, &coordy, &poids);
		Objet *  objet = Objet_create(); 
		Objet_setvalue_idObjet(objet, idObjet);
		Objet_setvalue_coordx(objet, coordx);
		Objet_setvalue_coordy(objet, coordy);
		Objet_setvalue_poids(objet, poids);
		tabObjet[indice] = objet; 
	}

	close_Fichier(file, filename); 
	return tabObjet; 
}

ListeCluster * remplissageCluster(const unsigned int cap_max, char * filename){ 
	unsigned int indice = 0; 
	unsigned int newCap =0; 
	unsigned int nb_lignes;
	ListeCluster * listeCluster = ListeCluster_create();
	ListeCluster * listeClusterTmp;
	Cluster * cluster;
	Cluster * clusterTmp;
	Objet * objet;
	Objet ** tabObjet = creationTableauObjet(filename);
	nb_lignes = (int) sizeof(tabObjet);
	ListeCluster_init(listeCluster);

	while (indice <= nb_lignes){
		objet = tabObjet[indice]; 
		newCap = listeCluster->cap + objet->poids;
		while ((cap_max < newCap) || listeCluster != NULL){
			listeCluster = listeCluster->succ; 
		}

		if (listeCluster == NULL){
			listeClusterTmp = ListeCluster_create();
			listeCluster->succ = listeClusterTmp;
			ListeCluster_init(listeClusterTmp);
			listeClusterTmp->cap = objet->poids; 
			if (listeClusterTmp->cap == cap_max)
				listeClusterTmp->fini = TRUE;
			cluster = Cluster_create();
			listeClusterTmp->ptrC = cluster; 
			cluster->ptrO = objet;
			cluster->succ = NULL; 
		}
		else{
			clusterTmp = listeCluster->ptrC;
			while (clusterTmp->succ != NULL){
				clusterTmp = clusterTmp->succ;
			}
			cluster = Cluster_create(); 
			clusterTmp->succ = cluster;
			cluster->ptrO = objet;
			cluster->succ =  NULL;
			listeCluster->cap = newCap; 
			if (newCap == cap_max)
				listeCluster->fini =  TRUE;
		}
		indice ++; 
	}
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
	enCours = head;
	while (enCours->succ != NULL){
		clusterTmp = lePlusProche(enCours);
		inserer(enCours, clusterTmp, head);
		enCours = clusterTmp;
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
		dist = calculDistance(x, y , objetTmp->coordx, objetTmp->coordy);
		if (dist < minDist){
			minDist = dist;
			plusProche = cluster;
		}
		cluster = cluster->succ;
	}
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