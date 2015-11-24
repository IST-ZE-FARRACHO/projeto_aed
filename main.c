/******************************************************************************
 *
 * File Name: main.c
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION
 *		Main program
 *
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "time.h"
#include "defs.h"
#include "tools.h"
#include "cars.h"
#include "restrictions.h"
#include "LinkedList.h"
#include "park_config.h"

int main(int argc, char *argv[])
{	

	Park * park;
	LinkedList * timeline;
	LinkedList * eventslist;
	LinkedList * carlist;
	LinkedList * liberationlist;
	LinkedList * restrictionlist;

	carlist = ListCreator();
	liberationlist = ListCreator();
	restrictionlist = ListCreator();
	eventslist = ListCreator();

	park = ReadFilePark(argv[1]); // Reads, allocates, and fills park matrix

	ListCreator(park, argv[2], argv[3], carlist, liberationlist, restrictionlist); // Reads, allocates, and fills event list

	timeline = TimelineCreator();
	
// Enquanto a lista de eventos não estiver vazia		
	// Percorre a fila de eventos 
		// Se for a entrada de um carro
			// Calcula automaticamente o melhor lugar e percurso
			// Escreve a sequência de movimentos para o ficheiro de saída
		// Se for a saída de um carro
			// Atualiza matriz de posições
		// Se for uma restrição nova
			// Atualiza matriz de posições



}