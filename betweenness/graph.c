#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

igraph_vector_t v;

void print_vector(igraph_vector_t *v, FILE *f) {
  long int i;
  for (i=0; i<igraph_vector_size(v); i++) {
    fprintf(f, " %li", (long int) VECTOR(*v)[i]);
  }
  fprintf(f, "\n");
}

igraph_t create_graph(char* file_name) {
  igraph_t g;
  int size, f, index = 0;

  // Create graph
  FILE *file = fopen (file_name, "r");
  fscanf(file, "%d", &size);
  igraph_vector_init(&v, size);
  while(fscanf(file, "%d", &f) > 0) {
     VECTOR(v)[index++] = f-1;
  }
  fclose(file);
  igraph_create(&g, &v, 0, IGRAPH_UNDIRECTED);
  
  return g;  
}

/* int main(int argc, char* argv[]) {

  igraph_vit_t vit;
  
  // Create a graph - pass filename
  igraph_t g = create_graph(argv[1]); 
  
  // Create an vit (iterator) through all of the vertices
  igraph_vit_create(&g, igraph_vss_all(), &vit);

  // Get the amount of items in the iterator
  printf("Vector Size: %ld\n\n", IGRAPH_VIT_SIZE(vit));
  
  // Check result
  igraph_get_edgelist(&g, &v, 0);
  igraph_vector_sort(&v);
  print_vector(&v, stdout);
  printf ("edge_count: %d\n", igraph_ecount(&g));
  igraph_write_graph_edgelist(&g, stdout);
  
  // Destroy resources
  igraph_vit_destroy(&vit);
  igraph_vector_destroy(&v);
  igraph_destroy(&g);

  return 0;
} */
