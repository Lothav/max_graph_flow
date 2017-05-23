//
// Created by luizorv on 5/22/17.
//

#include <stdlib.h>
#include "graph.h"

void setGraphWithMinValues(Tree *tree, int size, int **path, int min_value){
	int i, j, k, index, b_index, edge_index;
	for(i = size; i; i--){
		index = (*path)[i-1];
		b_index = (*path)[i];
		for(j = 0; j < tree[b_index].edges_size; j++) {
			if(tree[b_index].edges[j].to == index){
				tree[b_index].edges[j].size -= min_value;
				//create new edge
				edge_index = tree[index].edges_size;
				for(k = 0; k < edge_index; k++){
					if(tree[index].edges[k].to == b_index){
						edge_index = k;
						break;
					}
				}
				if(edge_index < tree[index].edges_size){
					tree[index].edges[ edge_index ].size += min_value;
				} else {
					tree[index].edges_size++;
					tree[index].edges = realloc(tree[index].edges, (size_t)(++tree[index].edges_size + 15) * sizeof(Edge));
					tree[index].edges[ edge_index ].to = b_index;
					tree[index].edges[ edge_index ].size = min_value;
				}
				break;
			}
		}
	}
}

int breadthFirstSearch(Tree *tree, int tree_index, int recursion_index, int ** path, int path_size){
	int i, r_value, to;
	if(tree[tree_index].type == TYPE_CLIENT){
		(*path) = malloc((path_size+1) * sizeof(int));
		(*path)[recursion_index] = tree_index;
		return tree_index;
	}
	if(tree[tree_index].edges_size && recursion_index){
		for (i = 0; i < tree[tree_index].edges_size; i++) {
			if (!tree[tree_index].edges[i].size) continue;
			to = tree[tree_index].edges[i].to;
			r_value = breadthFirstSearch(tree, to, recursion_index - 1, path, path_size);
			if (r_value == to && path != NULL) {
				(*path)[recursion_index] = tree_index;
				return tree_index;
			}
		}
	}
	return -1;
}
