#ifndef CLUSTERFIRST_H
#define CLUSTERFIRST_H

#include "Objet.h"

typedef struct _Cluster
{
	struct Objet * idObjet;
	struct _Cluster * succ;
} Cluster;





#endif //CLUSTERFIRST_H
