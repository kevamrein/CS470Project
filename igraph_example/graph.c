#include <stdio.h>
#include <stdlib.h>
#include <igraph.h>

/* int main(int argc, char* argv[]) {

  FILE *file = fopen (argv[1], "r");
  int f, t;
  int test[6];
  while(fscanf(file, "%d %d", &f, &t) > 0) {
     //printf("%d -> %d\n", f, t); 
     test[f] = t;
  }
  fclose(file);
  
  for (int i = 1; i < 6; i++)
   printf ("%d = %d\n", i, test[i]);
  return 0;
}
*/

void print_vector(igraph_vector_t *v, FILE *f) {
  long int i;
  for (i=0; i<igraph_vector_size(v); i++) {
    fprintf(f, " %li", (long int) VECTOR(*v)[i]);
  }
  fprintf(f, "\n");
}

int main(int argc, char* argv[]) {

  igraph_t g;
  igraph_vit_t vit;
  igraph_vector_t v;
  int ret;

  // Create graph
  igraph_vector_init(&v, 156);
  FILE *file = fopen (argv[1], "r");
  int f;
  int index; 
  while(fscanf(file, "%d", &f) > 0) {
     VECTOR(v)[index++] = f;
  }
  fclose(file);
  igraph_create(&g, &v, 0, IGRAPH_UNDIRECTED);
  
  // Create an vit (iterator) through all of the vertices
  igraph_vit_create(&g, igraph_vss_all(), &vit);

  // Get the amount of items in the iterator
  printf("Size: %ld\n\n", IGRAPH_VIT_SIZE(vit));
  
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
}
