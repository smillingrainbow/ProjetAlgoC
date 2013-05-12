#ifndef CLUSTERFIRST_H
#define CLUSTERFIRST_H

#include "Objet.h"

typedef struct _Cluster
{
	struct Objet * ptrC;
	struct _Cluster * succ;
} Cluster;





#endif //CLUSTERFIRST_H
