/******************************************************************************
 *
 * File Name: spots.c
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION
 *		reads the graph and creates the spots trees
 *
 *****************************************************************************/

#define EMPTY_SPOT 4
#define OCCUPIED 5

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "spots.h"


void merge(Parking_spot a[], int l, int m, int r, int maxN)
{
	int i, j, k;
	Parking_spot aux[maxN];

	for (i = m+1; i > l; i--)
		aux[i-1] = a[i-1];
	for (j = m; j < r; j++)
		aux[r+m-j] = a[j+1];
	for (k = l; k <= r; k++)
		if (LessNumPQ((Item) aux[i].distance, (Item) aux[j].distance))
			a[k] = aux[i++];
		else
			a[k] = aux[j--];
}


void mergesort(Parking_spot a[], int l, int r, int maxN)
{
	int m = (r+1)/2;

	if (r <= l)
		return;
	mergesort(a, l, m, maxN);
	mergesort(a, m+1, r, maxN);
	merge(a, l, m, r, maxN);
}


Parking_spot ** CreatesSpotsTable(Park *p)
{
	int i;

	Parking_spot **spots_matrix = (Parking_spot **) malloc((p->S)*sizeof(Parking_spot *));

	if(spots_matrix == NULL)
	{
		fprintf((stderr), "Error in malloc of spots matrix.\n");
		exit(0);
	}

	for(i = 0; i < p->Spots; i++)
	{
		spots_matrix[i] = (Parking_spot *) malloc(sizeof(Parking_spot));

		if(spots_matrix[i] == NULL)
		{
			fprintf(stderr, "Error in malloc of matrix.\n");
			exit(0);
		}
	}

	return spots_matrix;
}


void InsertSpotMatrix(Park *p, Parking_spot ** spots_matrix, int st[], long int wt[])
{
	int i, x = 0, y, pos;

	for(i = 0; i < p->G->V; i++)
	{
		if(p->G->node_info[i].type == EMPTY_SPOT || p->G->node_info[i].type == OCCUPIED)
		{
			spots_matrix[y][x].node = i;
			spots_matrix[y][x].status = p->G->node_info[i].status;
			printf("valor: %d\n", i);

			for(y = 0; y < p->S; y++)
			{
				pos = Get_Pos(p->accesses[y].pos->x, p->accesses[y].pos->y, p->accesses[y].pos->z, p->N, p->M);
				GRAPHpfs(p->G, pos, st, wt);
				spots_matrix[y][x].distance = 3*wt[i];
				printf("access: %d  dist: %ld\n", pos, spots_matrix[y][x].distance);	
			}
			x++;
		}
	}

	for(y = 0; y < p->S; y++)
		mergesort(spots_matrix[y], 0, p->Spots, p->G->V);

	for(y = 0; y < p->S; y++){
		for(x = 0; x < p->Spots; x++){
			printf("%ld ", spots_matrix[y][x].distance);
		}
		printf("\n\n");
	}	
}