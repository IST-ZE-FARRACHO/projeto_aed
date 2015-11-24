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
#include "defs.h"
#include "LinkedList.h"
#include "tools.h"

void ReadCarFile(Park * p, char * file, LinkedList * carlist, LinkedList * liberationlist);

int CheckEntrance(Park * p, int x, int y, int z);

Car * NewCar(char * id, int ta, char type, int xs, int ys, int zs);

Liberation * NewLiberation(int x, int y, int z, int time);

/* End of: Protect multiple inclusions                              */
#endif