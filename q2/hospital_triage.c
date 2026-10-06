#include <stdio.h>
#include <string.h>

#define MAX 32

typedef struct {
    char id[8];
    char name[24];
    int  pr;
} Patient;

Patient heap[MAX];
int n = 0;

static void swap(Patient *a, Patient *b) {
    Patient t = *a; *a = *b; *b = t;
}

void heapifyDown(int i) {
    for (;;) {
        int l = 2*i + 1, r = 2*i + 2, big = i;
        if (l < n && heap[l].pr > heap[big].pr) big = l;
        if (r < n && heap[r].pr > heap[big].pr) big = r;
        if (big == i) return;
        swap(&heap[i], &heap[big]);
        i = big;
    }
}

void heapifyUp(int i) {
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[p].pr >= heap[i].pr) return;
        swap(&heap[p], &heap[i]);
        i = p;
    }
}

void buildHeap(void) {
    for (int i = n/2 - 1; i >= 0; i--) heapifyDown(i);
}

void insert(const char *id, const char *name, int pr) {
    if (n >= MAX) { printf("Heap full\n"); return; }
    strcpy(heap[n].id, id);
    strcpy(heap[n].name, name);
    heap[n].pr = pr;
    heapifyUp(n++);
}

Patient extractMax(void) {
    Patient top = heap[0];
    heap[0] = heap[--n];
    if (n > 0) heapifyDown(0);
    return top;
}

int removeById(const char *id) {
    for (int i = 0; i < n; i++) {
        if (strcmp(heap[i].id, id) == 0) {
            heap[i] = heap[--n];
            if (i < n) { heapifyDown(i); heapifyUp(i); }
            return 1;
        }
    }
    return 0;
}

void printHeap(const char *title) {
    printf("%s\n  Array: ", title);
    for (int i = 0; i < n; i++)
        printf("[%s %s %d] ", heap[i].id, heap[i].name, heap[i].pr);
    printf("\n  Tree:\n");
    int level = 0, count = 1;
    for (int i = 0; i < n; ) {
        printf("   L%d: ", level++);
        for (int j = 0; j < count && i < n; j++, i++)
            printf("%s %s(%d)  ", heap[i].id, heap[i].name, heap[i].pr);
        printf("\n");
        count *= 2;
    }
    printf("\n");
}

int main(void) {
    const char *ids[]   = {"P01","P02","P03","P04","P05","P06","P07"};
    const char *names[] = {"Amina","Daniel","Eric","Grace","Hassan","Irene","Jean"};
    int scores[]        = {72, 45, 91, 63, 88, 54, 76};
    int size = 7;

    for (int i = 0; i < size; i++) {
        strcpy(heap[i].id, ids[i]);
        strcpy(heap[i].name, names[i]);
        heap[i].pr = scores[i];
    }
    n = size;
    printHeap("Initial array (not a heap)");

    buildHeap();
    printHeap("1) After Max-Heap construction");

    Patient backup[MAX];
    int backupN = n;
    memcpy(backup, heap, sizeof heap);

    printf("2) Treatment order:\n");
    while (n > 0) {
        Patient p = extractMax();
        printf("   Patient %s %s - Priority %d\n", p.id, p.name, p.pr);
    }
    printf("\n");

    memcpy(heap, backup, sizeof heap);
    n = backupN;

    insert("P08", "Kofi", 98);
    printHeap("3) After inserting P08 Kofi (98)");

    removeById("P08");
    printHeap("4) After removing P08");

    return 0;
}
