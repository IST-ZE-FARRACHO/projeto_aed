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
 * CheckEntrance()
 *
 * Arguments: Entrance Vector
 *			  New Entrance
 *
 * Returns: True or false, depending on Entrance Check result
 *
 * Description: Checks if an entrance is valid
 *
 *****************************************************************************/

int CheckEntrance(Park * p, int x, int y, int z)
{
	int i;

	for(i = 0; i <= p->E; i++)
	{
		if( (p->entries[i].xs) == x && (p->entries[i].ys == y ) && (p->entries[i].zs) == z )
			return 1;
	}

	return 0;	
}

/******************************************************************************
 * NewCar()
 *
 * Arguments: Car info
 *
 * Returns: Pointer to created Car
 *
 * Description: Allocates a new Car structure
 *
 *****************************************************************************/

Car * NewCar(char * id, int ta, char type, int xs, int ys, int zs)
{
	Car * newcar;

	newcar = (Car *) malloc(sizeof(Car));
	if (newcar == NULL) 
	{
		fprintf(stderr, "Error in malloc of new car.\n");
		exit(1);
	}

	newcar->id = (char *) malloc(sizeof(char)*4);
	if (newcar->id == NULL) 
	{
		fprintf(stderr, "Error in malloc of new car id.\n");
		exit(1);
	}

	strcpy(newcar->id, id);
	newcar->ta = ta;
	newcar->type = type;
	newcar->xs = xs;
	newcar->ys = ys;
	newcar->zs = zs;

	return (newcar);
}

/******************************************************************************
 * LiberationStructCreator
 *
 * Arguments: Liberation coordinates
 *
 * Returns: Created liberation structure
 *
 * Description: Allocates and fills an liberation structure
 *
 *****************************************************************************/

Liberation * NewLiberation(int x, int y, int z, int time)
{
	Liberation * libert;

	libert = (Liberation *) malloc(sizeof(Liberation)); //allocates memory for the struct

	if (libert == NULL)
	{
		fprintf(stderr, "Error in malloc of liberation struct.\n");
		exit(1);
	}

	libert->time = time;
	libert->xs = x;
	libert->ys = y;
	libert->zs = z;

	return libert;

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
void ReadCarFile(Park * p, char * file, LinkedList * carlist, LinkedList * liberationlist)
{

	 FILE *f; 
	 int n, tmpta, tmpxs, tmpys, tmpzs;
	 char tmptype;
	 char tmpid[5];
	 Car * newc;
	 Car * searchcar;
	 LinkedList * aux;

	 Liberation * newliberation;

 	f = AbreFicheiro(file, "r");

 	do{	
 		n = fscanf(f, "%s   %d %c %d %d %d", tmpid, &tmpta, &tmptype, &tmpxs, &tmpys, &tmpzs); // Reads each line
 		if( n < 3 ) continue;

 		if(tmptype != 'S') // If it is not exit info (it is an entrance)
 		{	
 			if( CheckEntrance(p, tmpxs, tmpys, tmpzs) ) // Checks if it is a valid entrance, if it's not, ignore
 			{
				newc = NewCar(tmpid, tmpta, tmptype, tmpxs, tmpys, tmpzs); // Creates new car
				carlist = insertUnsortedLinkedList(carlist, (Item) newc); // Inserts new car in given car list
				newc = (Car*) getItemLinkedList(carlist);
	
 			}
 			else
 			{
 				printf("Not a valid entrance!\n");
 			}

 		}

 		else // It is an exit/liberation case
 		{
 
 			if(n == 3) // Exit case -> Car is in carlist, register exit time
 			{	

 				while(carlist != NULL) // Searches carlist
 				{
 					searchcar = (Car*) getItemLinkedList(carlist); // Gets Item from LinkedList
 					
 					if( !(strcmp(searchcar->id, tmpid))) // If the Item matches the given id
					{	
						searchcar->tb = tmpta; // Updates exit time
						EditItemLinkedList(carlist, (Item) searchcar); // Sends it back to the list
						break;
					}
					else
					{
						carlist = carlist->next; // Iterates to next element
					}

 				}
 		
 			}

 			else // Liberation case -> Car is not in carlist, register coordinates liberation time
 			{	
 				newliberation = NewLiberation(tmpxs, tmpys, tmpzs, tmpta); // Creates a new struct to save liberation info
 				liberationlist = insertUnsortedLinkedList(liberationlist, (Item) newliberation); // Inserts new liberation in liberation list
 				newliberation = (Liberation*) getItemLinkedList(liberationlist);
 				
 			}

 		}

 	}
 	while(n >= 3);

 	FechaFicheiro(f);

 	return;
}