typedef struct {
  int vertex;
  int distance;
} HeapNode;

typedef struct {
  int length;
  int max_size;
  HeapNode* arr;
} Heap;

typedef struct {
    int length;
    int k;
    TopKHeapNode* arr;
} TopKHeap;

typedef struct {
    int u;
    int v;
    int distance;
} TopKHeapNode;

Heap* create_heap(int max_size);
void heappush(Heap* heap, int vertex, int distance);
HeapNode heappop(Heap* heap);

TopKHeap* create_topkheap(int k);
void topkheappush(TopKHeap* heap, int u, int v, int distance);
TopKHeapNode topkheappop(TopKHeap* heap);