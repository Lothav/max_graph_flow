#include <stdio.h>
#include <stdlib.h>

#include "tools.h"

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
				if( breadthFirstSearch(tree, i, j, &path, j) != -1 ){
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
	free(path);
	printf("%d", total);
	return EXIT_SUCCESS;
}