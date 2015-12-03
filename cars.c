/******************************************************************************
 *
 * File Name: cars.c
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION: Reads info about car entrance/exit/unparking
 *
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cars.h"
#include "LinkedList.h"
#include "tools.h"


/******************************************************************************
 * NewCar
 *
 * Arguments: Car info
 *
 * Returns: Pointer to created Car
 *
 * Description: Allocates a new Car structure
 *
 *****************************************************************************/

Car * NewCar(char * id, int ta, char type, char inout, int xs, int ys, int zs)
{
	Car * newcar;

	newcar = (Car *) malloc(sizeof(Car));
	if (newcar == NULL) 
	{
		fprintf(stderr, "Error in malloc of new car.\n");
		exit(0);
	}

	newcar->id = (char *) malloc((strlen(id)+1)*(sizeof(char)));
	if (newcar->id == NULL) 
	{
		fprintf(stderr, "Error in malloc of new car id.\n");
		exit(0);
	}

	newcar->pos = (Position*) malloc(sizeof(Position));
 	if(newcar->pos == NULL)
 	{
 		fprintf(stderr, "Error in malloc of entries/accesses.\n");
 		exit(0);
 	}


	strcpy(newcar->id, id);
	newcar->ta = ta;
	newcar->type = type;
	newcar->inout = inout;
	newcar->pos->x = xs;
	newcar->pos->y = ys;
	newcar->pos->z = zs;

	return (newcar);
}



/******************************************************************************
 * ReadCarFile()
 *
 * Arguments: Park
 *			  Car file
 *			  Car list
 *			  Liberation list
 *
 * Returns: Updated car list and liberation list
 *
 * Description: Reads car file and stores info into a list
 *
 *****************************************************************************/
LinkedList * ReadCarFile(char * file, LinkedList * carlist)
{

<<<<<<< HEAD
	FILE *f;
	int n, tmpta, tmpxs, tmpys, tmpzs;
	char tmptype;
	char tmpid[5];
	Car * newc;
	Car * searchcar;
	int carnumber = 0;

	if(tmpid == NULL) 
	{
		fprintf(stderr, "Error in malloc of tmpid.\n");
		exit(1);
	}

 	f = OpenFile(file, "r");

 	do{	
 		
<<<<<<< HEAD
 		n = fscanf(f, "%s %d %c %d %d %d", tmpid, &tmpta, &tmptype, &tmpxs, &tmpys, &tmpzs); // Reads each line
 		if( n < 3 ) continue; // If data is not in correct format, skip

 		if(tmptype != 'S') // If it is not exit info (it is an entrance)
 		{

				newc = NewCar(tmpid, tmpta, tmptype, 'E', tmpxs, tmpys, tmpzs); // Creates new car structure
				carlist = insertUnsortedLinkedList(carlist, (Item) newc); // Inserts new car in given car list
 		}



 		if(n == 3) // Exit case -> Car is in carlist, register exit time
 		{			
 						searchcar = getItemLinkedList(carlist);
						searchcar->inout = 'S'; // Car movement becomes an exit movement
						searchcar->ta = tmpta; // Updates exit time
						carlist = insertUnsortedLinkedList(carlist, (Item) searchcar); // Inserts exir ocurrence in carlist
 		}

  	}
 	while(n >= 3);

 	CloseFile(f);

 	return carlist;
}

void FreeCar(Item this)
{
	this = (Car*) this;
	free(this->pos);
	free(this->id);
	//free(carro);

	return;
}