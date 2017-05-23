#include <stdio.h>
#include <stdlib.h>

#include "tools.h"

int main() {

	//init variables
	int V, E, F, C, u, v, m;
	int i, j, min_value;
	int *path = NULL;
	int edge_index;

	// Read from STDIN and store on variables
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
		//mount graph from STDIN
		tree[u].edges = realloc( tree[u].edges, (size_t)(++tree[u].edges_size) * sizeof(Edge) );
		tree[u].edges[ edge_index ].to = v;
		tree[u].edges[ edge_index ].size = m;
	}

	//set FRANCHISE's and CLIENT's types
	for(i = 0; i < F; i++) {
		scanf("%d", &u);
		tree[u].type = TYPE_FRANCHISE;
	}
	for(i = 0; i < C; i++) {
		scanf("%d", &u);
		tree[u].type = TYPE_CLIENT;
	}

	int total = 0; 	//final result

	//principal loop
	for(i = 0; i < V; i++) {
		if(tree[i].type == TYPE_FRANCHISE) {
			for(j = 1; j < V; j++) {
				// here, 'j' is our recursion index and path length
				if( breadthFirstSearch(tree, i, j, &path, j) != -1 ){
					// here, we have get the path from graph
					min_value = getMinValue(tree, j, &path);
					// then, we get the minimal value from all edges
					total += min_value; // sum the result
					// set the graph with backwards edges
					setGraphWithMinValues(tree, j, &path, min_value);

					// clear path
					if(path != NULL){
						free(path);
						path = NULL;
					}
					// back recursion index
					j--;
				}
			}
		}
	}

	//free allocated memory
	for(i = 0; i < V; i++) free(tree[i].edges);
	free(tree);
	free(path);
	printf("%d", total);
	return EXIT_SUCCESS;
}