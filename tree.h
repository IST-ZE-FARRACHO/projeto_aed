/******************************************************************************
 *
 * File Name: tree.h
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION
 *
 *****************************************************************************/

 #ifndef tree_H
 #define tree_H

 #include "defs.h"

link_tree * NEW(Parking_spot *spot, link_tree *l, link_tree *r);
link_tree * parse();
int height(link_tree *tree);
link_tree *rotate_right(link_tree * tree);
link_tree *rotate_left(link_tree * tree);
link_tree * insert(Parking_spot *i, link_tree *tree);
link_tree * join(link_tree *a, link_tree *b);
link_tree * delete(int i, link *tree);

 #endif
