#!/bin/bash

#while IFS=: read cluster root < resultatDistance | tail -n  
#do  
	for ((i=0; $i<80; i=$i+20)); do

		cluster=`cat resultatDistance | head -n $(($i+2)) | tail -n 1 | cut -d "	" -f 1`
		root=`cat resultatDistance | head -n $(($i+2)) | tail -n 1 | cut -d "	" -f 2`
		#calcul de gap min, max et moy pour cluster 
		minCluster=$(((($root - $cluster) * 100)/$cluster));
		minRoot=$(((($cluster - $root) * 100)/$root));
		maxCluster=$minCluster;
		maxRoot=$minRoot;
		comptC=0;
		comptR=0;
		gapMoyC=0;
		gapMoyR=0;
		gapGenC=0;
		gapGenR=0;
		for ((j=0 ; $j<20 ; j++)); do
			#echo -e "$i \t $j $(($i + $j +2))"
			cluster=`cat resultatDistance | head -n $(($i+$j+2)) | tail -n 1 | cut -d "	" -f 1`
			root=`cat resultatDistance | head -n $(($i+$j+2)) | tail -n 1 | cut -d "	" -f 2`
			gapC=$(((($root - $cluster) * 100)/$cluster))
			gapR=$(((($cluster - $root) * 100)/$root))
			#echo -e "cluster : $cluster \t root : $root"
			if [[ "$gapC" -lt "$minCluster" ]]; then
			  	minCluster=$gapC;
			fi
			if [[ "$gapC" -gt "$maxCluster" ]]; then
				maxCluster=$gapC;
			fi
			if [[ "$cluster" -lt "$root" ]]; then
				gapMoyC=$(($gapMoyC + $gapC));
				comptC=$(($comptC + 1));
				#echo "comptC : $comptC"
			fi

			if [[ "$gapR" -lt "$minRoot" ]]; then
			  	minRoot=$gapR
			fi
			if [[ "$gapR" -gt "$maxRoot" ]]; then
				maxRoot=$gapR
			fi
			if [[ "$root" -lt "$cluster" ]]; then
				gapMoyR=$(($gapMoyR + $gapC));
				comptR=$(($comptR + 1));
				#echo "comptR : $comptR"
			fi
			if [[ "$cluster" -gt "$root" ]]; then
				gap=$(((($cluster - $root)*100)/ $cluster));
				gapGenC=$(($gapMoyC+ $gap))
			fi
			if [[ "$root" -gt "$cluster" ]]; then
				gap=$(((($root - $cluster)*100)/ $root));
				gapGenR=$(($gapMoyR+ $gap))
			fi
		done
		if [[ $comptC != 0 ]]; then
			gapMoyC=$(($gapMoyC / $comptC))
		fi
		if [[ gapGenC != 0 ]]; then
			gapGenC=$(($gapGenC / 20))
		fi
		echo -e "minCluster : $minCluster \t maxCluster : $maxCluster \t gapMoy : $gapMoyC \t gapCluster : $gapGenC"

		if [[ $comptC != 0 ]]; then
			gapMoyR=$(($gapMoyR / $comptR));
		fi
		if [[ gapGenR != 0 ]]; then
			gapGenr=$(($gapGenR / 20))
		fi
		echo  -e "minRoot : $minRoot \t maxRoot : $maxRoot \t gapMoy : $gapMoyR \t gaproot : $gapGenR"

	done

# done <  resultatDistance | tail -n 80