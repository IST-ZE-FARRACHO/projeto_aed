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
#include "LinkedList.h"
#include "tools.h"

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
	 int n, tmpta, tmpxs, tmpys, tmpzs;
	 char tmptype;
	 char tmpid[5];
	 Car * newc;
	 Car * searchcar;
	 LinkedList * aux;

	 Liberation * newliberation;

 	f = AbreFicheiro(file, "r");

 	do{	
 		n = fscanf(f, "%s %d %c %d %d %d", tmpid, &tmpta, &tmptype, &tmpxs, &tmpys, &tmpzs); // Reads each line


 		if(tmptype != 'S') // If it is not exit info (it is an entrance)
 		{	
 			if( CheckEntrance(p, tmpxs, tmpys, tmpzs) != 0 ) // Checks if it is a valid entrance, if it's not, ignore
 			{
				newc = NewCar(tmpid, tmpta, tmptype, tmpxs, tmpys, tmpzs); // Creates new car
				insertUnsortedLinkedList(carlist, (Item) newc); // Inserts new car in given car list
 			}

 		}

 		else // It is an exit/liberation case
 		{

 			if(n == 3) // Car is in carlist, register exit time
 			{	

 				while(carlist != NULL) // Percorre a lista de carros
 				{
 					searchcar = (Car*) getItemLinkedList(carlist); // Variável auxiliar searchcar é o resultado de sacar o item da lista

 					if( (searchcar->id) == tmpid) // Se encontrar na lista o carro com o mesmo identificador
					{	
						searchcar->tb = tmpta; // Novo tempo de saída é igual ao tempo lido
						EditItemLinkedList(carlist, (Item) searchcar); // Atualiza o tempo de saída desse carro na lista
					}

					carlist = carlist->next;

 				}
 		
 			}

 			else // Car is not in carlist, register coordinates liberation time
 			{	
 				newliberation = LiberationStructCreator(tmpxs, tmpys, tmpzs, tmpta); // Creates a new struct to save liberation info
 				insertUnsortedLinkedList(liberationlist, (Item) newliberation); // Inserts new liberation in liberation list
 			}

 		}

 	}while(n >= 3);

 	return;

}

/******************************************************************************
 * ListCreator
 *
 * Arguments: 
 *
 * Returns: Abstract created list
 *
 * Description: Creates an abstract list
 *
 *****************************************************************************/

LinkedList * ListCreator()
{
	LinkedList * abstractlist;

	abstractlist = initLinkedList();

	return abstractlist;	

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

LinkedList * EventsListCreator(Park * p, char * file)
{

	LinkedList * eventslist;
	LinkedList * carlist;
	LinkedList * liberationlist;
	LinkedList * restrictionlist;

	carlist = ListCreator();
	liberationlist = ListCreator();
	//restrictionlist = ListCreator();
	eventslist = ListCreator();

	ReadCarFile(p, file, carlist, liberationlist);

	// Lê lista de carros e cria eventos de entrada e saída
	// Lê lista de restrições e cria eventos de restrição
	// Lê lista de liberações e cria eventos de liberação

	return eventslist;

}



LinkedList * EventsListSort(LinkedList * list)
{

	// Use a function to sort list

	return list; // Returns sorted list
}

/******************************************************************************
 * TimelineCreator
 *
 * Arguments: Park, File
 *
 * Returns: Pointer to created Car
 *
 * Description: Allocates a new Car structure
 *
 *****************************************************************************/

LinkedList * TimelineCreator(Park * p, char * file)
{

	LinkedList * eventslist;
	LinkedList * sortedeventslist;

	eventslist = EventsListCreator(p, file);
	sortedeventslist = EventsListSort(eventslist);

	return sortedeventslist;
}


int main(int argc, char *argv[])
{
	
	Park * park;
	LinkedList * timeline;

	park = ReadFilePark(argv[1]);

	timeline = TimelineCreator(park, argv[2]);

	return;


}
