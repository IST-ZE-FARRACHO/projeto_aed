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
 * EventCounter
 *
 * Arguments: 
 *
 * Returns: 
 *
 * Description: 
 *
 *****************************************************************************/

int EventCounter (LinkedList * carlist, LinkedList * liberationlist, LinkedList * restrictionlist, Park * p)
{

	int i;
	
	for( i = 0; i < 3; i++)
	{

	}


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

LinkedList * TimelineCreator(int nr_eventos)
{	
	Heap * h;
	h = NewHeap(nr_eventos, LessNum, PrintNum);

}

/******************************************************************************
 * LessNumero()
 *
 * Arguments: a, b - 2 Items to be compared
 *
 * Returns: Integer with the results of the comparison
 *
 * Side-Effects: none
 *
 * Description: Comparison function with abstract type to be passed as argument;
 *              Function is specific for "int" variables
 *
 *****************************************************************************/

int LessNum(Item a, Item b) // If a < b return 1
{
  int aa, bb;

  aa = *((int *) a);
  bb = *((int *) b);

  return (aa < bb);
}