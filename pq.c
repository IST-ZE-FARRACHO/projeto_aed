/******************************************************************************
 *
 * File Name: pq.c
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION
 *		deals with priority queues
 *
 *****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "pq.h"
 
static Item *queue;
static int free_h;  //number of elements on the heap
static int hsize;


void PQinit(unsigned Size)
{
	queue = (Item *) malloc(Size*sizeof(Item));
	hsize = Size;
	free = 0;
}

void PQinsert(Item I)
{    //inserts new element at the end and fixes the order
	if((free_h+1) < hsize)
	{
		queue[free_h] = I;
		FixUp(queue, free_h);
		free_h++;
	}
}


Item PQdelmax()
{
	exch(queue[0], queue[free_h-1]);
	FixDown(queue, 0, free_h-1);
	return queue[--free_h];
}

Item PQdelmin()
{
	return queue[--free];
}

void PQsort(Item pTable[], int L, int R)
{
	int Aux;
	PQinit(R-L+1);
	for(Aux = L; Aux <= R; Aux++)
		PQinsert(pTable[Aux]);
	for(Aux = R; Aux >= L; Aux--)
		pTable[Aux] = PQdelmax();
}

int PQempty()
{
	if(free_h == 0)
		return 1;
}

void PQdec(int w)
{
	FixDown(queue, w, free_h-1);
}

