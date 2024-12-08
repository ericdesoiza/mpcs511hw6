#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "graph.h"
#include "heap.h"

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
  return;
}


int main(int argc, char **argv) {
  Graph g;
  char *filename;
  int i, j, u, v, w;

  filename = argv[1];
  read_graph(filename,&g,true);    
  print_graph(&g);

  TopKHeap* top_ten = create_topkheap(10);
  TopKHeapNode temp;

  int *dist = malloc(g.nvertices*sizeof(int));
  for (i = 0; i < g.nvertices; i++) {
    dijkstra(&g, i, dist);
    for (j=0;j<g.nvertices;++j) {
      if (dist[j] != INT_MAX) {
        if (top_ten->length < 10)
          topkheappush(top_ten, i, j, dist[j]);
        else if (dist[j] > top_ten->arr[0] && top_ten->length == 10) {
          topkheappop(top_ten);
          topkheappush(top_ten, i, j, dist[j]);
        }
      }
    }
  }

  for (i = 0; i < 10; i++) {
    temp = topkheappop(top_ten);
    printf("%d %d %d\n", temp->u, temp->v, temp->dist);
  }

  free(dist);
  return(0);
}
