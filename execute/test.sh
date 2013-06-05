#!/bin/ksh

# création du dossier de resultat
echo -e "ClusterFirst\tRootFirst" > resultatDistance
echo -e "ClusterFirst\tRootFirst" > resultatTemps

for ((i=100; $i<=200; i=$i+100 )); do
    for ((j=20; $j<=30; j=$j+10 )); do
        for ((k=1; $k<=20; k++ )); do
            #generer fichier de test
            ./GenerateurDeFichier -nbLigne=$i

            #cluster first
            time -p ./ClusterFirst $j ./fichierTest > tmpCluster 2> tmpClusterTime

            #root first
            time -p ./RootFirst $j ./fichierTest > tmpRoot 2> tmpRootTime

            #récupération des données
            cat tmpCluster | grep "La distance a parcourir est :" | cut -d " " -f 7 | tr -d "\n"  >> resultatDistance
            echo -e "\t"| tr -d "\n" >> resultatDistance
            cat tmpRoot    | grep "La distance a parcourir est :" | cut -d " " -f 7 | tr -d "\n"  >> resultatDistance
            echo >> resultatDistance

            cat tmpClusterTime | grep "real" | cut -d " " -f 2 | tr -d "\n" >> resultatTemps
            echo -e "\t"| tr -d "\n" >> resultatTemps
            cat tmpRootTime | grep "real" | cut -d " " -f 2 | tr -d "\n" >> resultatTemps
            echo >> resultatTemps
        done
    done
done
rm tmp*
