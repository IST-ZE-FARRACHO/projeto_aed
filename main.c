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
#include "defs.h"
#include "tools.h"

int main(int argc, char *argv[]))
{	

	Park * park;
	LinkedList * timeline;

	park = ReadFilePark(argv[1]);

	timeline = TimelineCreator(park, argv[2]);
	
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