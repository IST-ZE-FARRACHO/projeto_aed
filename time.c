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
 * EventCounter
 *
 * Arguments: 
 *
 * Returns: 
 *
 * Description: 
 *
 *****************************************************************************/

int EventCounter(LinkedList * carlist, LinkedList * liberationlist, LinkedList * restrictionlist)
{
	int a, b, c;

	a = lengthLinkedList(carlist);
	b = lengthLinkedList(liberationlist);
	c = lengthLinkedList(restrictionlist);

	return a + b + c;
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


void PrintNum(Item hi)
{
  int num;

  num = *((int *) hi);
  printf("%3d", num);

  return;
}