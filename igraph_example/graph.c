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

int main() {

  igraph_t g;
  igraph_vector_t v;
  int ret;

  // Create graph
  igraph_vector_init(&v, 0);
  FILE *file = fopen (argv[1], "r");
  int f, t;
  while(fscanf(file, "%d %d", &f, &t) > 0) {
     VECTOR(v)[f]=t;
  }
  fclose(file);
  igraph_create(&g, &v, 0, IGRAPH_UNDIRECTED);

  // Check result
  igraph_get_edgelist(&g, &v, 0);
  igraph_vector_sort(&v);
  print_vector(&v, stdout);


  return 0;
}
