/******************************************************************************
 *
 * File Name: liberation.h
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION
 *
 *****************************************************************************/

#ifndef Liberation_H
#define Liberation_H

#include "defs.h"
#include "tools.h"
#include "LinkedList.h"
#include "park_config.h"


Liberation * NewLiberation(int x, int y, int z, int time);
LinkedList * ReadLiberationFile(char * file, LinkedList * liberationlist);

#endif