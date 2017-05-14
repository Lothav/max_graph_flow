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

int main() {
	int V, E, F, C, u, v, m;
	int i;
	int edge_index;
	scanf("%d %d %d %d", &V, &E, &F, &C);
	Tree *tree = malloc(V * sizeof(Tree));
	for(i = 0; i < V; i++) {
		tree[i].type = TYPE_EMPTY;
		tree[i].edges_size = 0;
	}
	for(i = 0; i < E; i++) {
		scanf("%d %d %d", &u, &v, &m);
		edge_index = tree[u].edges_size;
		tree[u].edges_size++;
		tree[u].edges = realloc( tree[u].edges, (size_t)tree[u].edges_size * sizeof(Edge) );
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