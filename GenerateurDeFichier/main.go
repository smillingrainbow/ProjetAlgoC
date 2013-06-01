package main

import (
	"flag"
	"fmt"
	"math"
	"math/rand"
	"os"
	"time"
)

func Initialisation() uint {
	var (
		nbLigne *uint
	)
	nbLigne = flag.Uint("nbLigne", 100, "nombre de lignes à générer")
	flag.Parse()
	return *nbLigne

}

func main() {

	var (
		nbLigne uint
		result  [][]int
		r       *rand.Rand
		i       uint
	)

	nbLigne = Initialisation()

	result = make([][]int, nbLigne)

	r = rand.New(rand.NewSource(time.Now().UnixNano()))

	for i = 0; i < nbLigne; i++ {
		result[i] = make([]int, 3)
		result[i][0] = int(math.Mod(float64(r.Int()), 200)) - 100
		result[i][1] = int(math.Mod(float64(r.Int()), 200)) - 100
		result[i][2] = int(math.Mod(float64(r.Int()), 9)) + 1

	}

	ecrireFichier("fichierTest", nbLigne, result)
}

func ecrireFichier(nomDeFichier string, nbLigne uint, contenu [][]int) {
	var (
		fichier *os.File
		err     error
		i       uint
	)
	fichier, err = os.Create(nomDeFichier)

	_, err = fichier.WriteString(fmt.Sprintf("%d \n", nbLigne))
	if err != nil {
		panic(fmt.Sprint("[first line]", err))
	}
	defer fichier.Close()

	for i = 0; i < nbLigne; i++ {

		_, err = fichier.WriteString(fmt.Sprintf("%.5d\t", i))
		if err != nil {
			panic(fmt.Sprint("[write]", err))
		}

		_, err = fichier.WriteString(fmt.Sprintf("%+.5d\t", contenu[i][0]))
		if err != nil {
			panic(fmt.Sprint("[write]", err))
		}
		_, err = fichier.WriteString(fmt.Sprintf("%+.3d\t", contenu[i][1]))
		if err != nil {
			panic(fmt.Sprint("[write]", err))
		}
		_, err = fichier.WriteString(fmt.Sprintf("%.3d\t", contenu[i][2]))
		if err != nil {
			panic(fmt.Sprint("[write]", err))
		}

		_, err = fichier.WriteString("\n")
		if err != nil {
			panic(fmt.Sprint("[first line]", err))
		}
	}
}
