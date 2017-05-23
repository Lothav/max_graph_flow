//
// Created by luizorv on 5/22/17.
//

#include "tools.h"

int getMinValue(Tree *tree, int size, int **path){
	int min_value = -1, i, j, index, b_index;
	for(i = size; i; i--){
		index = (*path)[i-1];
		b_index = (*path)[i];
		for(j = 0; j < tree[b_index].edges_size; j++) {
			if(tree[b_index].edges[j].size && tree[b_index].edges[j].to == index){
				min_value = tree[b_index].edges[j].size < min_value || min_value == -1 ? tree[b_index].edges[j].size : min_value;
			}
		}
	}
	return min_value;
}

