#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "graph.h"


void dijkstra(Graph *g, int start, int *distance) {
  int i;
  Edgenode *p;
  bool *processed = malloc((g->nvertices)*sizeof(bool)); 
  int v, w, weight, dist;

                                    
  for (i=0; i < g->nvertices; i++) {  /* K and d data structures in pseudcoode */
    processed[i]  = false;
    distance[i]   = INT_MAX;
  }
  distance[start] = 0;
  v = start;                          /* v is current vertex being processed */


  while (processed[v] == false) {
    printf("processing vertex: %d\n", v);
    processed[v] = true;
    p = g->edges[v];    /* adjacency list for current node */
    while (p != NULL) {
      w = p->y;
      weight = p->weight;
      if (distance[w] > (distance[v]+weight)) 
        distance[w] = distance[v]+weight;
      p = p->next;
    }
  }
  
/* note: this loop is O(n) because of array, can do better */
  for (i=0,v=0,dist=INT_MAX; i < g->nvertices; i++) {
    if ((processed[i] == false) && (dist > distance[i])) {
      dist = distance[i];
      v = i;
    }
  }
  return;
}


int main(int argc, char **argv) {
  Graph g;
  char *filename;
  int i, u, v, w;

  filename = argv[1];
  read_graph(filename,&g,true);    
  print_graph(&g);


  int *dist = malloc(g.nvertices*sizeof(int));
  dijkstra(&g, 0, dist);
  for (i=0;i<g.nvertices;++i)
    printf("%d\n", dist[i]);
  free(dist);
  return(0);
}
