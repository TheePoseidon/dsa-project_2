#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define V 10
#define E 15
#define INF INT_MAX

typedef struct { int from, to, w; } Edge;

Edge edges[E] = {
    {0,1, 6}, {0,3,16}, {1,2, 6}, {1,3, 6}, {1,9, 7},
    {2,6,-9}, {3,4, 7}, {3,9, 8}, {4,5,10}, {4,8,-2},
    {5,6, 4}, {5,8, 2}, {6,7,13}, {8,5, 2}, {9,4, 3}
};

int dist[V], pred[V];

int bellmanFord(int src) {
    for (int i = 0; i < V; i++) { dist[i] = INF; pred[i] = -1; }
    dist[src] = 0;

    for (int pass = 1; pass <= V - 1; pass++) {
        int changed = 0;
        for (int j = 0; j < E; j++) {
            int u = edges[j].from, v = edges[j].to, w = edges[j].w;
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pred[v] = u;
                changed = 1;
            }
        }
        if (!changed) break;
    }

    for (int j = 0; j < E; j++) {
        int u = edges[j].from, v = edges[j].to, w = edges[j].w;
        if (dist[u] != INF && dist[u] + w < dist[v]) return 1;
    }
    return 0;
}

void printPath(int v) {
    int stack[V], top = 0;
    for (int x = v; x != -1 && top < V; x = pred[x]) stack[top++] = x;
    for (int i = top - 1; i >= 0; i--)
        printf("%c%s", 'A' + stack[i], i ? " \xe2\x86\x92 " : "");
}

int parseVertex(const char *s) {
    while (isspace((unsigned char)*s)) s++;
    if (!*s) return -1;
    char c = (char)toupper((unsigned char)*s);
    const char *p = s + 1;
    while (isspace((unsigned char)*p)) p++;
    if (*p) return -1;
    return (c >= 'A' && c < 'A' + V) ? c - 'A' : -1;
}

int main(void) {
    char line[64];

    printf("Enter source data center (A-J) [A]: ");
    if (!fgets(line, sizeof line, stdin)) { printf("No inptu received.\n"); return 1; }
    line[strcspn(line, "\r\n")] = '\0';

    int src = 0;
    if (line[0] != '\0') {
        src = parseVertex(line);
        if (src < 0) {
            printf("Invalid data center '%s'. Use a single letter from A to J.\n", line);
            return 1;
        }
    }

    int negCycle = bellmanFord(src);

    if (negCycle) {
        printf("\nNegativeweight cycle detected.\n");
        printf("Shortest-path results may be undefined.\n");
        return 0;
    }
    printf("\nNo negative-weight cycle detected.\n");

    printf("\nSource: %c\n\n", 'A' + src);
    printf("%-13s %-15s %s\n", "Destination", "Shortest Cost", "Path");
    for (int v = 0; v < V; v++) {
        if (v == src) continue;
        if (dist[v] == INF) {
            printf("%-13c %-15s %s\n", 'A' + v, "unreachable", "-");
        } else {
            printf("%-13c %-15d ", 'A' + v, dist[v]);
            printPath(v);
            printf("\n");
        }
    }

    printf("\nEnter a destination to look up: ");
    if (fgets(line, sizeof line, stdin)) {
        line[strcspn(line, "\r\n")] = '\0';
        if (line[0] != '\0') {
            int d = parseVertex(line);
            if (d < 0) printf("Invalid data center '%s'.\n", line);
            else if (dist[d] == INF) printf("Destination: %c is unreachable from %c.\n", 'A' + d, 'A' + src);
            else {
                printf("Destination: %c\nPath: ", 'A' + d);
                printPath(d);
                printf("\nCost: %d\n", dist[d]);
            }
        }
    }
    return 0;
}
