# include <stdio.h>
# include <stdlib.h>
# define V 7
# define E 10

typedef struct {
    int u, v, w;
} Edge;

int parent[V];
int find(int x){
    return parent[x] == x ? x : (parent[x] = find(parent[x]));
}

int unite(int a, int b){
    a = find(a); b = find(b);
    if(a == b) return 0;
    parent[a] = b;
    return 1;
}

int cmp (const void *a, const void *b){
    return ((Edge *)a) ->w - ((Edge *)b) ->w;
}

int main (void) {
    Edge edges[E] = {
        {0, 1, 6},
        {0,3, 12},
        {1, 3, 5},
        {1, 2, 11},
        {2, 3, 17},
        {2, 6 , 25},
        {3, 4, 22},
        {3, 5, 15},
        {4, 5, 10},
        {5, 6, 22}
    };
    int adj[V][V] = {0};
    for (int i = 0; i < E; i++) {
        adj[edges[i].u][edges[i].v] = edges[i].w;
        adj[edges[i].v][edges[i].u] = edges[i].w;
    }
    printf("Adjacency Matrix:\n");
    for (int j = 0; j < V; j++) printf("%4c", 'A' + j);
    printf("\n");
    for (int i = 0; i < V; i++) {
        printf("%4c", 'A' + i);
        for (int j = 0; j< V; j++) printf("%4d", adj[i][j]);
        printf("\n");
    }
    qsort(edges, E, sizeof(Edge), cmp);
    for (int i = 0; i < V; i++) parent[i] = i;
    printf("\nSelected Connections;\n");
    int count = 0, total = 0;
    for (int i = 0; i < E && count < V -1; i++){
        if (unite(edges[i].u, edges[i].v)){
            printf("Station %c - Station %c : %d\n", 'A' + edges[i].u, 'A' + edges[i].v, edges[i].w);
            total += edges[i].w;
            count++;
        }
    }
    printf("\nTotal Cost: %d\n", total);
    return 0;
}