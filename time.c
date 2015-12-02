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

#define CAR 1
#define LIBERATION 2
#define RESTRICTION 3

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

Heap * TimelineCreator(int nr_eventos, LinkedList * carlist, LinkedList * liberationlist, LinkedList * restrictionlist)
{	
	int i;
	Heap * h;
	h = NewHeap(nr_eventos, LessNumEvento, PrintNumEvento);

	ListToHeap(carlist, h, CAR);
	ListToHeap(liberationlist, h, LIBERATION);
	ListToHeap(restrictionlist, h, RESTRICTION);

	return HeapSort(h);
}

Heap * ListToHeap(LinkedList * list, Heap * h, int listtype)
{		
		Event * event;

		if(list == NULL)
			return;
		
		if(listtype == CAR)
		{	
			Car * item1;
			item1 = (Car*) getItemLinkedList(list);
			event = EventCreator(item1, item1->ta, item1->inout);

		}
		else if(listtype == RESTRICTION)
		{

			Restrictions * item2;
			item2 = (Restrictions*) getItemLinkedList(list);
			event = EventCreator(item2, item2->ta, item2->inout);
			
		}
		else if(listtype == LIBERATION)
		{
			Liberation * item3;
			item3 = (Liberation*) getItemLinkedList(list);
			event = EventCreator(item3, item3->time, 'L');

		}

		Insert(h, event);
		ListToHeap(getNextNodeLinkedList(list), h, listtype);

		return h;
}

Event * EventCreator(Item this, int time, char type)
{
	Event * newevent;
	newevent = (Event*) malloc(sizeof(Event));
	if (newevent == NULL) 
	{
		fprintf(stderr, "Error in malloc of new event.\n");
		exit(1);
	}

	newevent->object = this;
	newevent->time = time;
	newevent->type = type;

	return newevent;

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

int LessNumEvento(Item a, Item b) // If a < b return 1
{

  Event aa, bb;

  aa = *( (Event *) a );
  bb = *( (Event *) b );



  return (aa.time < bb.time);
}

void PrintNumEvento(Item hi)
{
  Event num;

  num = *((Event *) hi);
  printf("%d", num.time);

  return;
}

void exchEvento(Item *i, Item *j)
{	

  int temp;

  Event * aa;
  Event * bb;

  aa = ( (Event *) i );
  bb = ( (Event *) j );

  temp = aa->time;
  aa->time = bb->time;
  bb->time = temp;

}