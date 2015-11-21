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

struct _car // Struct for cars
{ 

char *id; // Vehicle identification

int ta; // Entrance moment - TA
int te; // Elapsed time - TE

char type; // Type of access required
//“C” (Cinema), “H” (Habitacão), “E” (Escritorios), “L” (Loja) ou “R”(Restauracao)

int xs;  // Entrance coordinates
int ys; 
int zs;

};

/******************************************************************************
 * ReadCarFile()
 *
 * Arguments: Car file
 *			  Car list
 *
 * Returns: Updated car list
 *
 * Description: Reads car file and stores info into a list
 *
 *****************************************************************************/

ReadCarFile()
{
	 FILE *f;
	 int tmpta, tmpxs, tmpys, tmpzs;
	 char tmptype;
	 char tmpid[5];
	 char storage[]

 	 f = fopen(name, mode);

 	 if (f == NULL) 
 	 {
  	  fprintf(stderr, "Error: Unable to open file %s\n.", name);
  	  exit(1);
 	 }

 	while(fscanf(storage, "%s %d %c %d %d %d", &tmpid, &tmpta, &tmptype, &tmpxs, &tmpys, &tmpzs))
 		if(tmptype != 'S')
 			NewCar(tmpid, tmpta, tmptype, tmpxs, tmpys, tmpzs);
 		else
 			{
 				if // O carro já existir, libertar o seu lugar

 				else // Não existir, libertar as coordenadas dadas
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

// Main para testes
int main()
{
	Car * teste;

	teste = NewCar("NQ", 0, 'H', 0, 0, 0);

	printf("%s %d %c %d %d %d\n", teste->id, teste->ta, teste->type, teste->xs, teste->ys, teste->zs);

	return 0;
}
