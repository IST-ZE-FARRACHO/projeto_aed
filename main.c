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
#include "heap.h"
#include "liberation.h"

int main(int argc, char *argv[])
{	

	Park * park;

	int nr_eventos, a = 0, b = 0, c = 0;

	LinkedList * timeline;
	LinkedList * eventslist;
	LinkedList * carlist;
	LinkedList * liberationlist;
	LinkedList * restrictionlist; // Declares list

	park = ReadFilePark(argv[1]); // Reads, allocates, and fills park matrix

	carlist = initLinkedList();
	liberationlist = initLinkedList();
	restrictionlist = initLinkedList();

	carlist = ReadCarFile(park, argv[2], carlist);
	liberationlist = ReadLiberationFile(argv[2], liberationlist);
	restrictionlist = ReadRestrictsFile(argv[3], restrictionlist); // Sends list pointer to function

	a = lengthLinkedList(carlist);
	b = lengthLinkedList(liberationlist);
	c = lengthLinkedList(restrictionlist);
	
	nr_eventos = EventCounter(carlist, liberationlist, restrictionlist);
	printf("\nNúmero de carros: %d\n", a);
	printf("Número de libertações: %d\n", b);
	printf("Número de restrições: %d\n", c);
	printf("Número de eventos: %d\n\n", nr_eventos);

	//timeline = TimelineCreator();

//Lista de eventos:

// Enquanto a lista de eventos não estiver vazia		
	// Percorre a fila de eventos 
		// Se for a entrada de um carro
			// Calcula automaticamente o melhor lugar e percurso
			// Escreve a sequência de movimentos para o ficheiro de saída
		// Se for a saída de um carro
			// Atualiza matriz de posições
                      //Insere a posiçao da qual o carro saiu no grafo
		// Se for uma restrição nova
			// Atualiza matriz de posições

//Caminhos : algoritmo de FLoyd ou Dijkstra?

}