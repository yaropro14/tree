#include<stdio.h>
#include <stdlib.h>

typedef int Data;

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
void print_tree_postfix(struct Node * tree, FILE * postfix, int left, int right);
int print_tree_list(struct Node * tree, FILE * file_graph);

Data max (Data x, Data y);


int main()
{
	struct root tree = create_tree();
	struct root tree1 = create_tree();
	//tree_print (tree.tree);
	
	tree.tree = tree_add (tree.tree, NULL, 5);
	//tree_print (tree.tree);
	
	tree.tree = tree_add (tree.tree, NULL, 3);
	//tree_print (tree.tree);
	
	tree.tree = tree_add (tree.tree, NULL, 4);
	//tree_print (tree.tree);
	
	tree.tree = tree_add (tree.tree, NULL, 1);
	//tree_print (tree.tree);
	
	
	tree.tree = tree_add (tree.tree, NULL, 2);
	//tree_print (tree.tree);
	
	tree.tree = tree_add (tree.tree, NULL, 8);
	//tree_print (tree.tree);
	
	tree.tree = tree_add (tree.tree, NULL, 9);
	//tree_print (tree.tree);
	
	tree.tree = tree_add (tree.tree, NULL, 6);
	//tree_print (tree.tree);
	
	tree.tree = tree_add (tree.tree, NULL, 7);
	//tree_print (tree.tree);
	
	//printf("h = %d\n", tree_height(tree.tree));
	
	tree1.tree = search_element(tree.tree, 8);
	
	FILE * postfix = fopen("postfix.txt", "w");
	
	print_tree_postfix(tree.tree, postfix, 1, 0);
	//print_tree_postfix(tree.tree->right, NULL, 0, 1);
	//printf("%d", tree1.tree);
	//printf("%d", tree_get_elem(tree1.tree));
	//printf("h = %d\n", tree_height(tree1.tree));
	//tree_print (tree1.tree);
	
	print_tree_image(tree.tree);

	//printf("%d", tree_get_elem(tree.tree));
	
	tree_destroy (tree.tree);
	return 0;
}


struct root create_tree()
{
	struct root new_root;
	
	new_root.tree = NULL;
	
	return new_root;
}


struct Node * tree_add (struct Node * tree, struct Node * parent, Data val)
{
	if (tree == NULL)
	{
		tree = (struct Node *) calloc(1, sizeof(struct Node));
		tree->val = val;
		tree->left = NULL;
		tree->right = NULL;
		tree->parent = parent;
		return tree;
	}
	
	else 
	{
		if (val == tree->val);
		
		if (val < tree->val)
			tree->left = tree_add (tree->left, tree,  val);
			
		else if (val > tree->val)
			tree->right = tree_add (tree->right, tree,  val);
			
	}
	
	return tree;
}


Data tree_get_elem( struct Node * node)
{
	return node->val;
}


void tree_destroy (struct Node * tree)
{
	if(tree->left != NULL)
		tree_destroy(tree->left);
	if (tree->right != NULL)
		tree_destroy(tree->right);
	free(tree);
}


struct Node * search_element(struct Node * tree, Data val)
{
	struct Node * tree_l = NULL;
	struct Node * tree_r = NULL;
	
	
	if(tree == NULL) return NULL;
	
	if(val == tree->val) return tree;
	
	else
	{
		if(tree->left != NULL)
			tree_l = search_element(tree->left, val);
		
		if(tree->right != NULL)
			tree_r = search_element(tree->right, val);
			
		if(tree_l == NULL) 
			return tree_l;
			
		else
			return tree_r;
	}
}


Data tree_height(struct Node * tree) {
	
	if (tree == NULL)
		return 0;
		
	return 1 + max(tree_height(tree->left), tree_height(tree->right));
}


void tree_print (struct Node * tree)
{
	if (tree == NULL)
		return;
		
	//printf("\n|%p|\n", tree->parent);
	tree_print(tree->left);
	printf("%d ", tree->val);
	tree_print(tree->right);
}


