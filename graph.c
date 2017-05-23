//
// Created by luizorv on 5/22/17.
//

#include <stdlib.h>
#include "graph.h"

void setGraphWithMinValues(Tree *tree, int size, int **path, int min_value){
	// init useful variables
	int i, j, k, index, b_index, edge_index;

	// loop on path
	// size = path.length
	for(i = size; i; i--){
		index = (*path)[i-1];
		b_index = (*path)[i];
		// loop on tree to found those structs that indexes on path represent
		for(j = 0; j < tree[b_index].edges_size; j++) {
			if(tree[b_index].edges[j].to == index){
				// founded
				// deduct min value from his edge
				tree[b_index].edges[j].size -= min_value;

				//backwards edge:
				edge_index = tree[index].edges_size;
				for(k = 0; k < edge_index; k++){
					if(tree[index].edges[k].to == b_index){
						edge_index = k;
						break;
					}
				}
				// check if already exists backward edge
				if(edge_index < tree[index].edges_size){
					// case yes, set new size
					tree[index].edges[ edge_index ].size += min_value;
				} else {
					// otherwise, create it
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

	if(!recursion_index && tree[tree_index].type == TYPE_CLIENT){
		// reach the recursion index 0 and found the client
		// set it on the path and return their index
		(*path) = malloc((path_size+1) * sizeof(int));
		(*path)[recursion_index] = tree_index;
		return tree_index;
	}
	if(tree[tree_index].edges_size && recursion_index){
		// loop on edges vertex
		for (i = 0; i < tree[tree_index].edges_size; i++) {
			// check size
			if (!tree[tree_index].edges[i].size) continue;
			to = tree[tree_index].edges[i].to;
			// call recursion
			r_value = breadthFirstSearch(tree, to, recursion_index - 1, path, path_size);
			if (r_value == to && path != NULL) {
				// if we enter here, means one of the last heap recursion found client
				// and we going to complete the path with index's
				(*path)[recursion_index] = tree_index;
				return tree_index;
			}
		}
	}
	return -1;
}
