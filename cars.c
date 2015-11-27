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
		if( (p->entries[i].pos->x) == x && (p->entries[i].pos->y == y ) && (p->entries[i].pos->z) == z )
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

	newcar->pos = (Position*) malloc(sizeof(Position));

 	if(newcar->pos == NULL)
 	{
 		fprintf(stderr, "Error in malloc of entries/accesses.\n");
 		exit(1);
 	}


	strcpy(newcar->id, id);
	newcar->ta = ta;
	newcar->type = type;
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
LinkedList * ReadCarFile(Park * p, char * file, LinkedList * carlist)
{

	 FILE *f; 
	 int n, tmpta, tmpxs, tmpys, tmpzs;
	 char tmptype;
	 char tmpid[5];
	 Car * newc;
	 Car * searchcar;
	 LinkedList * aux = carlist;
	 int carnumber = 0;

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
				aux = carlist;
	
 			}
 			else printf("Not a valid entrance!\n");
 		}

 		else
 		{
 
 			if(n == 3) // Exit case -> Car is in carlist, register exit time
 			{	
 				

 				while(aux != NULL) // Searches carlist
 				{
 					searchcar = (Car*) getItemLinkedList(aux); // Gets Item from LinkedList
 					
 					if( !(strcmp(searchcar->id, tmpid))) // If the Item matches the given id
					{	
						searchcar->tb = tmpta; // Updates exit time
						carlist = insertUnsortedLinkedList(carlist, (Item) searchcar); // Inserts exir ocurrence in carlist
						break;
					}
					else
					{
						aux = aux->next; // Iterates to next element
					}

 				}
 		
 			}

 		}

 	}
 	while(n >= 3);

 	FechaFicheiro(f);

 	return carlist;
}