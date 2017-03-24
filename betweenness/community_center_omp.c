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
void normal_betweenness();

int main(int argc, char *argv[]) {
    // Get adjacency matrix or edges from the file and use Chuchi's functions
    // and put it in graph
    START_TIMER(graph_create)
    graph = create_graph(argv[1]);
    STOP_TIMER(graph_create)
    vcount = igraph_vcount(&graph);
    printf ("vertices: %d, edges: %d\n", vcount, igraph_ecount(&graph)); 

    START_TIMER(find_max)
    struct Compare current_max = find_max_betweenness();
    STOP_TIMER(find_max);

    START_TIMER(normal)
    normal_betweenness();
    STOP_TIMER(normal)
    igraph_destroy(&graph);

    printf("Graph Creation Time: %f\tFind Max Time: %f\tNormal: %f\n", GET_TIMER(graph_create), GET_TIMER(find_max), GET_TIMER(normal));
    return 0;
}

struct Compare find_max_betweenness() {
#   pragma omp declare reduction(maximum : struct Compare : omp_out = omp_in.val < omp_out.val ? omp_out : omp_in)
    int i;
    // Create the struct that will hold the max values
    struct Compare max_vertex;
    max_vertex.betweenness = -1;
    max_vertex.vid = -1;


//#   pragma omp parallel for default(none) shared(vcount, graph) \
    private(i) reduction(maximum: max_vertex)
#   pragma omp parallel for default(none) shared(max_vertex, vcount, graph) \
    private(i)
   for (i = 0; i < vcount; i++) {
        igraph_vs_t vs;
        igraph_vector_t result;
        igraph_vector_init(&result, 0);
        igraph_vs_1(&vs, i);
        igraph_betweenness(&graph, &result, vs, IGRAPH_UNDIRECTED, 0, 1);
        double betweenness = (double) VECTOR(result)[0];
        //printf ("i: %d betweenness: %f\n", i, betweenness);
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

void normal_betweenness() {
    igraph_vector_t result;
    igraph_vector_init(&result, igraph_vcount(&graph));
    igraph_betweenness(/*graph=*/ &graph, /*res=*/ &result, /*vids=*/ igraph_vss_all(), 
        /*directed=*/IGRAPH_UNDIRECTED, /*weights=*/ 0, /*nobigint=*/ 1);
    //print_vector(&result, stdout);
    igraph_vector_destroy(&result);
}
