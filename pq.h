 /******************************************************************************
 *
 * File Name: pq.h
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION
 *
 *****************************************************************************/

 #ifndef pq_H
 #define pq_H

 #include "defs.h"
 #include "heap.h"
#include "tools.h"

void PQinit(unsigned Size);
void PQinsert(Item I);
Item PQdelmax();
void PQsort(Item pTable[], int L, int R);


#endif