//
// Created by luizorv on 5/22/17.
//

#ifndef MAX_GRAPH_FLOW_GRAPH_H
#define MAX_GRAPH_FLOW_GRAPH_H

#define TYPE_EMPTY 0
#define TYPE_FRANCHISE 1
#define TYPE_CLIENT 2

typedef struct Edge {
	int to;
	int size;
} Edge;

typedef struct Tree {
	int type;
	Edge *edges;
	int edges_size;
} Tree;

int breadthFirstSearch(Tree *tree, int tree_index, int recursion_index, int ** path, int path_size);
void setGraphWithMinValues(Tree *tree, int size, int **path, int min_value);
#endif //MAX_GRAPH_FLOW_GRAPH_H
