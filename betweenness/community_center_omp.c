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
    int max_vertex = -1;
    double max_betweenness = -1;
    double betweenness;
    printf ("vertices: %d, edges: %d\n", vcount, igraph_ecount(&graph)); 

#   pragma omp parallel for default(none) shared(vcount, graph, max_vertex) \
    private(betweenness, i) reduction(max: max_betweenness)
   for (i = 0; i < vcount; i++) {
        igraph_vs_t vs;
        igraph_vector_t result;
        igraph_vector_init(&result, 0);
        //igraph_vs_seq(&vs, i, i);
        igraph_vs_1(&vs, i);
        igraph_betweenness(&graph, &result, vs, IGRAPH_UNDIRECTED, 0, 1);
        betweenness = (double) VECTOR(result)[0];
        printf ("i: %d betweenness: %f\n", i, betweenness);
        if (betweenness > max_betweenness) {
            max_betweenness = betweenness;
            max_vertex = i;
            //printf("i: %d\n", i);
        }
        igraph_vs_destroy(&vs);
        igraph_vector_destroy(&result);
    }
    printf ("max vertex: %d, max_b: %f\n", max_vertex, max_betweenness);    
    
    igraph_destroy(&graph);
    return 0;
}

