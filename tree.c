/******************************************************************************
 *
 * File Name: tree.c
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION
 *		creates a tree
 *
 *****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"

#define OCCUPIED 5

link_tree * NEW_tree(Parking_spot *spot)
{
	link_tree *x = (link_tree *) malloc(sizeof(link_tree));

	if(x == NULL)
	{
		fprintf(stderr, "Error in malloc of tree.\n");
		exit(1);
	}

	x->parking = (Parking_spot *) malloc(sizeof(Parking_spot));

	if(x->parking == NULL)
	{
		fprintf(stderr, "Error in malloc of tree.\n");
		exit(1);
	}

	x->parking = spot;
	x->left = NULL;
	x->right = NULL;

	return x;
}

int height(link_tree *tree)
{
	int hl, hr;

	if(tree == NULL)
		return 0;
	if(tree->left == NULL && tree->right == NULL)
		return 1;
	hl = height(tree->left);
	hr = height(tree->right);

	return ((hl>hr) ? 1+hl : 1+hr);
}

link_tree *rotate_right(link_tree * tree)
{
	link_tree *x, *y, *beta;

	if (tree == NULL) //if the tree is empty
		return tree;

	else if (tree->left == NULL)
		return tree;

	//saves the pointers
	y = tree;
	x = tree->left;
	beta = x->right;

	//updates the connections
	x->right = y;
	y->left = beta;

	return x;
}


link_tree *rotate_left(link_tree * tree)
{
	link_tree *x, *y, *beta;

	if(tree == NULL)
		return tree;

	else if(tree->left == NULL)
		return tree;

	x = tree;
	y = tree->right;
	beta = y->left;

	y->left = x;
	x->right = beta;

	return y;
}




link_tree * insert(Parking_spot *i, link_tree *tree)
{ 
	int h1, h2, h3;

	if(tree == NULL) //empty tree
	{
		tree = (link_tree *) malloc(sizeof(link_tree));

		if(tree == NULL)
		{
			fprintf(stderr, "Error in tree insertion.\n");
			exit(1);
		}

		tree->parking = (Parking_spot *) malloc(sizeof(Parking_spot));

		if(tree->parking == NULL)
		{
			fprintf(stderr, "Error in malloc of tree.\n");
			exit(1);
		}

		tree->parking = i;
		tree->left = tree->right = NULL;

		return tree;
	}

	if (i->distance < tree->parking->distance) //inserts in the left sub-tree
	{
		tree->left = insert(i, tree->left);
		h1 = height(tree->left->left);
		h2 = height(tree->left->right);
		h3 = height(tree->right);

		if (h1 > h3)
			tree = rotate_right(tree);
		if (h2 > h3)
		{
			tree->left = rotate_left(tree->left);
			tree = rotate_right(tree);
		}
	}

	else if(i->distance == tree->parking->distance)
	{
		if(i->secundary < tree->parking->secundary)
		{
			tree->right = insert(i, tree->right);
			h1 = height(tree->right->right);
			h2 = height(tree->right->left);
			h3 = height(tree->left);

			if (h1 > h3)
				tree = rotate_left(tree);
			if (h2 > h3)
			{
				tree->right = rotate_right(tree->right);
				tree = rotate_left(tree);
			}		
		}
	}

	else
	{
		tree->right = insert(i, tree->right);
		h1 = height(tree->right->right);
		h2 = height(tree->right->left);
		h3 = height(tree->left);

		if (h1 > h3)
			tree = rotate_left(tree);
		if (h2 > h3)
		{
			tree->right = rotate_right(tree->right);
			tree = rotate_left(tree);
		}
	}

	return tree;
}


link_tree * join(link_tree *a, link_tree *b)
{
	if (a == NULL)
		return b;
	if (b == NULL)
		return a;

	b = insert(a->parking, b);
	b = join(a->left, b);
	b = join(a->right, b);

	free(a);
	return b;
}

link_tree * delete(Parking_spot *i, link_tree *tree)
{
	link_tree *aux = tree;
	if (tree == NULL)
		return NULL;

	if (i->distance < tree->parking->distance)
		tree->left = delete(i, tree->left);
	if (i->distance > tree->parking->distance)
		tree->right = delete(i, tree->right);
	if (i->distance == tree->parking->distance)
	{
		tree = join(tree->left, tree->right);
		free(aux);
	}
	return tree;
}

