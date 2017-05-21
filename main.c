#include <stdio.h>
#include <stdlib.h>

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

int breadthFirstSearch(Tree *tree, int tree_index, int recursion_index, int ** path){
	int i, r_value, to;
	if(tree[tree_index].type == TYPE_CLIENT){
		(*path) = malloc((recursion_index+1) * sizeof(int));
		(*path)[recursion_index] = tree_index;
		return tree_index;
	}
	if(tree[tree_index].edges_size && recursion_index){
		for (i = 0; i < tree[tree_index].edges_size; i++) {
			if (!tree[tree_index].edges[i].size) continue;
			to = tree[tree_index].edges[i].to;
			r_value = breadthFirstSearch(tree, to, recursion_index - 1, path);
			if (r_value == to && path != NULL) {
				(*path)[recursion_index] = tree_index;
				return tree_index;
			}
		}
	}
	return -1;
}

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
					tree[index].edges = realloc(tree[index].edges, (size_t)(++tree[index].edges_size) * sizeof(Edge));
					tree[index].edges[ edge_index ].to = b_index;
					tree[index].edges[ edge_index ].size = min_value;
				}
				if(min_value < 0){
					printf("lool");
				}
				break;
			}
		}
	}
}

int main() {
	int V, E, F, C, u, v, m;
	int i, j, min_value;
	int *path = NULL;
	int edge_index;
	scanf("%d %d %d %d", &V, &E, &F, &C);
	Tree *tree = malloc(V * sizeof(Tree));
	for(i = 0; i < V; i++) {
		tree[i].type = TYPE_EMPTY;
		tree[i].edges_size = 0;
		tree[i].edges = NULL;
	}
	for(i = 0; i < E; i++) {
		scanf("%d %d %d", &u, &v, &m);
		edge_index = tree[u].edges_size;
		tree[u].edges = realloc( tree[u].edges, (size_t)(++tree[u].edges_size) * sizeof(Edge) );
		tree[u].edges[ edge_index ].to = v;
		tree[u].edges[ edge_index ].size = m;
	}
	for(i = 0; i < F; i++) {
		scanf("%d", &u);
		tree[u].type = TYPE_FRANCHISE;
	}
	for(i = 0; i < C; i++) {
		scanf("%d", &u);
		tree[u].type = TYPE_CLIENT;
	}

	int total = 0;
	for(i = 0; i < V; i++) {
		if(tree[i].type == TYPE_FRANCHISE) {
			for(j = 1; j < V; j++) {
				if( breadthFirstSearch(tree, i, j, &path) != -1 ){
					min_value = getMinValue(tree, j, &path);
					total += min_value;
					setGraphWithMinValues(tree, j, &path, min_value);
					if(path != NULL){
						free(path);
						path = NULL;
					}
					j--;
				}
			}
		}
	}
	for(i = 0; i < V; i++) free(tree[i].edges);
	free(tree);

	printf("%d", total);
	return EXIT_SUCCESS;
}

/*
Test from

6 8 2 2
0 2 8
0 3 4
1 2 8
1 3 8
2 3 6
2 4 8
3 4 3
3 5 11
0
1
4
5

 */