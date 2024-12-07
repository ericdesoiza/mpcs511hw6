#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "graph.h"

void print_graph(Graph *g){
  Edgenode *e = NULL;
  for (int i=0;i<g->nvertices;++i){              /* for each node 0..NV-1 */
    e = g->edges[i];                             /* e=pointer to root of node i's edge list */
    while (e != NULL) {                          /* traverse list */
      printf("%d %d \n", i, e->y); /* print edge and weight */
      e = e->next;
    }
  }
}

void read_graph(char *filename, Graph *g, bool directed){
  int nvertices, nedges;
  int u,v;
  FILE *file = NULL;
  file = fopen(filename,"r");
  fscanf(file,"%d %d", &nvertices, &nedges);     /* read header */
  printf("NV = %d    NE = %d\n",nvertices,nedges);

  g->nvertices = nvertices;                      /* initialize Graph fields */
  g->nedges = nedges;
  g->directed = false;
  g->edges = malloc((nvertices)*sizeof(Edgenode));
  
  for (int i=0;i<nvertices;++i)
    g->edges[i] = NULL;
  
  Edgenode *prev;
  while (fscanf(file, "%d %d \n", &u,&v) != EOF) {
    Edgenode *new_node = (Edgenode *) malloc(sizeof(Edgenode));

    if (g->edges[u] == NULL) {       /* if first edge foor vertex u */
      g->edges[u] = new_node;
      g->edges[u]->y = v;
      g->edges[u]->next = NULL;
      prev = new_node;
    } else {                         /* adding another edge to vertex u */
      prev->next = new_node;
      new_node->y = v;
      new_node->next = NULL;
      prev = new_node;
    }
  }
  fclose(file);
}
