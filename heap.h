/******************************************************************************
 *
 * File Name: heap.c
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION - Heap manipulation header
 *
 *****************************************************************************/
#include "defs.h"

typedef struct _heap Heap;

Heap *NewHeap(int tamanho, int (*less) (Item, Item), void (*print) (Item));

void FreeHeap(Heap * h);

int Insert(Heap * h, Item element);

int Direct_Insert(Heap * h, Item element);

void Modify(Heap * h, int indice, Item newvalue);

Item RemoveMax(Heap * h);

int PrintHeap(Heap * h);

void CleanHeap(Heap * h);

int VerifyHeap(Heap * h);

void HeapSort(Heap * h);

void Heapify(Heap * h);

