/******************************************************************************
 *
 * File Name: graph.c
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION
 *		creates graph
 *
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"

/******************************************************************************
 * MATRIXint()
 *
 * Arguments: V - number of rows
 *            K - number of columns

 * Returns: int **matrix
 * Description: Creates a matrix of integers
 *
 *****************************************************************************/

int **MATRIXint(int V, int K, int init)
{
	int **matrix, i, j;

	matrix = (int **) malloc(sizeof(int *));

	for(i = 0; i < V; i++)
	{
		matrix[i] = (int *) malloc(sizeof(int));
	}

	for(i = 0; i < V; i++)
	{
		for(j = 0; j < K; j++)
		{
			matrix[i][j] = init;
		}
	}

	return matrix;
}

/******************************************************************************
 * GRAPHinit()
 *
 * Arguments: V - number of nodes

 * Returns: Graph
 * Description: Creates a graph
 *
 *****************************************************************************/

Graph *GRAPHinit(int V)
{
	Graph *G = (Graph *) malloc(sizeof(struct graph));
	G->V = V;
	G->E = 0;
	G->adj = 
}