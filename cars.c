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
void ReadCarFile(Park * p, char * file, LinkedList * carlist, LinkedList * liberationlist)
{
	 FILE *f;
	 int tmpta, tmpxs, tmpys, tmpzs;
	 char tmptype;
	 char tmpid[5];
	 char storage[];
	 Car * newc;

	 Liberation * newliberation;

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

 		else // It is exit/liberation info
 		{

 			if( /*fscanf só ler 3 elementos*/ ) // Car is in carlist, register exit time
 			{
 				for()
 				// Atualizar com tempo de saída
 			}

 			else // Car is not in carlist, register coordinates liberation time
 			{	
 				newliberation = LiberationStructCreator(tmpxs, tmpys, tmpzs, tmpta); // Creates a new struct to save liberation info
 				insertUnsortedLinkedList(liberationlist->next, (Item) newliberation); // Inserts new liberation in liberation list
 			}

 		}			
 	}
}

/******************************************************************************
 * LiberationListCreator
 *
 * Arguments: Park, file to be read
 *
 * Returns: void
 *
 * Description: Creates and fills a car list, reading the input file
 *
 *****************************************************************************/

void CarlistCreator(Park * p, char * file)
{
	LinkedList * carlist;
	carlist = initLinkedList();

	ReadCarFile(p, file, carlist);

}

/******************************************************************************
 * LiberationListCreator
 *
 * Arguments: -
 *
 * Returns: Creates an liberation list
 *
 * Description: 
 *
 *****************************************************************************/

LinkedList * LiberationListCreator()
{

	LinkedList * liberationlist;

	liberationlist = initLinkedList();

}

/******************************************************************************
 * LiberationStructCreator
 *
 * Arguments: Liberation coordinates
 *
 * Returns: Creates an liberation structure and returns it
 *
 * Description: Allocates and fills an liberation structure
 *
 *****************************************************************************/

Liberation * LiberationStructCreator(int x, int y, int z, int time)
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
 * EventsListCreator
 *
 * Arguments: 
 *
 * Returns: Creates an event list and sorts it
 *
 * Description: Reads every other action list and creates an general event list
 *
 *****************************************************************************/

LinkedList * EventsListCreator()
{

	LinkedList * eventslist;

	eventslist = initLinkedList(); // Listas criadas aqui, para depois serem enviadas para ReadCarFile e preenchidas

	// Lê lista de carros e cria eventos de entrada e saída
	// Lê lista de restrições e cria eventos de restrição
	// Lê lista de liberações e cria eventos de liberação
	// Ordena tudo em função do time

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
