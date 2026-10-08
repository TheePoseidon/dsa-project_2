# include <stdio.h>
#define max 32

typedef struct {char id; int pr; } Container;
Container heap[max];
int n = 0;


static void swap(Container *a, Container *b) {Container t = *a; *a = *b; *b =t;}

void heapifyDown(int i) {
    for (;;) {
        int 1 = 2*i + 1, r = 2*i + 2, big = i;
        if (1 < n && heap[1].pr > heap[big].pr) big = 1;
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

void buildHeap(Void) {
    for (int i = n / 2 - 1; i >= 0; i--) heapifyDown(i);
}

void insert(char id, int pr) {
    heap[n].id = id; heap[n].pr = pr;
    heapifyUp(n++);
}

int removeById(char id) {
    for (int i = 0; i < n; i ++) {
        if (heap[i].id == id){
            heap[i] = heap[--n];
            if (i < n) { heapifyDown(i); heapifyUp(i); }
            return 1;
        }
    }
    return 0;
}

void printheap( const char * title) {
    printf("%s\n Array: ", title);
    for ( int  i = 0; i < n; i ++ ) printf("(%c(%d))", heap[i].id, heap[i].pr);
    printf("\n Tree:\n");
    int level = 0, count = 1;
    for (int i = 0;  i < n; ){
        printf("L%d: ", level++);
        for (int j = 0; j < count && i < n; j++, i++)
            printf("(%c(%d))", heap[i].id, heap[i].pr);
        printf("\n");
        count *= 2;
    }
    printf("\n");
}

int main(void) {
    int p[] = { 56,  23, 91, 34, 72, 48, 85, 17, 63, 79, 42};
    int size = sizeof p / sizeof p[0];
    for (int i = 0 ; i < size; i++) {
        heap[i].id = 'A' + i;
        heap[i].pr = p[i];
    }
    n = size;
    printHeap("Initial array");

    buildHeap();
    printHeap("After buildHeap");

    insert('x', 100);
    printHeap("After insert x(100)");

    removeById('x');
    printHeap("After remove x");

    return 0;
}
