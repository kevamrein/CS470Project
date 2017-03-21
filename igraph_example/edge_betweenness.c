/* -*- mode: C -*-  */
/*
   IGraph library.
   Copyright (C) 2006-2012  Gabor Csardi <csardi.gabor@gmail.com>
   334 Harvard street, Cambridge, MA 02139 USA

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc.,  51 Franklin Street, Fifth Floor, Boston, MA
   02110-1301 USA

gcc edge_betweenness.c -I/usr/local/Cellar/igraph/0.7.1_3/include/igraph -L/usr/local/Cellar/igraph/0.7.1_3/lib -ligraph -o igraph_test

*/

#include <igraph.h>

void print_vector(igraph_vector_t *v, FILE *f) {
  long int i;
  for (i=0; i<igraph_vector_size(v); i++) {
    fprintf(f, "%.5f\n", (double) VECTOR(*v)[i]);
  }
  fprintf(f, "\n");
}

int main() {

  igraph_t g;
  igraph_vector_t eb, mine;

  igraph_small(&g, 0, IGRAPH_UNDIRECTED, 0, 1, 1, 2, 1, 3, 2, 3, 2, 4, 4, 6, 5, 6, 5, 7, 6, 8, 7, 10, 7, 8, 8, 10, 8, 9, 8, 11, -1);
  //igraph_small(&g, 0, IGRAPH_UNDIRECTED, 0, 1, 1, 2, 1, 3, 2, 3, 2, 4, 4, 6, 5, 6, 5, 7, 7, 10, -1);

  igraph_vector_init(&eb, igraph_ecount(&g));
  igraph_edge_betweenness(&g, &eb, IGRAPH_UNDIRECTED, /*weights=*/ 0);
  printf("EDGE BETWEENNESS\n\n");
  print_vector(&eb, stdout);
  igraph_vector_destroy(&eb);
  igraph_vector_init(&mine, igraph_ecount(&g));
  igraph_betweenness(/*graph=*/ &g, /*res=*/ &mine, /*vids=*/ igraph_vss_all(),
  		     /*directed=*/IGRAPH_UNDIRECTED, /*weights=*/ 0, /*nobigint=*/ 1);
             printf("\n\nBETWEENNESS\n\n");
             print_vector(&mine, stdout);

  igraph_vector_destroy(&mine);
  igraph_destroy(&g);

  return 0;
}
