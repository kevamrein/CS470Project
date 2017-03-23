#include "graph.h"
#ifdef _OPENMP
#include <omp.h>
#endif

// Global Variables
igraph_t graph;

// Function prototypes
igraph_vit_t* get_iterators();

int main(int argc, char *argv[]) {
    int i;

    // Get adjacency matrix or edges from the file and use Chuchi's functions
    // and put it in graph
    graph = create_graph(argv[1]);
    int vcount = igraph_vcount(&graph);
    int max_vertex;
    double max_betweenness = -1;
    igraph_vector_t result;
    igraph_vector_init(&result, 0);
    printf ("vertices: %d, edges: %d\n", vcount, igraph_ecount(&graph)); 

//#   pragma omp parallel for default(none) shared(graph, max_vertex, max_betweenness) private(i)
   for (i = 0; i < vcount-1; i+=2) {
        igraph_vs_t vs = igraph_vss_seq(i-1, i);
        igraph_betweenness(&graph, &result, vs, IGRAPH_UNDIRECTED, 0, 1);
        double betweenness = (double) VECTOR(result)[0];
        printf ("betweenness: %d\n", betweenness);
//#       pragma omp critical
       // {
        if (betweenness > max_betweenness) {
            max_betweenness = betweenness;
            max_vertex = i; 
        }
      //  } 
    } 
    printf ("max vertex: %d, max_b: %d\n", max_vertex, max_betweenness);    
    
    igraph_vector_destroy(&result);
    igraph_destroy(&graph);
    return 0;
}

