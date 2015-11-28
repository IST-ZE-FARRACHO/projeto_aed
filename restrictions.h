/******************************************************************************
 *
 * File Name: restrictions.h
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION
 *
 *****************************************************************************/

#ifndef Restrictions_H
#define Restrictions_H

#include "defs.h"
#include "tools.h"
#include "LinkedList.h"


Restrictions *NewRestrictions(int rest_type, int ta, char inout, int x, int y, int z);
LinkedList * ReadRestrictsFile(char * file, LinkedList * restrictionslist);

#endif