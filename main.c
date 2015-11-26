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

	carlist = initLinkedList();
	liberationlist = initLinkedList();
	restrictionlist = initLinkedList();
	eventslist = initLinkedList();
	
	park = ReadFilePark(argv[1]); // Reads, allocates, and fills park matrix*/

	//ListCreator(park, argv[2], argv[3], carlist, liberationlist, restrictionlist); // Reads, allocates, and fills event list

//timeline = TimelineCreator();

	//Grafos:

	//Cria um grafo com o número de caminhos do parque;
	//Cria um vetor da estrutura Edge para as arestas
	//Percorre a matriz e insere todas as posiçoes que sejam ou ROAD ou SPOT ou ACCESS ou ENTRY no grafo
		//Vê logo quais as arestas para cada posição e adiciona ao vetor de arestas (Verificar em : x+1 (se x<(Colunas-2), y+1 (se y<(Linhas-2)))
	//Adiciona cada aresta no vetor à lista de adjacências;





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