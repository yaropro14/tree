#ifndef TREE_H
#define TREE_H


 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef (char *) Data;

struct root
{
	struct Node * tree;		// value
};

struct Node
{
	Data val;            	// value
	struct Node * left;  	// left child
	struct Node * right; 	// right child
	struct Node * parent;	// parent
};


struct root create_tree();

struct Node * tree_add (struct Node * tree, struct Node * parent, Data val);
Data tree_get_elem( struct Node * node);
struct Node * search_element(struct Node * tree, Data val);
void tree_destroy (struct Node * tree);

Data tree_height(struct Node * tree);
void tree_print (struct Node * tree);

void print_tree_image(struct Node * tree);
//void print_tree_postfix(struct Node * tree, FILE * postfix, int left, int right);
int print_tree_list(struct Node * tree, FILE * file_graph);

Data max (Data x, Data y);


#include "tree.c"

#endif //TREE_H
