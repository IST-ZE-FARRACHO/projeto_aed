#include "listdefs.h" // Definir Item

typedef struct listNode* node;

/*A estrutura que corresponde a um elemento de uma list*/
typedef struct listNode
{
	Item item;
	lLink next;

}listNode;

list* listInit();

node * InsertNode(Item);

void * DeleteNode(*node);

node * InsertNextNode(*node, *node);

void * DeleteNextNode(*node);

Item GiveMeItem(*node);