void print_tree_image(struct Node * tree)
{
	FILE * file_graph = fopen("graph.dot", "w");
	fprintf(file_graph, "graph tree {\n");
	//char ** lists = (char **) calloc(1, sizeof(cahr *));
	//int n_lists = 0;
	int i = print_tree_list(tree, file_graph);
	fprintf(file_graph, "}\n");
	fclose(file_graph);
	system("dot -Tpng graph.dot -o gtaph.png");
}


void print_tree_postfix(struct Node * tree, FILE * postfix, int left, int right)
{
	if (tree == NULL)
		return;
		
	else
	{
		if(left)
		{
			if (tree->left == NULL && tree->right == NULL)
			{
				//printf("!!!");
				fprintf(postfix, "%d", tree->val);
				return;
			}
			
			if (tree->left != NULL && tree->right != NULL)
			{
				fprintf(postfix, "(");
				left = 1;
				print_tree_postfix(tree->left, postfix, 1, 0);
				fprintf(postfix, ",");
				print_tree_postfix(tree->right, postfix, 0, 1);
				fprintf(postfix, ")");
				fprintf(postfix, "%d", tree->val);
				return;
			}
			
			if(tree->left == NULL)
			{
				//printf("left");
				fprintf(postfix, "(");
			}
			
			if(tree->left != NULL)
			{
				//printf("left");
				fprintf(postfix, "(");
				left = 1;
				print_tree_postfix(tree->left, postfix, 1, 0);
				fprintf(postfix, ",");
			}
			
			if(tree->right != NULL)
			{
				//printf("right");
				//printf("(");
				print_tree_postfix(tree->right, postfix, 0, 1);
				fprintf(postfix, ")");
			}
			
			if(tree->right == NULL)
			{
				fprintf(postfix, "0)");
				return;
			}
			
			fprintf(postfix, "%d", tree->val);
			
		}
			
			
		if(right)
		{
			
			if (tree->left != NULL && tree->right != NULL)
			{
				fprintf(postfix, "(");
				left = 1;
				print_tree_postfix(tree->left, postfix, 1, 0);
				fprintf(postfix, ",");
				print_tree_postfix(tree->right, postfix, 0, 1);
				fprintf(postfix, ")");
				fprintf(postfix, "%d", tree->val);
				return;
			}
			
			//printf("left");
			if(tree->left != NULL)
			{
				fprintf(postfix, "(");
				left = 1;
				print_tree_postfix(tree->left, postfix, 1, 0);
				fprintf(postfix, ",");
			}
			
			if (tree->left == NULL && tree->right == NULL)
			{
				//printf("!!!");
				fprintf(postfix, "%d", tree->val);
				//printf(")");
				return;
				
			}
			
			if(tree->left == NULL)
			{
				//printf("left");
				fprintf(postfix, "(");
			}
			
			if(tree->right != NULL)
			{
				fprintf(postfix, "(");
				print_tree_postfix(tree->right, postfix, 0, 1);
				fprintf(postfix, ")");
				return;
			}
			
			fprintf(postfix, "%d", tree->val);
			fprintf(postfix, ")");
		}
	}
	
	//return left;
}


int print_tree_list(struct Node * tree, FILE * file_graph)
{
	if (tree == NULL)
		return 0;
		
	if(tree->left != NULL)
	{
		fprintf(file_graph, "%d", tree->val);
		fprintf(file_graph, " -- ");
		int i = print_tree_list(tree->left, file_graph);
	}
	
	if(tree->right != NULL)
	{
		fprintf(file_graph, "%d", tree->val);
		fprintf(file_graph, " -- ");
		int i = print_tree_list(tree->right, file_graph);
	}
	
	
	if(tree->left == NULL && tree->right == NULL)
	{
		fprintf(file_graph, "%d;\n", tree->val);
	}
	
	return 0;
}


Data max (Data x, Data y)
{
	return x > y ? x : y;
}

