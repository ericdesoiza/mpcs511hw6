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
    int u;
    int v;
    int distance;
} TopKHeapNode;

typedef struct {
    int length;
    int max_size;
    TopKHeapNode* arr;
} TopKHeap;

Heap* create_heap(int max_size);
void heappush(Heap* heap, int vertex, int distance);
void heapify_down(Heap* heap, int parent_index);
HeapNode heappop(Heap* heap);

TopKHeap* create_topkheap(int k);
void topkheappush(TopKHeap* heap, int u, int v, int distance);
TopKHeapNode topkheappop(TopKHeap* heap);