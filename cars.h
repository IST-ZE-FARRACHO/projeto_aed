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

void ReadCarFile(Park * p, char * file, Car * carlist);

int CheckEntrance(Park * p, int x, int y, int z);

Car * NewCar(char * id, int ta, char type, int xs, int ys, int zs);

void FreeSpot(Park * p, int xs, int ys, int zs, int time);

/* End of: Protect multiple inclusions                              */
#endif