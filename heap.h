typedef struct {
  int vertex;
  int distance;
} HeapNode;

typedef struct {
  int length;
  int max_size;
  HeapNode* arr;
} Heap;

Heap* create_heap(int max_size);
void heappush(Heap* heap, int vertex, int distance);
HeapNode heappop(Heap* heap);