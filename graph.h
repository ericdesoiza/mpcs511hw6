#include<stdbool.h>
/* edgenode is a linked list owned by each vertex
   representing that nodes adjacent nodes
   y: node that this vertex is connected to
   w: weight of the connection
   next: pointer to next node in list
*/

typedef struct edgenode {
  int y;                  /* node connected to */
  int weight;             /* weight of connection */
  struct edgenode *next;  /* pointer to next node */
} Edgenode;

typedef struct {
  Edgenode **edges;        /* graph is just array of lists: each element of array is a node 
			      and list is list of adjacent nodes */
  int nvertices;           /* useful to store total size of graph, but number of vertices ...*/
  int nedges;              /* ... and number of edges */
  bool directed;           /* directed or undirected?? */
} Graph;

void print_graph(Graph *g);
void read_graph(char *filename, Graph *g, bool directed);
