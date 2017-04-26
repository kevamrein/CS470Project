/**
 * Computes betweenness centrality and returns the vertex with the
 * maximum betweenness.
 */

#include "graph.h"
#ifdef _OPENMP
#include <omp.h>
#endif

// Global Variables
igraph_t graph;
int vcount;

typedef struct Compare {
    double betweenness;
    int vid;
} Compare;

// Function Prototypes
struct Compare find_max_betweenness();

/**
 * Calls method to calculate the maximum betweenness and prints the execution time
 * to calculate the betweenness.
 */
int main(int argc, char *argv[]) {
    graph = create_graph(argv[1]);

    vcount = igraph_vcount(&graph);

    START_TIMER(find_max)
        struct Compare current_max = find_max_betweenness();
    STOP_TIMER(find_max);

    printf("Find Max Time: %f\n", GET_TIMER(find_max));

    return 0;
}

/**
 * Calculates the maximum betweenness using user-defined reductions.
 * Returns a Compare struct which contains the max betweenness value
 * as well as the vertex which had the max betweenness.
 */
struct Compare find_max_betweenness() {
    int i;
    // Create the struct that will hold the max values
    struct Compare max_vertex;
    max_vertex.betweenness = -1;
    max_vertex.vid = -1;


#   pragma omp parallel for default(none) shared(vcount, graph, max_vertex) \
    private(i)
    for (i = 0; i < vcount ; i+=1) {
        igraph_vs_t vs;
        igraph_vector_t result;
        igraph_vector_init(&result, 0);
        igraph_vs_1(&vs, i);
        igraph_betweenness(&graph, &result, vs, IGRAPH_UNDIRECTED, 0, 1);
        double betweenness = (double) VECTOR(result)[0];
#       pragma omp critical 
        {

            if (betweenness > max_vertex.betweenness) {
                max_vertex.betweenness = betweenness;
                max_vertex.vid = i;
            }
        }
        igraph_vector_destroy(&result);
        igraph_vs_destroy(&vs);
    }

    printf ("max vertex: %d, max_b: %f\n", max_vertex.vid, max_vertex.betweenness);
    return max_vertex;    
}
