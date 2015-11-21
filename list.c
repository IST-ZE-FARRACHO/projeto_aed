/****************************************
     Abstract model for list use
*****************************************

This file contains the necessary functions to create and operate lists in C.*/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

list* listInit() /* Initializes a list*/
{
	list* l = (list *) malloc(sizeof(list));
	l->first = NULL;
	l->size = 0;
	return l;
}

node * InsertNode(Item) /* Inserts new Node with Item parameter and returns pointer to created node */
{

	node *node1 = (node*) malloc(sizeof(node));
	(*node1).Item = Item;
	(*node1).next = NULL;
	return(newnode);

}


void * DeleteNode(node *node1) /*Deletes memory allocated for one single node */
{
	free(node1);
}


node * InsertNextNode(node *node1, node *node2); /* Inserts the node that is after the other */
{

	(*node2).next = node1->next->next;
	(*node1).next = (*node2);

}


void * DeleteNextNode(node *node1) /*Deletes the node that is after the other */
{

	node *aux;
	aux = node1->next->next;
	DeleteNode(node1->next);
	node->next = aux;

}


Item GiveMeItem(node *node1) /*Returns Item of a given node */
{
	return (*node1).Item;
}

Item* listSearch() // Não acabado