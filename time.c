/******************************************************************************
 *
 * File Name: time.c
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION
 *		Time management file
 *
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "time.h"

/******************************************************************************
 * EventsListCreator
 *
 * Arguments: 
 *
 * Returns: Creates an event list and sorts it
 *
 * Description: Reads every other action list and creates an general event list
 *
 *****************************************************************************/

void ListsCreator(Park * p, char * carfile, char * restrictionfile, LinkedList * carlist, LinkedList * liberationlist, LinkedList * restrictionlist)
{

	ReadCarFile(p, carfile, carlist, liberationlist); // Carlist and liberation list created

	ReadRestrictsFile(restrictionfile, restrictionlist); // Restriction list created

}


/******************************************************************************
 * TimelineCreator
 *
 * Arguments: 
 *
 * Returns: 
 *
 * Description: 
 *
 *****************************************************************************/

LinkedList * TimelineCreator()
{


}