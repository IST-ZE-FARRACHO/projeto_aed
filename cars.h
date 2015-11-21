/******************************************************************************
 *
 * File Name: cars.h
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION
 *
 *****************************************************************************/

#ifndef CarsHeader
#define CarsHeader

#include "park_config.h"

typedef struct _car Car;

int CheckEntrance(Park * p, int x, int y, int z);

Car * NewCar(char * id, int ta, char type, int xs, int ys, int zs);

/* End of: Protect multiple inclusions                              */
#endif