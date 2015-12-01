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

int EventCounter(LinkedList * carlist, LinkedList * liberationlist, LinkedList * restrictionlist);

void PrintNum(Item hi);

int LessNum(Item a, Item b);

Heap * TimelineCreator(int nr_eventos, LinkedList * carlist, LinkedList * liberationlist, LinkedList * restrictionlist);

Heap * ListToHeap(LinkedList * list, Heap * h, int listtype);

Event * EventCreator(Item this, int time, char type);

/* End of: Protect multiple inclusions                              */
#endif