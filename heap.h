/******************************************************************************
 *
 * File Name: heap.c
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION - Heap manipulation header
 *
 *****************************************************************************/
#include "defs.h"

Heap *NewHeap(int tamanho, int (*less) (Item, Item), void (*print) (Item));

void FreeHeap(Heap * h);

int Insert(Heap * h, Item element);

void InsertNum(Heap * h, long int i);

int Direct_Insert(Heap * h, Item element);

void Modify(Heap * h, int indice, Item newvalue);

Item RemoveMax(Heap * h);

long int RemoveMin(Heap * h, long int vector[]);

int PrintHeap(Heap * h);

void CleanHeap(Heap * h);

int VerifyHeap(Heap * h);

Heap * HeapSort(Heap * h);

void Heapify(Heap * h);

int HeapEmpty(Heap * h);



