#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/time.h>
#include <math.h>
#include <omp.h>
#include "graph.h"
#include "heap.h"

struct timeval timerStart;

void StartTimer(){
  gettimeofday(&timerStart, NULL);
}

double GetTimer(){
  struct timeval timerStop, timerElapsed;
  gettimeofday(&timerStop, NULL);
  timersub(&timerStop, &timerStart, &timerElapsed);

  return timerElapsed.tv_sec*1000.0+timerElapsed.tv_usec/1000.0;
}

void dijkstra(Graph *g, int start, int *distance) {
  int i;
  int v, w, weight, dist;
                                
  for (i=0; i < g->nvertices; i++) {  /* K and d data structures in pseudcoode */
    distance[i]   = INT_MAX;
  }
  distance[start] = 0;

  HeapNode vert_dist;
  Edgenode* edge;
  Heap* pq = create_heap(g->nvertices);

  heappush(pq, start, 0);

  while (pq->length > 0) {
    vert_dist = heappop(pq);
    edge = g->edges[vert_dist.vertex];
    while (edge) {
      if (distance[edge->y] > distance[vert_dist.vertex] + edge->weight) {
        distance[edge->y] = distance[vert_dist.vertex] + edge->weight;
        heappush(pq, edge->y, distance[edge->y]);
      }
      edge = edge->next;
    }
  }
  free(pq->arr);
  free(pq);
  return;
}

int isPowerOfTwo(int n) {
    // Handle base cases
    if (n <= 0) {
        return 0;
    }
    return (n & (n - 1)) == 0; 
}

int main(int argc, char **argv) {
  Graph g;
  char *filename;
  int i, j, u, v, w;

  filename = argv[1];
  read_graph(filename,&g,true);    
  print_graph(&g);

  int n_cores = omp_get_num_procs();

  printf("\nDONE\n");

  printf("Core Count: %d\n", omp_get_num_procs());

  TopKHeap** top_tens;
  int** dists;
  TopKHeapNode temp;
  TopKHeap *heap1, *heap2;
  TopKHeap* top_ten;
  int* dist;

  top_tens = malloc(n_cores * sizeof(TopKHeap*));
  for (i = 0; i < n_cores; i++)
    top_tens[i] = create_topkheap(10);

  dists = malloc(n_cores * sizeof(int*));
  for (i = 0; i < n_cores; i++)
    dists[i] = malloc(g.nvertices*sizeof(int));

  double start_time, end_time;
  start_time = omp_get_wtime();

  #pragma omp parallel for schedule(dynamic) shared(g) private(i,j, top_ten, dist)
  for (i = 0; i < g.nvertices; i++) {
    top_ten = top_tens[omp_get_thread_num()];
    dist = dists[omp_get_thread_num()];
    dijkstra(&g, i, dist);
    for (j = 0; j < g.nvertices; j++) {
      if (dist[j] == INT_MAX)
        continue;
      if (top_ten->length < 10) {
        topkheappush(top_ten, i, j, dist[j]);
      }
      else if (dist[j] > top_ten->arr[0].distance && top_ten->length == 10) {
        topkheappop(top_ten);
        topkheappush(top_ten, i, j, dist[j]);
      }
    }
  }

  for (i = n_cores-2; i >= 0; i--) {
    heap1 = top_tens[i];
    heap2 = top_tens[i+1];
    while (heap2->length > 0) {
      if (heap1->length < 10) {
        temp = topkheappop(heap2);
        topkheappush(heap1, temp.u, temp.v, temp.distance);
      }
      if (heap2->arr[0].distance > heap1->arr[0].distance) {
        temp = topkheappop(heap2);
        topkheappop(heap1);
        topkheappush(heap1, temp.u, temp.v, temp.distance);
      }
      else {
        topkheappop(heap2);
      }
    }
  }

  i = 9;
  TopKHeapNode* top_ten_arr = malloc(10 * sizeof(TopKHeapNode));
  TopKHeap* final_top_ten = top_tens[0];
  while (final_top_ten->length > 0) {
    top_ten_arr[i] = topkheappop(final_top_ten);
    i--;
  }
  for (j = 0; j < 10; j++)
    printf("%d %d %d\n", top_ten_arr[j].u, top_ten_arr[j].v, top_ten_arr[j].distance);

  end_time = omp_get_wtime();

  printf("Time Taken!: %.5lf\n", end_time - start_time);

  printf("%d\n", INT_MAX);

  for (i = 0; i < n_cores; i++)
    free(dists[i]);
  free(dists);

  for (i = 0; i < n_cores; i++) {
    free(top_tens[i]->arr);
    free(top_tens[i]);
  }
  free(top_tens);
  
  free(top_ten_arr);

  return(0);
}
