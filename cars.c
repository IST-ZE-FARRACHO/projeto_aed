/******************************************************************************
 *
 * File Name: cars.c
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION
 *		reads info about car entrance/exit/unparking
 *
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cars.h"
#include "park_config.h"
#include "defs.h"

/******************************************************************************
 * ReadCarFile()
 *
 * Arguments: Park
 *			  Car file
 *			  Car list
 *
 * Returns: Updated car list
 *
 * Description: Reads car file and stores info into a list
 *
 *****************************************************************************/

void ReadCarFile(Park * p, char * file, Car * carlist)
{
	 FILE *f;
	 int tmpta, tmpxs, tmpys, tmpzs;
	 char tmptype;
	 char tmpid[5];
	 char storage[]
	 Car * newc;

 	 f = fopen(file, mode); // Opens vehicles input file

 	 if (f == NULL) 
 	 {
  	  fprintf(stderr, "Error: Unable to open car file %s\n.", name);
  	  exit(1);
 	 }

 	while(fscanf(storage, "%s %d %c %d %d %d", &tmpid, &tmpta, &tmptype, &tmpxs, &tmpys, &tmpzs)) // Reads each line
 	{	

 		if(tmptype != 'S') // If it is not exit info (it is an entrance)
 		{	
 			if( CheckEntrance(p, tmpxs, tmpys, tmpzs) == 1 ) // Checks if it is a valid entrance, if it's not, ignore
 			{
				newc = NewCar(tmpid, tmpta, tmptype, tmpxs, tmpys, tmpzs); // Creates new car
				// Insert car in carlist
 			}

 		}

 		else // It is exit info
 		{

 			if() // Car is in carlist, free its coordinates
 			{

 			}

 			else // Car doesn't exist, free given parking spot (read coordinates)
 			{

 			}

 		}			
 	}
}


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
			return i;
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
	if (newcar == ((Car*) NULL)) 
	{
		fprintf(stderr, "Error in malloc of new car.\n");
		exit(1);
	}

	strcpy(newcar->id, id);
	newcar->ta = ta;
	newcar->type = type;
	newcar->xs = xs;
	newcar->ys = ys;
	newcar->zs = zs;

}


/******************************************************************************
 * FreeSpot()
 *
 * Arguments: Park
 *			  Spot to liberate (coordinates)
 * 			  Time when spot will be liberated
 *
 * Returns: -
 *
 * Description: Liberates a given parking spot
 *
 *****************************************************************************/
void FreeSpot(Park * p, int xs, int ys, int zs, int time)
{

}


/******************************************************************************

								MAIN PARA TESTES

 *****************************************************************************/
int main()
{
	Car * teste;

	teste = NewCar("NQ", 0, 'H', 0, 0, 0);

	printf("%s %d %c %d %d %d\n", teste->id, teste->ta, teste->type, teste->xs, teste->ys, teste->zs);

	return 0;
}
