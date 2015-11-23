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

FILE *AbreFicheiro(char *name, char *mode);
Restrictions *NewRestrictions(int rest_pos, int rest_floors);
void ReadRestrictsFile(Restrictions * rest, char * file);

#endif