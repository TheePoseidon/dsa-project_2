#include <stdio.h>
#include <ctyp.h>
#include <string.h>

#define V 7

int adj[V][V] = {
    {  0,  6,  0, 12,  0,  0,  0 },
    {  6,  0, 11,  5,  0,  0,  0 },
    {  0, 11,  0, 17,  0,  0, 25 },
    { 12,  5, 17,  0, 22, 15,  0 },
    {  0,  0,  0, 22,  0, 10,  0 },
    {  0,  0,  0, 15, 10,  0, 22 },
    {  0,  0, 25,  0,  0, 22,  0 }
};

int queue[V], front = 0, rear = 0;
void enqueue(int x) { queue[rear++] = x; }
int  dequeue(void)  { return queue[front++]; }
int  isEmpty(void)  { return front == rear; }

int main(void) {
    char line[64];

    printf("Entr starting gateway (A-G): ");
    if (!fgets(line, sizeof line, stdin)) {
        printf("No input received.\n");
        return 1;
    }

    char c = '\0';
    int len = (int)strcspn(line, "\r\n");
    int k = 0;
    while (k < len && isspace((unsigned char)line[k])) k++;
    int end = len;
    while (end > k && isspace((unsigned char)line[end - 1])) end--;
    if (end - k == 1) c = (char)toupper((unsigned char)line[k]);

    if (c < 'A' || c >= 'A' + V) {
        printf("Invalid gateway. Please enter a single letter from A to G.\n");
        return 1;
    }

    int start = c - 'A';
    int visited[V] = {0};
    int hop[V] = {0};
    int order[V], oc = 0;

    visited[start] = 1;
    enqueue(start);
    while (!isEmpty()) {
        int u = dequeue();
        order[oc++] = u;
        for (int v = 0; v < V; v++) {
            if (adj[u][v] != 0 && !visited[v]) {
                visited[v] = 1;
                hop[v] = hop[u] + 1;
                enqueue(v);
            }
        }
    }

    printf("\nBFS traversal order from %c: ", c);
    for (int i = 0; i < oc; i++) printf("%c%s", 'A' + order[i], i < oc - 1 ? " -> " : "\n");

    printf("\nDirectly connected gateways (one hop):\n");
    int maxNode = -1, maxTime = -1, found = 0;
    for (int i = 0; i < oc; i++) {
        int v = order[i];
        if (hop[v] == 1) {
            printf("  %c  (%d ms)\n", 'A' + v, adj[start][v]);
            found = 1;
            if (adj[start][v] > maxTime) {
                maxTime = adj[start][v];
                maxNode = v;
            }
        }
    }

    if (!found) {
        printf("  None. Gateway %c has no direct links.\n", c);
        return 0;
    }

    printf("\nHighest data-transfer time among direct neighbors: Gateway %c (%d ms)\n",
           'A' + maxNode, maxTime);
    return 0;
}
