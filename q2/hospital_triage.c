# include <stdio.h>
# include <stdlib.h>
# include <string.h>
#define max 32

typedef struct {
    char id [8];
    char name [24];
    int pr;
} Patient;

Patient heap [max];
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
        if (heap[i].pr <= heap[p].pr) return;
        swap(&heap[i], &heap[p]);
        i = p;
    }
}

void buildHeap(void) {
    for (int i = n / 2 - 1; i >= 0; i--) heapifyDown(i);
}

void insert (const char *id, const char *name, int pr) {
    if (n >= max) {
        printf("Heap is full\n");
        return;
    }

    strcpy(heap[n].id, id);
    strcpy(heap[n].name, name);
    heap[n].pr = pr;
    heapifyUp(n++);
}

Patient exttractMax(void){
    Patient top = heap[0];
    heap[0] = heap[--n];
    if (n > 0) heapifyDown(0);
    return top;
}

int removeById (const char *id) {
    for (int i = 0; i < n; i++){
        if (strcmp(heap[i].id, id) == 0) {
            heap [i] = heap [--n];
            if (i < n) {
                heapifyDown(i);
                heapifyUp(i);
            }
            return 1;
        }
    }
    return 0;
}

int printHeap(const char *title){
    printf("%s\n Array: ", title);
    for (int i = 0; i < n; i++)
        printf("%s(%d)%s ", heap[i].id, heap[i].pr, heap[i].name);
    printf("\n Tree:\n");
    int level = 0, count = 1;
    for (int i = 0; i < n; ) {
        printf("L%d: ", level++);
        for (int j = 0; j < count && i < n; j++, i++)
            printf("%s(%d)%s ", heap[i].id, heap[i].pr, heap[i].name);
        printf("\n");
        count *= 2;
    }
    printf("\n");
}

int main (void) {
    const char *ids[] = {"PO1", "PO2", "PO3", "PO4", "PO5", "PO6", "PO7"};
    const char *names[] = {"Amina", "Daniel", "Eric", "Grace", "Hassan", "Irene", "Jean"};
    int scores[] = {72, 45, 91, 63, 88, 54, 76};
    int size = 7;
    for (int i = 0; i < size; i++){
        strcpy(heap[i].id, ids[i]);
        strcpy(heap[i].name, names[i]);
        heap[i].pr = scores[i];
    }

    n = size;
    printHeap("Before buildHeap");
    buildHeap();
    printHeap("After buildHeap");
    Patient backup[max];
    int backupN = n;
    memcpy(backup, heap, sizeof(heap));
    printf("Order of treatment:\n");
    while (n > 0) {
        Patient p = exttractMax();
        printf("Patient %s %s Priority %d\n", p.id, p.name, p.pr);
    }
    printf("\n");

    memcpy(heap, backup, sizeof(heap));
    n = backupN;
    insert("PO8", "Kofi", 98);
    printHeap("After inserting Kofi");
    removeById("PO8");
    printHeap("After removing Kofi");

    return 0;
}