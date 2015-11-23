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

 /******************************************************************************
 * AbreFicheiro ()
 *
 * Arguments: nome - pointer to string containing name of file to open
 *            mode - mode to use to open the file
 * Returns: FILE * - handle to file opened
 * Side-Effects: input file is opened
 *
 * Description: Open file for reading, returns handle
 *
 *****************************************************************************/

FILE *AbreFicheiro(char *name, char *mode)
{
  	FILE *f;

 	 f = fopen(name, mode);

 	 if (f == NULL) 
 	 {
  	  fprintf(stderr, "Error: Unable to open park-config file %s\n.", name);
  	  exit(1);
 	 }
 	 return f;
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

	return (newcar);
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
void ReadCarFile(Park * p, char * file, LinkedList * carlist)
{
	 FILE *f;
	 int tmpta, tmpxs, tmpys, tmpzs;
	 char tmptype;
	 char tmpid[5];
	 char storage[];
	 Car * newc;

 	f = AbreFicheiro(file, "r");

 	while(fscanf(f, "%s %d %c %d %d %d", tmpid, &tmpta, &tmptype, &tmpxs, &tmpys, &tmpzs) >= 3) // Reads each line
 	{	

 		if(tmptype != 'S') // If it is not exit info (it is an entrance)
 		{	
 			if( CheckEntrance(p, tmpxs, tmpys, tmpzs) != 0 ) // Checks if it is a valid entrance, if it's not, ignore
 			{
				newc = NewCar(tmpid, tmpta, tmptype, tmpxs, tmpys, tmpzs); // Creates new car
				insertUnsortedLinkedList(carlist->next, (Item) newc); // Inserts new car in given car list
 			}

 		}

 		else // It is exit info
 		{

 			if() // Car is in carlist, register exit time
 			{
 				// Percorrer lista até encontrar carro dado
 				// Atualizar com tempo de saída
 			}

 			else // Car is not in carlist, register coordinates liberation time
 			{

 			}

 		}			
 	}
}

LinkedList * CarlistCreator(Park * p, char * file)
{
	LinkedList * carlist;
	carlist = initLinkedList();

	ReadCarFile(p, file, carlist);
	
}

LinkedList * EventsListCreator()
{

	LinkedList * eventslist;

	eventslist = initLinkedList(); // Listas criadas aqui, para depois serem enviadas para ReadCarFile e preenchidas

	// Lê lista de carros e cria eventos de entrada e saída
	// Lê lista de restrições e cria eventos de restrição
	// Lê ficheiro de movimentações e cria evento de liberação de lugar de carro que não está na lista
	// Ordena tudo

	return eventslist;

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
