/******************************************************************************
 *
 * File Name: time.h
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION
 *
 *****************************************************************************/

#ifndef TimeHeader
#define TimeHeader

#include "defs.h"
#include "LinkedList.h"
#include "tools.h"
#include "park_config.h"

void ListsCreator(Park * p, char * carfile, char * restrictionfile, LinkedList * carlist, LinkedList * liberationlist, LinkedList * restrictionlist);

LinkedList * TimelineCreator();

//LinkedList * TimelineCreator(Park * p, char * file);

/* End of: Protect multiple inclusions                              */
#endif