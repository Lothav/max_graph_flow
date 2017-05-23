//
// Created by luizorv on 5/22/17.
//

#include "tools.h"

int getMinValue(Tree *tree, int size, int **path){
	//init values
	int min_value = -1, i, j, index, b_index;
	// browse the vector vertex's
	for(i = size; i; i--){
		index = (*path)[i-1];
		b_index = (*path)[i];
		// browse the vector edges on each vertex
		for(j = 0; j < tree[b_index].edges_size; j++) {
			// check if value is lower than min_value
			if(tree[b_index].edges[j].size && tree[b_index].edges[j].to == index){
				min_value = tree[b_index].edges[j].size < min_value || min_value == -1 ? tree[b_index].edges[j].size : min_value;
			}
		}
	}
	// return min value
	return min_value;
}

