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
	Heap * timeline;

	int nr_eventos, a = 0, b = 0, c = 0;

	LinkedList * eventslist, * carlist, * liberationlist, * restrictionlist; // Declares list

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

	timeline = TimelineCreator(nr_eventos, carlist, liberationlist, restrictionlist);
	
	PrintHeap(timeline);

	
	/* while(não chegar ao último elemento do heap)
	{

		for(primeiro elemento, ultimo elemento, elemento++)
		{
			if(é uma entrada de carro)
			{
				calculate best lugar
				calculate best percurso
				write output file
			}
			else if(é uma saída de carro)
			{	
				atualiza lista de carros
				atualiza o grafo, marcando lugar como vago
			}
			else if(é uma nova restrição)
			{

				atualiza grafo das ligações
			}
			else if(acabou uma restrição)
			{
				atualiza o grafo das ligações
			}
			else if(libertação de lugar)
			{

				atualiza grafo das posições
			}

	}	*/

	// Percorre a fila de eventos 
		// Se for a entrada de um carro
			// Calcula automaticamente o melhor lugar e percurso
			// Escreve a sequência de movimentos para o ficheiro de saída
		// Se for a saída de um carro
			// Atualiza matriz de posições
                      //Insere a posiçao da qual o carro saiu no grafo
		// Se for uma restrição nova
			// Atualiza matriz de posições

}