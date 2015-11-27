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
#include "heap.h"

void ListsCreator(Park * p, char * carfile, char * restrictionfile, LinkedList * carlist, LinkedList * liberationlist, LinkedList * restrictionlist);

LinkedList * TimelineCreator();

int EventCounter(LinkedList * carlist, LinkedList * liberationlist, LinkedList * restrictionlist);

void PrintNum(Item hi);

int LessNum(Item a, Item b);

/* End of: Protect multiple inclusions                              */
#endif